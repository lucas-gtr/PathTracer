#include "Quad.hpp"

Quad::Quad(const vec3& center, const vec3& u, const vec3& v, const std::string& material_name) : Shape2D(center, u, v, material_name) { }

const bool Quad::IsInShape(const float a, const float b) const {
  float x = a + 0.5f;
  float y = b + 0.5f;
  return (0.0f <= x && x <= 1.0f && 0.0f <= y && y <= 1.0f);
}


