#pragma once

#include "vec3.h"
#include "vec2.h"

inline float radians(const float angle_deg){
  return angle_deg * M_PI / 180.0f;
}

inline float degrees(const float angle_rad){
  return angle_rad * 180.0 / M_PI;
}

inline vec3 reflect(const vec3& incidence, const vec3& normal) {
  return incidence - 2 * dot(incidence, normal) * normal;
}

inline vec3 refract(const vec3& incidence, const vec3& normal, float IOR_factor) {
  float cos_theta = std::fmin(dot(-incidence, normal), 1.0);
  
  vec3 refract_perp =  IOR_factor * (incidence + cos_theta * normal);
  float refract_perp_length = refract_perp.length();
  
  vec3 refract_parallel = -std::sqrt(std::fabs(1.0 - refract_perp_length * refract_perp_length)) * normal;
  
  return refract_perp + refract_parallel;
}

//inline mat4 ortho(float x_min, float x_max, float y_min, float y_max, float zNear, float zFar){
//  mat4 orthographicMatrix(1.0f);
//  orthographicMatrix(0, 0) = 2 / (x_max - x_min);
//  orthographicMatrix(0, 3) = -(x_max + x_min) / (x_max - x_min);
//  orthographicMatrix(1, 1) = 2 / (y_max - y_min);
//  orthographicMatrix(1, 3) = -(y_max + y_min) / (y_max - y_min);
//  orthographicMatrix(2, 2) = -2 / (zFar - zNear);
//  orthographicMatrix(2, 3) = -(zFar + zNear) / (zFar - zNear);
//
//  return orthographicMatrix;
//}

inline float clamp(float x, float v_min, float v_max) {
  return std::max(v_min, std::min(v_max, x));
}
