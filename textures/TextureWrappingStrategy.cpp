#include "TextureWrappingStrategy.hpp"

vec2 RepeatWrapping::GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const {
  vec2 adjusted_texture_coord = texture_coord;
  
  if(texture_coord.x < 0.0f || texture_coord.x > 1.0 ||
     texture_coord.y < 0.0f || texture_coord.y > 1.0) {
    adjusted_texture_coord.x = std::fmod(texture_coord.x, 1.0);
    adjusted_texture_coord.y = std::fmod(texture_coord.y, 1.0);
    
    if(adjusted_texture_coord.x < 0.0f) adjusted_texture_coord.x += 1;
    if(adjusted_texture_coord.y < 0.0f) adjusted_texture_coord.y += 1;
  }
  
  float pixel_u = adjusted_texture_coord.x * (width - 1);
  float pixel_v = adjusted_texture_coord.y * (height - 1);
  
  return vec2(pixel_u, pixel_v);
}

vec2 RepeatMirrorWrapping::GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const {
  vec2 adjusted_texture_coord = texture_coord;
  
  if(texture_coord.x < 0.0f || texture_coord.x > 1.0 ||
     texture_coord.y < 0.0f || texture_coord.y > 1.0) {
    adjusted_texture_coord.x = std::fabs(std::fmod(texture_coord.x, 2.0));
    adjusted_texture_coord.y = std::fabs(std::fmod(texture_coord.y, 2.0));
    
    if(adjusted_texture_coord.x > 1.0f)
      adjusted_texture_coord.x = 2.0f - adjusted_texture_coord.x;
    if(adjusted_texture_coord.y > 1.0f)
      adjusted_texture_coord.y = 2.0f - adjusted_texture_coord.y;
  }
  
  return vec2(adjusted_texture_coord.x * (width - 1),
              adjusted_texture_coord.y * (height - 1));
}

vec2 ClampWrapping::GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const {
  vec2 adjusted_texture_coord = texture_coord;
  
  if (adjusted_texture_coord.x < 0.0f) adjusted_texture_coord.x = 0.0f;
  else if (adjusted_texture_coord.x > 1.0f) adjusted_texture_coord.x = 1.0f;
  if (adjusted_texture_coord.y < 0.0f) adjusted_texture_coord.y = 0.0f;
  else if (adjusted_texture_coord.y > 1.0f) adjusted_texture_coord.y = 1.0f;
  
  return vec2(adjusted_texture_coord.x * (width - 1),
              adjusted_texture_coord.y * (height - 1));
}

vec2 ClampColorWrapping::GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const {
  if(texture_coord.x < 0.0f || texture_coord.x > 1.0 ||
     texture_coord.y < 0.0f || texture_coord.y > 1.0)
    return vec2(-1.0f);
  
  return vec2(texture_coord.x * (width - 1),
              texture_coord.y * (height - 1));
}
