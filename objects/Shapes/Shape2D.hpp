#pragma once

#include "VisibleObject.hpp"

class Shape2D : public VisibleObject {
protected:
  vec3 m_shape_center;
  vec3 m_u, m_v;
    
  vec3 m_normal;
  vec3 m_normal_weight;
  float intersection_constant;
  
  
public:
  static float m_timer;
  
  Shape2D(const vec3& center, const vec3& u, const vec3& v, const std::string& material_name="default");
  
  void SetupShape();

  void SetRotation(const vec3& rotation);
  
  const bool CheckRayCollision(Ray& ray) const override;
  const vec3 GetHitNormal(const HitRecord& ray) const override;
  const vec2 GetTextureCoord(const HitRecord& ray) const override;
  void SetBBox() override;
  
  virtual const bool IsInShape(const float a, const float b) const = 0;
};
