#pragma once

#include "geometry.h"

class Material;

struct HitRecord {
  bool hit = false;
  
  float IOR = 1.0f;
  
  float distance = std::numeric_limits<float>::max();
  vec3 intersection_point;
  
  std::shared_ptr<const Material> material = nullptr;
  vec2 texture_coord;
  vec3 normal;

  vec3 light_color_intensity;
};

class Ray {
private:
  const vec3 m_origin;
  const vec3 m_direction;
  
  static float m_init_min_dist;
  static float m_init_max_dist;
  
  float m_min_dist;
  float m_max_dist;
  
  const unsigned int m_depth;
  
  HitRecord m_hit_record;
  
public:
  Ray(const vec3& origin, const vec3& direction, const unsigned int depth = 0);
  
  const vec3& origin() const { return m_origin; }
  const vec3& direction() const { return m_direction; }
  
  const float distance() const { return m_hit_record.distance; }
  const float min_distance() const { return m_min_dist; }
  const float max_distance() const { return m_max_dist; }
  
  const unsigned int depth() const { return m_depth; }

  static void SetInitMinDistance(float distance);
  static void SetInitMaxDistance(float distance);
  
  void SetMinDistance(float distance);
  void SetMaxDistance(float distance);

  const bool IsDistanceOutOfBounds(const float distance);
  const void RecordIntersection(const vec3& intersection_point, const float distance);
  const bool TryRecordIntersection(const float distance);
  void SetNormal(const vec3& normal);
  void SetMaterial(const std::shared_ptr<const Material> material);
  void SetIOR(const float IOR);
  void SetTextureCoord(const vec2& texture_coord);
  void SetLightColorIntensity(const vec3& light_color_intensity);

  const HitRecord hit_record() const { return m_hit_record; }
};

