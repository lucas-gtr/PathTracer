#pragma once

#include <vector>
#include <fstream>

#include "Scene.hpp"
#include "TextureManager.h"
#include "ToneMappingStrategy.hpp"

enum class ToneMapping { NONE, REINHARD, EXPOSURE };

class Renderer {
private:
  float m_gamma = 2.2;
  
  std::unique_ptr<IToneMappingStrategy> m_tone_mapping_strategy = std::make_unique<ToneMappingReinhard>();
    
  void ApplyToneMapping(vec3& color);
  void ApplyGammaCorrection(vec3& color);
  
protected:
  unsigned int m_width, m_height;
  float m_frame_rate;
  unsigned int m_frame_range[2];
  
  long m_start_rendering_time = -1l;
  
  std::shared_ptr<Camera> m_rendering_camera;
  
  std::shared_ptr<Texture> m_background;
  std::vector<vec3> m_framebuffer;
  
  const vec3 GetBackgroundColor(const vec3& dir) const;
  
public:
  Renderer(unsigned int width = 1280, unsigned int height = 720);
  
  void SetWidth(unsigned int width);
  void SetHeight(unsigned int height);
  void SetToneMapping(ToneMapping tone_mapping, float exposure=1.0f);
  void SetGamma(float gamma);
  void SetBackground(std::string background_texture);
  void SetFrameRate(float frame_rate);
  void SetStartFrame(unsigned int start_frame);
  void SetEndFrame(unsigned int end_frame);
  void SetFrameRange(unsigned int start_frame, unsigned int end_frame);
  void SetFrameRange(unsigned int frame_range[2]);
  
  virtual void Render(const Scene& scene) = 0;
  
  void SetPixelColor(unsigned int x, unsigned int y, vec3& color);
  void AddPixelColor(unsigned int x, unsigned int y, const vec3& color);

  void SaveToDisk(const std::string& file_name);
};

