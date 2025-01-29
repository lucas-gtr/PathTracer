#pragma once

#include "geometry.h"

#include "TextureLoader.hpp"
#include "TextureWrappingStrategy.hpp"
#include "TextureFilteringStrategy.hpp"

enum class ColorSpace { RGB, sRGB };
enum class TextureWrapping { REPEAT, REPEAT_MIRROR, CLAMP, CLAMP_COLOR };
enum class TextureFiltering { NEAREST, LINEAR };

class Texture {
private:
  float* m_image;
  unsigned int m_channels;
  unsigned int m_width, m_height;
  
  ColorSpace m_color_space = ColorSpace::sRGB;
  
  vec4 m_clamp_border_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
  std::unique_ptr<ITextureWrappingStrategy> m_texture_wrapping_strategy = std::make_unique<RepeatMirrorWrapping>();
  std::unique_ptr<ITextureFilteringStrategy> m_texture_filtering_strategy = std::make_unique<LinearFiltering>();
  
  const vec2 GetPixelCoordinates(const vec2& texture_coord);
  
public:
  Texture(std::string file_path);
  explicit Texture(const float color);
  explicit Texture(const vec3& color);
  explicit Texture(const vec4& color);
    
  void SetWidth(unsigned int width);
  void SetHeight(unsigned int height);
  
  void SetColorSpace(ColorSpace color_space);

  void SetTextureFiltering(TextureFiltering texture_filtering);
  void SetTextureWrapping(TextureWrapping texture_wrapping);
  void SetClampBorderColor(const vec3& color);
  
  float GetValue1F(const vec2& texture_coord);
  vec3 GetValue3F(const vec2& texture_coord);
  vec4 GetValue4F(const vec2& texture_coord);
  
  ~Texture();
};
