#include "Sphere.hpp"

Sphere::Sphere(const vec3& center, const float radius, const std::string& material_name) : VisibleObject(vec3(0.0f), vec3(0.0f), vec3(radius  * 2.0f), material_name) {
  m_radius = radius;
  m_center = center;
  SetBBox();
}

void Sphere::SetBBox() {
  m_bbox = BBox(m_center + m_position - vec3(m_radius), m_center  + m_position + vec3(m_radius));
}

const bool Sphere::CheckRayCollision(Ray& ray) const {
  vec3 ray_center = m_center - (ray.origin() - m_position);
  
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

const vec3 Sphere::GetHitNormal(const HitRecord& hit_record) const {
  return (hit_record.intersection_point - m_position - m_center).normalized();
}

const vec2 Sphere::GetTextureCoord(const HitRecord& hit_record) const {
  const vec3 normal = (hit_record.intersection_point - m_position - m_center).normalized();
  
  vec3 rotatedNormal = normal;
  
  if (m_rotation.z != 0.0f) {
    float cosZ = std::cos(-radians(m_rotation.z));
    float sinZ = std::sin(-radians(m_rotation.z));
    rotatedNormal = vec3(rotatedNormal.x * cosZ - rotatedNormal.y * sinZ,
                         rotatedNormal.x * sinZ + rotatedNormal.y * cosZ,
                         rotatedNormal.z);
  }
  
  if (m_rotation.y != 0.0f) {
    float cosY = std::cos(-radians(m_rotation.y));
    float sinY = std::sin(-radians(m_rotation.y));
    rotatedNormal = vec3(rotatedNormal.x * cosY + rotatedNormal.z * sinY,
                         rotatedNormal.y,
                         -rotatedNormal.x * sinY + rotatedNormal.z * cosY);
  }
  
  if (m_rotation.x != 0.0f) {
    float cosX = std::cos(-radians(m_rotation.x));
    float sinX = std::sin(-radians(m_rotation.x));
    rotatedNormal = vec3(rotatedNormal.x,
                         rotatedNormal.y * cosX - rotatedNormal.z * sinX,
                         rotatedNormal.y * sinX + rotatedNormal.z * cosX);
  }
  
  float theta = std::acos(rotatedNormal.y);
  float phi = std::atan2(rotatedNormal.x, -rotatedNormal.z);
  
  if (phi < 0) phi += 2 * M_PI;
  
  return vec2(phi / (2*M_PI), theta / M_PI);
}
