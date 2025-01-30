#include "Renderer.hpp"

Renderer::Renderer(unsigned int width, unsigned int height) : m_width(width), m_height(height), m_framebuffer(width*height) {
  
}

void Renderer::SetWidth(unsigned int width){
  m_width = width;
}

void Renderer::SetHeight(unsigned int height){
  m_height = height;
}

void Renderer::SetGamma(float gamma) {
  m_gamma = gamma;
}

void Renderer::SetToneMapping(ToneMapping tone_mapping, float exposure)
{
  if (tone_mapping == ToneMapping::NONE)
    m_tone_mapping_strategy = std::make_unique<ToneMappingNone>();
  else if (tone_mapping == ToneMapping::REINHARD)
    m_tone_mapping_strategy = std::make_unique<ToneMappingReinhard>();
  else if (tone_mapping == ToneMapping::EXPOSURE)
    m_tone_mapping_strategy = std::make_unique<ToneMappingExposure>(exposure);
}

void Renderer::SetBackground(std::string background_texture){
  m_background = GetTexture(background_texture);
  
//  GetBackgroundColor(vec3(1.0f, 0.0f, 1.0f).normalized());
//  GetBackgroundColor(vec3(-1.0f, 0.0f, 1.0f).normalized());
}

const vec3 Renderer::GetBackgroundColor(const vec3& dir) const {
  static constexpr float INV_TWO_PI = 1.0f / (2.0f * M_PI);
  static constexpr float INV_PI = 1.0f / M_PI;
  
  float theta = std::acos(dir.y);
  float phi = std::atan2(dir.x, -dir.z);
  
  float fov_factor = M_PI / (2.0f * m_rendering_camera->fov());
  const vec3& dir_cam = m_rendering_camera->orientation();
  
  float theta_center_cam = std::acos(dir_cam.y);
  float phi_center_cam = std::atan2(dir_cam.x, -dir_cam.z);
  
  float angle_diff = phi - phi_center_cam;
  angle_diff = (angle_diff > M_PI) ? angle_diff - 2.0f * M_PI : (angle_diff < -M_PI ? angle_diff + 2.0f * M_PI : angle_diff);
  
  float new_phi = angle_diff * fov_factor + phi_center_cam;
  float new_theta = (theta - theta_center_cam) * fov_factor + theta_center_cam;
  
  new_phi = (new_phi < 0) ? new_phi + 2.0f * M_PI : new_phi;
  
  return m_background->GetValue3F(vec2(new_phi * INV_TWO_PI, new_theta * INV_PI));
}


void Renderer::SetStartFrame(unsigned int start_frame){
  m_frame_range[0] = start_frame;
}

void Renderer::SetEndFrame(unsigned int end_frame){
  m_frame_range[1] = end_frame;
}

void Renderer::SetFrameRange(unsigned int start_frame, unsigned int end_frame){
  SetStartFrame(start_frame);
  SetEndFrame(end_frame);
}

void Renderer::SetFrameRange(unsigned int frame_range[2]){
  SetStartFrame(frame_range[0]);
  SetEndFrame(frame_range[1]);
}


void Renderer::ApplyGammaCorrection(vec3& color) {
  for(int i = 0; i < 3; i++) {
    color[i] = pow(color[i], 1/m_gamma);
  }
}

void Renderer::ApplyToneMapping(vec3& color) {
  m_tone_mapping_strategy->GetColorLDR(color);
}

void Renderer::SetPixelColor(unsigned int x, unsigned int y, vec3& color) {
  x = std::max(0u, std::min(x, m_width - 1u));
  y = std::max(0u, std::min(y, m_height - 1u));
  
  ApplyGammaCorrection(color);
  
  m_framebuffer[x + m_width * y] = color;
}

void Renderer::AddPixelColor(unsigned int x, unsigned int y, const vec3& color) {
  x = std::max(0u, std::min(x, m_width - 1u));
  y = std::max(0u, std::min(y, m_height - 1u));
    
  m_framebuffer[x + m_width * y] += color;
}

void Renderer::SaveToDisk(const std::string& file_name) {
  std::ofstream ofs;
  ofs.open(file_name + ".ppm");
  ofs << "P6\n" << m_width << " " << m_height << "\n255\n";
  for (size_t i = 0; i < m_width*m_height; ++i) {
    vec3 color = m_framebuffer[i];
   
    ApplyToneMapping(color);
    ApplyGammaCorrection(color);

    ofs << (char)(256 * clamp(color[0], 0.0f, 0.999));
    ofs << (char)(256 * clamp(color[1], 0.0f, 0.999));
    ofs << (char)(256 * clamp(color[2], 0.0f, 0.999));
  }
  ofs.close();
}
