#include "Ellipse.hpp"

Ellipse::Ellipse(const vec3& center, const vec3& u, const vec3& v, const std::string& material_name)
: Shape2D(center, u, v, material_name) { }

const bool Ellipse::IsInShape(const float a, const float b) const {
  return (a * a / 0.25f + b * b / 0.25f) <= 1.0f;
}

