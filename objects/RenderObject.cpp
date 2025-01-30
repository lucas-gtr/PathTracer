#include "RenderObject.hpp"

RenderObject::RenderObject(const vec3& position, const vec3& rotation, const vec3& scale) : HittableObject(position, rotation, scale) { }

void RenderObject::SetPosition(const vec3& position){
  m_position = position;
  SetBBox();
}

const bool RenderObject::hit(Ray& ray) const {
  if(!CheckRayCollision(ray)) return false;
  
  UpdateHitRecord(ray);

  return true;
}
