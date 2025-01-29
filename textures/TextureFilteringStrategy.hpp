#pragma once

#include "geometry.h"

class ITextureFilteringStrategy {
public:
  virtual ~ITextureFilteringStrategy() = default;
  virtual const float GetFiltering1F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const = 0;
  virtual const vec3 GetFiltering3F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const = 0;
  virtual const vec4 GetFiltering4F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const = 0;
};

class NearestFiltering : public ITextureFilteringStrategy {
public:
  virtual const float GetFiltering1F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const override;
  virtual const vec3 GetFiltering3F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image)  const override;
  virtual const vec4 GetFiltering4F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const override;
};

class LinearFiltering : public ITextureFilteringStrategy {
private:
  std::array<float, 4> GetInterpolationWeights(const vec2& pixel_coord, const int width, const int height, int& x0, int& y0, int& x1, int& y1) const;
  
public:
  virtual const float GetFiltering1F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const override;
  virtual const vec3 GetFiltering3F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image)  const override;
  virtual const vec4 GetFiltering4F(const vec2& pixel_coord, const int width, const int height, const int channels, const float* image) const override;
};
