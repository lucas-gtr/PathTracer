#pragma once

#include "geometry.h"

class SceneObject {
protected:
  vec3 m_position;
  vec3 m_rotation;
  vec3 m_scale;
  
public:
  SceneObject(const vec3& position = vec3(0.0f), const vec3& rotation = vec3(0.0f), const vec3& scale = vec3(1.0f));
  
  const vec3& position() const { return m_position; }
  const vec3& rotation() const { return m_rotation; }
  const vec3& scale() const { return m_scale; }
  
  void SetPosition(const vec3& position);
  void SetRotation(const vec3& rotation);
  void SetScale(const vec3& scale);
};
