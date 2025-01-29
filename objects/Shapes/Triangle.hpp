#pragma once

#include "Shape2D.hpp"

class Triangle : public Shape2D {
public:
  Triangle(const vec3& p1, const vec3& p2, const vec3& p3, const std::string& material_name="default");
  
  const bool IsInShape(const float a, const float b) const;
};
