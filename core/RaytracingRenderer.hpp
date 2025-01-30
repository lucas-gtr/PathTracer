#pragma once

#include <sys/time.h>

#include "Renderer.hpp"
#include "Ray.hpp"
#include "BVHNode.hpp"

#include "random_generator.h"

class RaytracingRenderer : public Renderer {
private:
  struct Viewport {
    const vec3 pixel00_pos;
    const vec3 pixel_du;
    const vec3 pixel_dv;
    
    const vec3 lens_u;
    const vec3 lens_v;
        
    Viewport(const vec3& pixel00, const vec3& p_du, const vec3& p_dv, const vec3& l_u, const vec3& l_v) : pixel00_pos(pixel00), pixel_du(p_du), pixel_dv(p_dv), lens_u(l_u), lens_v(l_v){ }
  };
  
  Viewport InitializeViewport(std::shared_ptr<Camera> camera);
  Ray GenerateRay(int x, int y, int s_x, int s_y, const Viewport& viewport, std::shared_ptr<Camera> camera);
  
  float m_timer;

  unsigned int m_samples_per_pixel = 10u;
  unsigned int m_sqrt_samples_per_pixels = std::sqrt(m_samples_per_pixel);
  float m_grid_cell_size = 1 / m_sqrt_samples_per_pixels;
  float m_pixel_sample_factor = 1 / (m_samples_per_pixel * m_sqrt_samples_per_pixels);
  
  unsigned int m_max_depth = 10u;
  
  const float reflectance(float cosine, float IOR) const;
  const vec3 GetOutgoingDir(const vec3& incidence_dir, HitRecord& hit_record) const;

  vec3 GetRayRadiance(Ray& ray, const std::shared_ptr<BVHNode>& bvh_root);

public:
  RaytracingRenderer(unsigned int width, unsigned int height);
  
  void SetRayMinDistance(float distance);
  void SetRayMaxDistance(float distance);
  void SetSamplesPerPixels(unsigned int samples);
  void SetMaxDepth(unsigned int max_depth);
  
  void NormalizeSamples();

  void DisplayETA(const long current_sample);
  void Render(const Scene& scene) override;
  
  
};
