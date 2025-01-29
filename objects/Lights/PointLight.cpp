#include "PointLight.hpp"

PointLight::PointLight(const vec3& position, const float radius, const vec3& color, const float intensity) : Light(color, intensity), m_radius(radius) {
  m_position = position;
  SetBBox();
}

void PointLight::SetBBox() {
  m_bbox = BBox(m_position - vec3(m_radius), m_position + vec3(m_radius));
}

const bool PointLight::CheckRayCollision(Ray& ray) const {
  if(ray.depth() == 0) return false;
  
  vec3 ray_center = m_position - ray.origin();
  
  float ray_center_length = ray_center.length();
  
  float h = dot(ray.direction(), ray_center);
  float c = ray_center_length * ray_center_length - m_radius*m_radius;
  
  float discriminant = h*h - c;
  
  if (discriminant < 0) return false;
  
  float sqrt_d = std::sqrt(discriminant);
  float intersection_distance = h - sqrt_d;
  if(!ray.TryRecordIntersection(intersection_distance)) {
    intersection_distance = h + sqrt_d;
    if(!ray.TryRecordIntersection(intersection_distance)) return false;
  }
  return true;
}

void PointLight::UpdateHitRecord(Ray& ray) const{
  ray.SetLightColorIntensity(m_color * m_intensity);
}

