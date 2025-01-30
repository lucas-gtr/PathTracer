#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>

class vec2 {
public:
  float values[2];
  float& x = values[0];
  float& y = values[1];
  
  float& u = values[0];
  float& v = values[1];
  
  inline vec2() : values{0.0f, 0.0f} {}
  inline vec2(float x, float y) : values{x, y} {}
  inline explicit vec2(float scalar) : values{scalar, scalar} {}
  
  inline vec2(const vec2& other) : values{other[0], other[1]} {}
  inline vec2& operator=(const vec2& other) { values[0] = other[0]; values[1] = other[1]; return *this; }
  
  inline float& operator[](size_t i) { return values[i]; }
  inline const float& operator[](size_t i) const { return values[i]; }
  
  inline vec2 operator+() const { return *this; }
  inline vec2 operator-() const { return {-x, -y}; }
  
  inline vec2 operator+(const vec2& other) const { return {x + other[0], y + other[1]}; }
  inline vec2 operator-(const vec2& other) const { return {x - other[0], y - other[1]}; }
  inline vec2 operator*(const vec2& other) const { return {x * other[0], y * other[1]}; }
  inline vec2 operator/(const vec2& other) const { return {x / other[0], y / other[1]}; }
  
  inline vec2 operator+(float scalar) const { return {x + scalar, y + scalar}; }
  inline vec2 operator-(float scalar) const { return {x - scalar, y - scalar}; }
  inline vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
  inline vec2 operator/(float scalar) const { return {x / scalar, y / scalar}; }
  
  inline vec2& operator+=(const vec2& other) { x += other[0]; y += other[1]; return *this; }
  inline vec2& operator-=(const vec2& other) { x -= other[0]; y -= other[1]; return *this; }
  inline vec2& operator*=(const vec2& other) { x *= other[0]; y *= other[1]; return *this; }
  inline vec2& operator/=(const vec2& other) { x /= other[0]; y /= other[1]; return *this; }
  
  inline vec2& operator+=(float scalar) { x += scalar; y += scalar; return *this; }
  inline vec2& operator-=(float scalar) { x -= scalar; y -= scalar; return *this; }
  inline vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
  inline vec2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
  
  inline bool operator==(const vec2& other) const { return x == other[0] && y == other[1]; }
  inline bool operator!=(const vec2& other) const { return !(*this == other); }
  
  inline friend float dot(const vec2& a, const vec2& b) { return a[0] * b[0] + a[1] * b[1]; }
  
  inline float length() const { return std::sqrt(dot(*this, *this)); }
  inline vec2 normalized() const { float len = length(); return len > 0 ? *this * (1.0f / len) : vec2(0.0f); }
  inline void normalize() { *this = normalized(); }
  
  inline vec2 clamped(float minVal, float maxVal) const { return {std::clamp(x, minVal, maxVal), std::clamp(y, minVal, maxVal)}; }
  inline vec2 clamped(const vec2& minVec, const vec2& maxVec) const { return {std::clamp(x, minVec[0], maxVec[0]), std::clamp(y, minVec[1], maxVec[1])}; }
  
  inline bool isZero() const { return *this == vec2(0.0f); }
  inline bool isUnit() const { return std::abs(length() - 1.0f) < 1e-6f; }
  
  inline friend vec2 operator*(float scalar, const vec2& v) { return {scalar * v[0], scalar * v[1]}; }
  
  inline friend std::ostream& operator<<(std::ostream& os, const vec2& v) { return os << "vec2(" << v[0] << ", " << v[1] << ")"; }
};

