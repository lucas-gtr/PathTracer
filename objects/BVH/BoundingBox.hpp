#pragma once

#include "Ray.hpp"

class BBox {
private:
  vec3 m_axis_bounds[2];
  float epsilon = 1e-3;
  
public:
  BBox();
  BBox(vec3 min_bounds, vec3 max_bounds);
  BBox(BBox bbox1, BBox bbox2);
  
  const vec3 (&axis_bounds() const)[2] { return m_axis_bounds; }
  const int longest_axis() const;
  
  const bool hit(Ray& ray) const;
};
