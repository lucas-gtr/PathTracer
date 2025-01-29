#pragma once

#include "Shape2D.hpp"

class Ring : public Shape2D {
private:
  float m_inner_radius;
  
public:
  Ring(const vec3& center, const vec3& u, const vec3& v, const float inner_radius, const std::string& material_name="default");
  
  const bool IsInShape(const float a, const float b) const;
};
