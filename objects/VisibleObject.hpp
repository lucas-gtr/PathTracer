#pragma once

#include "MaterialManager.h"
#include "RenderObject.hpp"

class VisibleObject : public RenderObject {
protected:
  std::shared_ptr<Material> m_material;
  
public:
  VisibleObject(const vec3& position, const vec3& rotation, const vec3& scale, const std::string& material_name="default");
  
  const std::shared_ptr<Material> material() const { return m_material; }
  
  virtual const vec3 GetHitNormal(const HitRecord& ray) const = 0;
  virtual const vec2 GetTextureCoord(const HitRecord& ray) const = 0;
  
  void UpdateHitRecord(Ray& ray) const;
};
