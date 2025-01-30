#pragma once

#include <cstdlib>

#include "geometry.h"

inline float random_float() {
  return std::rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
  return min + (max-min)*random_float();
}

inline vec2 random_vec2(float min=0.0f, float max=1.0f){
  vec2 v;
  v[0] = random_float(min, max);
  v[1] = random_float(min, max);
  
  return v;
}

inline vec2 random_unit_vec2(float min=0.0f, float max=1.0f){
  while (true) {
    vec2 v = random_vec2(-1.0f, 1.0f);
    float length = v.length();
    if (length > 1e-20 && length*length <= 1)
      return v / length;
  }
}

inline vec3 random_vec3(float min=0.0f, float max=1.0f){
  vec3 v;
  v[0] = random_float(min, max);
  v[1] = random_float(min, max);
  v[2] = random_float(min, max);

  return v;
}

inline vec3 random_unit_vec3(float min=0.0f, float max=1.0f){
  while (true) {
    vec3 v = random_vec3(-1.0f, 1.0f);
    float length = v.length();
    if (length > 1e-20 && length*length <= 1)
      return v / length;
  }
}

inline vec2 random_stratisfied(int s_x, int s_y, int cell_size) {
  float px = ((s_x + random_float()) * cell_size) - 0.5;
  float py = ((s_y + random_float()) * cell_size) - 0.5;
  
  return vec2(px, py);
}
