#pragma once

#include "Shape2D.hpp"

class Ellipse : public Shape2D {
public:
  Ellipse(const vec3& center, const vec3& u, const vec3& v, const std::string& material_name="default");
  
  const bool IsInShape(const float a, const float b) const;
};
