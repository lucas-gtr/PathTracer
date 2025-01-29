#include "Camera.hpp"

Camera::Camera(vec3 position, vec3 rotation, const float focal_length) : SceneObject(position, rotation, vec3(1.0f)) {
  SetFocalLength(focal_length);
}

const vec3 Camera::orientation() const {
  float pitch = radians(m_rotation.x);
  float yaw = radians(m_rotation.y);
  
  float cosPitch = std::cos(pitch);
  float sinPitch = std::sin(pitch);
  float cosYaw = std::cos(yaw);
  float sinYaw = std::sin(yaw);
  
  vec3 orientation;
  orientation.x = cosPitch * sinYaw;
  orientation.y = -sinPitch;
  orientation.z = -cosPitch * cosYaw;
  
  return orientation.normalized();
}

void Camera::LookAt(const vec3& point) {
  vec3 dir = (point - m_position).normalized();
  
  float pitch = std::asin(-dir.y);
  float yaw = std::atan2(dir.x, -dir.z);
  
  m_rotation = vec3(degrees(pitch), degrees(yaw), 0.0f);
}

void Camera::LookAt(std::shared_ptr<SceneObject> object) {
  LookAt(object->position());
}

void Camera::SetSensorWidth(const float sensor_width) {
  m_sensor_width = sensor_width;
  SetFocalLength(m_focal_length);
}

void Camera::SetFOV(float fov) {
  m_fov = radians(fov);
  m_focal_length = m_sensor_width / (2.0f * std::tan(radians(fov) / 2.0f));
}

void Camera::SetFocalLength(float focal_length) {
  m_focal_length = focal_length;
  m_fov = 2 * std::atan(m_sensor_width / (2.0f * focal_length));
}

void Camera::SetAperture(float aperture) {
  m_aperture = aperture;
}

void Camera::SetFocusDistance(const float focus_distance) {
  m_focus_distace = focus_distance;
}

void Camera::SetFocusObject(std::shared_ptr<SceneObject> object) {
  SetFocusDistance((object->position() - m_position).length());
}

void Camera::SetShutterSpeed(float shutter_speed) {
  m_shutter_speed = shutter_speed;
}

