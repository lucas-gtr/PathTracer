#include "Triangle.hpp"

Triangle::Triangle(const vec3& p1, const vec3& p2, const vec3& p3, const std::string& material_name)
: Shape2D((p2 + p3) / 2.0f, p2 - p1, p3 - p1, material_name) { }


const bool Triangle::IsInShape(const float a, const float b) const {
  float x = a + 0.5f;
  float y = b + 0.5f;
  return (x >= 0.0f && y >= 0.0f && x + y <= 1.0f);
}
