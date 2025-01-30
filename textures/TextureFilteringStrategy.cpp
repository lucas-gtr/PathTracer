#include "TextureFilteringStrategy.hpp"

const float NearestFiltering::GetFiltering1F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const{
  
  int x = static_cast<int>(pixel_coord.x);
  int y = static_cast<int>(pixel_coord.y);
  return image[x + y * width];
}

const vec3 NearestFiltering::GetFiltering3F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const{
  
  assert(channels != 1);
  int x = static_cast<int>(pixel_coord.x);
  int y = static_cast<int>(pixel_coord.y);
  
  vec3 filtering_value;
  for(int i = 0; i < 3; i++) {
    filtering_value[i] = image[channels * (x + y * width) + i];
  }
  return filtering_value;
}


std::array<float, 4> LinearFiltering::GetInterpolationWeights(const vec2& pixel_coord, const int width, const int height, int& x0, int& y0, int& x1, int& y1) const {
  
  x0 = static_cast<int>(pixel_coord.x - 0.5f);
  y0 = static_cast<int>(pixel_coord.y - 0.5f);
  
  x0 = std::max(0, std::min(x0, int(width) - 2));
  y0 = std::max(0, std::min(y0, int(height) - 2));
  
  x1 = (x0 + 1) < width ? x0 + 1 : x0;
  y1 = (y0 + 1) < height ? y0 + 1 : y0;
  
  float tx = pixel_coord.x - (x0 + 0.5f);
  float ty = pixel_coord.y - (y0 + 0.5f);
  
  return {{
    (1.0f - tx) * (1.0f - ty),
    (1.0f - tx) * ty, tx *
    (1.0f - ty),
      tx * ty}};
}

const float LinearFiltering::GetFiltering1F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const{
    
  int x0, y0, x1, y1;
  std::array<float, 4> weights = GetInterpolationWeights(pixel_coord, width, height, x0, y0, x1, y1);
  
  float c00 = image[(x0 + y0 * width)];
  float c01 = image[(x0 + y1 * width)];
  float c10 = image[(x1 + y0 * width)];
  float c11 = image[(x1 + y1 * width)];
  
  return weights[0] * c00 + weights[1] * c01 + weights[2] * c10 + weights[3] * c11;
}

const vec3 LinearFiltering::GetFiltering3F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const{
  
  assert(channels != 1);
  vec3 filtering_value;
  
  int x0, y0, x1, y1;
  std::array<float, 4> weights = GetInterpolationWeights(pixel_coord, width, height, x0, y0, x1, y1);
  
  int idx00 = channels * (x0 + y0 * width);
  int idx01 = channels * (x0 + y1 * width);
  int idx10 = channels * (x1 + y0 * width);
  int idx11 = channels * (x1 + y1 * width);
    
  for (int i = 0; i < 3; i++) {
    float c00 = image[idx00 + i];
    float c01 = image[idx01 + i];
    float c10 = image[idx10 + i];
    float c11 = image[idx11 + i];
    
    filtering_value[i] = (weights[0] * c00 + weights[1] * c01 +
                          weights[2] * c10 + weights[3] * c11);
  }
  
  return filtering_value;
}
