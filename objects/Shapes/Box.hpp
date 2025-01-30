#pragma once

#include "Quad.hpp"

class Box : public VisibleObject {
private:
  
public:
  std::shared_ptr<Quad> quad_list[6];
  Box(const vec3& center, const vec3& scale, const std::string& material_name="default");
  
  void SetRotation(const vec3 &rotation);

  void SetBBox() override;
  
  const bool hit(Ray& ray) const override;
  const bool CheckRayCollision(Ray& ray) const override { return true; };
  const vec3 GetHitNormal(const HitRecord& ray) const override { return vec3(0.0f); };
  const vec2 GetTextureCoord(const HitRecord& ray) const override { return vec2(0.0f); };
};
