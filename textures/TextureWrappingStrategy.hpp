#pragma once

#include "geometry.h"

class ITextureWrappingStrategy {
public:
  virtual ~ITextureWrappingStrategy() = default;
  virtual vec2 GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const = 0;
};

class RepeatWrapping : public ITextureWrappingStrategy {
public:
  vec2 GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const override;
};

class RepeatMirrorWrapping : public ITextureWrappingStrategy {
public:
  vec2 GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const override;
};

class ClampWrapping : public ITextureWrappingStrategy {
public:
  vec2 GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const override;
};

class ClampColorWrapping : public ITextureWrappingStrategy {
public:
  vec2 GetPixelCoordinates(const vec2& texture_coord, unsigned int width, unsigned int height) const override;
};
