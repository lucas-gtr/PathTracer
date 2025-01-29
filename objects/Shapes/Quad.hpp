#pragma once

#include "Shape2D.hpp"

class Quad : public Shape2D {
public:
  Quad(const vec3& center, const vec3& u, const vec3& v, const std::string& material_name="default");
  
  const bool IsInShape(const float a, const float b) const;
};
