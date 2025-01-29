#include "RaytracingRenderer.hpp"

RaytracingRenderer::RaytracingRenderer(unsigned int width, unsigned int height) : Renderer(width, height) { }

void RaytracingRenderer::SetRayMinDistance(float distance) {
  Ray::SetInitMinDistance(distance);
}

void RaytracingRenderer::SetRayMaxDistance(float distance) {
  Ray::SetInitMaxDistance(distance);
}

void RaytracingRenderer::SetSamplesPerPixels(unsigned int samples) {
  m_samples_per_pixel = samples;
  m_sqrt_samples_per_pixels = std::sqrt(m_samples_per_pixel);
  m_grid_cell_size = 1 / m_sqrt_samples_per_pixels;
  m_pixel_sample_factor = 1 / (m_sqrt_samples_per_pixels * m_sqrt_samples_per_pixels);
}

void RaytracingRenderer::SetMaxDepth(unsigned int max_depth){
  m_max_depth = max_depth;
}

const float RaytracingRenderer::reflectance(float cosine, float IOR) const {
  float r0 = (1 - IOR) / (1 + IOR);
  r0 = r0*r0;
  return r0 + (1-r0)*std::pow((1 - cosine),5);
}

const vec3 RaytracingRenderer::GetOutgoingDir(const vec3& incidence_dir, HitRecord& hit_record) const {
  const vec3& normal = hit_record.normal;
  auto& mat = hit_record.material;
  const vec2& tex_coord = hit_record.texture_coord;
  float opacity = mat->opacity(tex_coord);
  if (opacity < 1.0f) {
    float opacity_factor = random_float();
    
    if(opacity_factor >= opacity) {
      float IOR_factor;
      float ray_IOR = hit_record.IOR;
      if(ray_IOR == mat->IOR(tex_coord)) {
        ray_IOR = 1.0f;
        IOR_factor = mat->IOR(tex_coord) / ray_IOR;
      } else {
        IOR_factor = ray_IOR / mat->IOR(tex_coord);
        ray_IOR = mat->IOR(tex_coord);
      }
      
      float cos_theta = std::fmin(dot(-incidence_dir, normal), 1.0);
      float sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
      
      bool cannot_refract = IOR_factor * sin_theta > 1.0;
      vec3 direction;
      
      if (cannot_refract || reflectance(cos_theta, IOR_factor) > random_float())
        return reflect(incidence_dir, normal);
      else {
        hit_record.IOR = ray_IOR;
        return refract(incidence_dir, normal, IOR_factor);
      }
    }
  }
  
  float metalness = mat->metallic(tex_coord);
  if(metalness > 0.0f) {
    float metal_factor = random_float();
    if(metal_factor < metalness) {
      float roughness = mat->roughness(tex_coord);
      return (reflect(incidence_dir, normal) + (roughness * random_unit_vector<3>())).normalized();
    }
  }
  
  return (normal + random_unit_vector<3>()).normalized();
}

vec3 RaytracingRenderer::GetRayRadiance(Ray& ray, const std::shared_ptr<BVHNode>& bvh_root) {
  
  if(ray.depth() >= m_max_depth) return vec3(0.0f);
  if(!bvh_root->hit(ray)) return GetBackgroundColor(ray.direction());
  
  HitRecord hit_record = ray.hit_record();
  
  if(hit_record.material == nullptr) return hit_record.light_color_intensity;
  
  // TO ADD : TANGENT SPACE CALCULATION
  hit_record.normal = hit_record.material->normal_map(hit_record.texture_coord);
  vec3 outgoing_dir = GetOutgoingDir(ray.direction(), hit_record);
    
  Ray outgoing_ray(hit_record.intersection_point, outgoing_dir, ray.depth() + 1);
  outgoing_ray.SetIOR(hit_record.IOR);
  
  const vec3& diffuse_color = hit_record.material->diffuse(hit_record.texture_coord);
  const vec3& light_emit = hit_record.material->emission_color(hit_record.texture_coord) * hit_record.material->emission_intensity(hit_record.texture_coord);
  return light_emit + diffuse_color * (GetRayRadiance(outgoing_ray, bvh_root));
}

RaytracingRenderer::Viewport RaytracingRenderer::InitializeViewport(std::shared_ptr<Camera> camera){
  float viewport_width = 2 * std::tan(camera->fov()/2.0) * camera->focus_distance();
  float viewport_height = viewport_width * (float(m_height)/m_width);
  
  vec3 camera_v_up = vec3(0.0f, 1.0f, 0.0f);
  
  vec3 w = -camera->orientation();
  
  vec3 u;
  if (std::abs(w.y) > 0.999f) {
    u = vec3(1.0f, 0.0f, 0.0f);
  } else {
    u = vec_cross(camera_v_up, w).normalized();
  }
  vec3 v = vec_cross(w, u);
  
  vec3 viewport_u = viewport_width * u;
  vec3 viewport_v = viewport_height * -v;
  
  vec3 pixel_du = viewport_u / m_width;
  vec3 pixel_dv = viewport_v / m_height;
  
  vec3 viewport_upper_left = camera->position() + (-w * camera->focus_distance()) - viewport_u/2 - viewport_v/2;
  
  vec3 pixel00_pos = viewport_upper_left + (pixel_du + pixel_dv) * 0.5f;
  
  float lens_radius = camera->focal_length() / (2.0 * camera->aperture());
  vec3 lens_u = u * lens_radius;
  vec3 lens_v = v * lens_radius;
  return Viewport(pixel00_pos, pixel_du, pixel_dv, lens_u, lens_v);
}

Ray RaytracingRenderer::GenerateRay(int x, int y, int s_x, int s_y, Viewport viewport, std::shared_ptr<Camera> camera){
  vec2 offset = random_stratisfied(s_x, s_y, m_grid_cell_size);
  vec3 pixel_sample = viewport.pixel00_pos + ((x + offset.x) * viewport.pixel_du) + ((y + offset.y) * viewport.pixel_dv);
  
  vec2 lens_ray_origin = random_unit_vector<2>();
  vec3 ray_origin = camera->position() + (lens_ray_origin.x * viewport.lens_u) + (lens_ray_origin.y * viewport.lens_v);
  
  vec3 ray_direction = pixel_sample - ray_origin;
  
  return Ray(ray_origin, ray_direction.normalized());
}

void RaytracingRenderer::Render(const Scene& scene) {
  if(scene.camera() == nullptr) {
    std::cerr << "No camera attached to the scene" << '\n';
    return;
  }
  m_rendering_camera = scene.camera();
  if(scene.renderable_list().size() == 0) {
    std::cerr << "No object to render on the scene" << '\n';
    return;
  }
  
  timeval time_start;
  gettimeofday(&time_start, NULL);
  long start_time = (time_start.tv_sec * 10'000) + (time_start.tv_usec / 100);
  
  std::shared_ptr<BVHNode> bvh_root = std::make_shared<BVHNode>(scene.renderable_list());
  
  Viewport viewport = InitializeViewport(scene.camera());
  
  int total_samples = m_sqrt_samples_per_pixels * m_sqrt_samples_per_pixels;
  for (int s_y = 0; s_y < m_sqrt_samples_per_pixels; s_y++) {
    for (int s_x = 0; s_x < m_sqrt_samples_per_pixels; s_x++) {
      timeval current_time;
      gettimeofday(&current_time, NULL);
      long time_elapsed = ((current_time.tv_sec * 10'000) + (current_time.tv_usec / 100) - start_time) / 10000;
      
      int current_sample = m_sqrt_samples_per_pixels*s_y + s_x + 1;
      
      float time_to_one_sample = current_sample == 1 ? time_elapsed : float(time_elapsed) / (current_sample - 1);
      
      std::clog << "Sample " << current_sample << "/" << total_samples << " (ETA: " << int(time_to_one_sample * (total_samples - current_sample + 1)) / 60 << "m" << int(time_to_one_sample * (total_samples - current_sample + 1)) % 60 << "s, Elapsed : " << time_elapsed / 60 << "m" << time_elapsed % 60 << "s)" << '\n';
      for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
          Ray ray = GenerateRay(x, y, s_x, s_y, viewport, scene.camera());
          vec3 pixel_color = GetRayRadiance(ray, bvh_root);
          AddPixelColor(x, y, pixel_color);
        }
      }
    }
  }
  DividePixelColor(m_samples_per_pixel);
  
  timeval time_end;
  gettimeofday(&time_end, NULL);
  long time_elapsed = ((time_end.tv_sec * 10'000) + (time_end.tv_usec / 100) -  start_time) / 10000;
  std::clog << "Done in " << time_elapsed / 60 << "m" << time_elapsed % 60 << "s" << '\n';
}
