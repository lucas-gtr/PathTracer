#pragma once

#include "VisibleObject.hpp"

class Sphere : public VisibleObject {
private:
  float m_radius;
  vec3 m_center;
  
public:
  Sphere(const vec3& center, const float radius, const std::string& material_name="default");
  
  void SetBBox() override;
  
  const bool CheckRayCollision(Ray& ray) const override;
  const vec3 GetHitNormal(const HitRecord& ray) const override;
  const vec2 GetTextureCoord(const HitRecord& ray) const override;
};
