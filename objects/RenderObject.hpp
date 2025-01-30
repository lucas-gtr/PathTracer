#pragma once

#include "HittableObject.hpp"

class RenderObject : public HittableObject {
protected:
public:
  RenderObject(const vec3& position = vec3(0.0f), const vec3& rotation = vec3(0.0f), const vec3& scale = vec3(1.0f));
    
  void SetPosition(const vec3& position);
  virtual const bool CheckRayCollision(Ray& ray) const = 0;
  virtual void SetBBox() = 0;
  
  virtual const bool hit(Ray& ray) const;
  virtual void UpdateHitRecord(Ray& ray) const = 0;
};
