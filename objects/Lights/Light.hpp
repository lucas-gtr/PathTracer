#pragma once

#include "RenderObject.hpp"

class Light : public RenderObject {
protected:
  vec3 m_color;
  float m_intensity;
  
  Light(const vec3& color = vec3(1.0f), const float intensity = 1.0f);
  
public:
  const vec3& color() const { return m_color; }
  const float intensity() const { return m_intensity; }
};
