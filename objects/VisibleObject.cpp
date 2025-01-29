#include "VisibleObject.hpp"

VisibleObject::VisibleObject(const vec3& position, const vec3& rotation, const vec3& scale, const std::string& material_name) : RenderObject(position, rotation, scale) {
  m_material = GetMaterial(material_name);
}

void VisibleObject::UpdateHitRecord(Ray& ray) const {
  ray.SetMaterial(m_material);
  
  ray.SetTextureCoord(GetTextureCoord(ray.hit_record()));
  ray.SetNormal(GetHitNormal(ray.hit_record()));
}
