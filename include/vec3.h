#pragma once
  
#include <cmath>
#include <iostream>
#include <algorithm>
  
  class vec3 {
  public:
    float values[3];
    float& x = values[0];
    float& y = values[1];
    float& z = values[2];
    
    inline vec3() : values{0.0f, 0.0f, 0.0f} {}
    inline vec3(float x, float y, float z) : values{x, y, z} {}
    inline explicit vec3(float scalar) : values{scalar, scalar, scalar} {}
    
    inline vec3(const vec3& other) : values{other[0], other[1], other[2]} {}
    inline vec3& operator=(const vec3& other) { values[0] = other[0]; values[1] = other[1]; values[2] = other[2]; return *this; }
    
    inline float& operator[](size_t i) { return values[i]; }
    inline const float& operator[](size_t i) const { return values[i]; }
    
    inline vec3 operator+() const { return *this; }
    inline vec3 operator-() const { return {-values[0], -values[1], -values[2]}; }
    
    inline vec3 operator+(const vec3& other) const { return {values[0] + other[0], values[1] + other[1], values[2] + other[2]}; }
    inline vec3 operator-(const vec3& other) const { return {values[0] - other[0], values[1] - other[1], values[2] - other[2]}; }
    inline vec3 operator*(const vec3& other) const { return {values[0] * other[0], values[1] * other[1], values[2] * other[2]}; }
    inline vec3 operator/(const vec3& other) const { return {values[0] / other[0], values[1] / other[1], values[2] / other[2]}; }
    
    inline vec3 operator+(float scalar) const { return {values[0] + scalar, values[1] + scalar, values[2] + scalar}; }
    inline vec3 operator-(float scalar) const { return {values[0] - scalar, values[1] - scalar, values[2] - scalar}; }
    inline vec3 operator*(float scalar) const { return {values[0] * scalar, values[1] * scalar, values[2] * scalar}; }
    inline vec3 operator/(float scalar) const { return {values[0] / scalar, values[1] / scalar, values[2] / scalar}; }
    
    inline vec3& operator+=(const vec3& other) { values[0] += other[0]; values[1] += other[1]; values[2] += other[2]; return *this; }
    inline vec3& operator-=(const vec3& other) { values[0] -= other[0]; values[1] -= other[1]; values[2] -= other[2]; return *this; }
    inline vec3& operator*=(const vec3& other) { values[0] *= other[0]; values[1] *= other[1]; values[2] *= other[2]; return *this; }
    inline vec3& operator/=(const vec3& other) { values[0] /= other[0]; values[1] /= other[1]; values[2] /= other[2]; return *this; }
    
    inline vec3& operator+=(float scalar) { values[0] += scalar; values[1] += scalar; values[2] += scalar; return *this; }
    inline vec3& operator-=(float scalar) { values[0] -= scalar; values[1] -= scalar; values[2] -= scalar; return *this; }
    inline vec3& operator*=(float scalar) { values[0] *= scalar; values[1] *= scalar; values[2] *= scalar; return *this; }
    inline vec3& operator/=(float scalar) { values[0] /= scalar; values[1] /= scalar; values[2] /= scalar; return *this; }
    
    inline bool operator==(const vec3& other) const { return values[0] == other[0] && values[1] == other[1] && values[2] == other[2]; }
    inline bool operator!=(const vec3& other) const { return !(*this == other); }
    
    inline friend float dot(const vec3& a, const vec3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
    inline friend vec3 vec_cross(const vec3& a, const vec3& b) { return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
    
    inline float length() const { return std::sqrt(dot(*this, *this)); }
    inline vec3 normalized() const { float len = length(); return len > 0 ? *this * (1.0f / len) : vec3(0.0f); }
    inline void normalize() { *this = normalized(); }
    
    inline vec3 clamped(float minVal, float maxVal) const { return {std::clamp(values[0], minVal, maxVal), std::clamp(values[1], minVal, maxVal), std::clamp(values[2], minVal, maxVal)}; }
    inline vec3 clamped(const vec3& minVec, const vec3& maxVec) const { return {std::clamp(values[0], minVec[0], maxVec[0]), std::clamp(values[1], minVec[1], maxVec[1]), std::clamp(values[2], minVec[2], maxVec[2])}; }
    
    inline bool isZero() const { return *this == vec3(0.0f); }
    inline bool isUnit() const { return std::abs(length() - 1.0f) < 1e-6f; }
    
    inline friend vec3 operator*(float scalar, const vec3& v) { return {scalar * v[0], scalar * v[1], scalar * v[2]}; }
    
    inline friend std::ostream& operator<<(std::ostream& os, const vec3& v) { return os << "vec3(" << v[0] << ", " << v[1] << ", " << v[2] << ")"; }
  };
