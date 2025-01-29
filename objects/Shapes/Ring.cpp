#include "Ring.hpp"

Ring::Ring(const vec3& center, const vec3& u, const vec3& v, const float inner_radius, const std::string& material_name)
: Shape2D(center, u, v, material_name), m_inner_radius(inner_radius) { }

const bool Ring::IsInShape(const float a, const float b) const {
  float center_distance_squared = (a*a + b*b) / 0.25f;
  return (m_inner_radius * m_inner_radius <= center_distance_squared &&
          center_distance_squared <= 1.0);
}
