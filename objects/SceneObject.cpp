#include "SceneObject.hpp"

SceneObject::SceneObject(const vec3& position, const vec3& rotation, const vec3& scale) {
  m_position = position;
  m_rotation = rotation;
  m_scale = scale;
}

void SceneObject::SetPosition(const vec3& position) {
  m_position = position;
}

void SceneObject::SetRotation(const vec3& rotation) {
  m_rotation = rotation;
}

void SceneObject::SetScale(const vec3& scale) {
  m_scale = scale;
}
