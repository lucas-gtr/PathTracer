#pragma once

#include "Light.hpp"

class PointLight : public Light {
private:
  float m_radius;
  
public:
  PointLight(const vec3& position, const float m_radius, const vec3& color = vec3(1.0f), const float intensity = 1.0f);
    
  const bool CheckRayCollision(Ray& ray) const;
  void SetBBox();
  
  void UpdateHitRecord(Ray& ray) const;
};
