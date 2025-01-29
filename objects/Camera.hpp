#pragma once

#include "geometry.h"

#include "SceneObject.hpp"

class Camera : public SceneObject {
private:
  float m_sensor_width = 0.036;
  float m_focal_length;
  float m_fov;
  
  float m_aperture = 1.8f;
  float m_focus_distace = 10.0f;
  
  float m_shutter_speed = 1.0f;
  
public:
  Camera(vec3 position = vec3(0.0f), vec3 rotation = vec3(0.0f), float focal_length = 0.050);

  const vec3 orientation() const;
  
  void LookAt(const vec3& point);
  void LookAt(std::shared_ptr<SceneObject> object);

  const float sensor_width() const { return m_sensor_width; }
  const float fov() const { return m_fov; }
  const float focal_length() const { return m_focal_length; }
  const float focus_distance() const { return m_focus_distace; }
  const float aperture() const { return m_aperture; }
  const float shutter_speed() const { return m_shutter_speed; }

  void SetSensorWidth(const float sensor_width);
  void SetFOV(const float fov);
  void SetFocalLength(const float focal_length);
  
  void SetAperture(float aperture);
  void SetFocusDistance(const float focus_distance);
  void SetFocusObject(std::shared_ptr<SceneObject> focus_object);

  void SetShutterSpeed(float shutter_speed);
};
