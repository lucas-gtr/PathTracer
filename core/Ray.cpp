#include "Ray.hpp"

float Ray::m_init_min_dist = 1e-8f;
float Ray::m_init_max_dist = 1e4f;

Ray::Ray(const vec3& origin, const vec3& direction, unsigned int depth) : m_origin(origin), m_direction(direction), m_depth(depth) {
  m_min_dist = m_init_min_dist;
  m_max_dist = m_init_max_dist;
}

const bool Ray::IsDistanceOutOfBounds(const float distance) {
  return (distance < m_min_dist || distance > m_max_dist || distance > m_hit_record.distance);
}

const void Ray::RecordIntersection(const vec3& intersection_point, const float distance) {
  m_hit_record.distance = distance;
  m_hit_record.intersection_point = intersection_point;
  m_hit_record.hit = true;
}

const bool Ray::TryRecordIntersection(const float distance) {
  if(IsDistanceOutOfBounds(distance)) return false;
  
  RecordIntersection(m_origin + distance * m_direction, distance);
  
  return true;
}

void Ray::SetLightColorIntensity(const vec3& light_color_intensity) {
  m_hit_record.light_color_intensity = light_color_intensity;
  m_hit_record.material = nullptr;
  m_hit_record.hit = true;
}

void Ray::SetNormal(const vec3 &normal) {
  if(dot(m_direction, normal) < 0) m_hit_record.normal = normal;
  else m_hit_record.normal = -normal;
}

void Ray::SetMaterial(const std::shared_ptr<const Material> material) {
  m_hit_record.material = material;
}

void Ray::SetIOR(const float IOR) {
  m_hit_record.IOR = IOR;
}

void Ray::SetMinDistance(float distance) {
  m_min_dist = distance;
}

void Ray::SetMaxDistance(float distance) {
  m_max_dist = distance;
}

void Ray::SetInitMinDistance(float distance) {
  m_init_min_dist = distance;
}

void Ray::SetInitMaxDistance(float distance) {
  m_init_max_dist = distance;
}

void Ray::SetTextureCoord(const vec2& texture_coord) {
  m_hit_record.texture_coord = texture_coord;
}
