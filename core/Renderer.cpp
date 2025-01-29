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

void Renderer::SetToneMapping(ToneMapping tone_mapping, float exposure) {
  switch (tone_mapping) {
    case ToneMapping::NONE:
      m_tone_mapping_strategy = std::make_unique<ToneMappingNone>();
      break;
    case ToneMapping::REINHARD:
      m_tone_mapping_strategy = std::make_unique<ToneMappingReinhard>();
      break;
    case ToneMapping::EXPOSURE:
      m_tone_mapping_strategy = std::make_unique<ToneMappingExposure>(exposure);
      break;
  }
}


void Renderer::SetBackground(std::string background_texture){
  m_background = GetTexture(background_texture);
}

const vec3 Renderer::GetBackgroundColor(const vec3& dir) const{
  float theta = std::acos(dir.y);
  float phi = std::atan2(dir.x, -dir.z);
  
  if (phi < 0) phi += 2 * M_PI;
  
  return m_background->GetValue3F(vec2(phi / (2 * M_PI), theta / M_PI));
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

void Renderer::DividePixelColor(const float n_samples){
  for (size_t i = 0; i < m_width*m_height; ++i) {
    m_framebuffer[i] /= n_samples;
  }
}

void Renderer::SaveToDisk(const std::string& file_name) {
  std::ofstream ofs;
  ofs.open(file_name + ".ppm");
  ofs << "P6\n" << m_width << " " << m_height << "\n255\n";
  for (size_t i = 0; i < m_width*m_height; ++i) {
    vec3 color = m_framebuffer[i];
   
    ApplyToneMapping(color);
    ApplyGammaCorrection(color);

    ofs << (char)(256 * clamp(color.r, 0.0f, 0.999));
    ofs << (char)(256 * clamp(color.g, 0.0f, 0.999));
    ofs << (char)(256 * clamp(color.b, 0.0f, 0.999));
  }
  ofs.close();
}
