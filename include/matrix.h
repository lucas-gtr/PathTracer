#pragma once

#include <array>
#include <iostream>
#include <iomanip>

#include "vec3.h"

template <size_t Rows, size_t Cols = Rows>
class mat {
public:
  std::array<float, Rows * Cols> values;
  
  mat(float value = 1.0f) {
    values.fill(0.0f);
    for (size_t i = 0; i < Rows && i < Cols; ++i) {
      values[i * Cols + i] = value;
    }
  }
  
  mat(const std::array<vec<Cols>, Rows>& vecs) {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        values[i * Cols + j] = vecs[i][j];
      }
    }
  }
  
  float& operator()(size_t row, size_t col) { return values[row * Cols + col]; }
  const float& operator()(size_t row, size_t col) const { return values[row * Cols + col]; }
  
  mat operator+(const mat& other) const {
    mat result;
    for (size_t i = 0; i < Rows * Cols; ++i) {
      result.values[i] = values[i] + other.values[i];
    }
    return result;
  }
  
  mat& operator+=(const mat& other) {
    for (size_t i = 0; i < Rows * Cols; ++i) {
      values[i] += other.values[i];
    }
    return *this;
  }
  
  mat operator-(const mat& other) const {
    mat result;
    for (size_t i = 0; i < Rows * Cols; ++i) {
      result.values[i] = values[i] - other.values[i];
    }
    return result;
  }
  
  mat& operator-=(const mat& other) {
    for (size_t i = 0; i < Rows * Cols; ++i) {
      values[i] -= other.values[i];
    }
    return *this;
  }
  
  mat operator*(const mat<Cols, Rows>& other) const {
    mat<Rows, Rows> result(0.0f);
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Rows; ++j) {
        for (size_t k = 0; k < Cols; ++k) {
          result(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    return result;
  }
  
  mat& operator*=(const mat<Cols, Rows>& other) {
    *this = *this * other;
    return *this;
  }
  
  typedef vec<Rows> vecN;
  
  vec<Rows> operator*(const vec<Cols>& vec) const {
    vecN result(0.0f);
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        result[i] += (*this)(i, j) * vec[j];
      }
    }
    return result;
  }
  
  mat operator*(float scalar) const {
    mat result;
    for (size_t i = 0; i < Rows * Cols; ++i) {
      result.values[i] = values[i] * scalar;
    }
    return result;
  }
  
  mat& operator*=(float scalar) {
    for (size_t i = 0; i < Rows * Cols; ++i) {
      values[i] *= scalar;
    }
    return *this;
  }
  
  mat<Cols, Rows> transpose() const {
    mat<Cols, Rows> mat_transpose;
    for(size_t i = 0; i < Rows; i++){
      for(size_t j = 0; j < Cols; j++){
        mat_transpose(j, i) = (*this)(i, j);
      }
    }
    
    return mat_transpose;
  }
  
  operator const float*() const {
    return values.data();
  }
  
  operator float*() {
    return values.data();
  }
  
  template <size_t NewRows, size_t NewCols>
  operator mat<NewRows, NewCols>() const {
    mat<NewRows, NewCols> result(1.0f); 
    
    for (size_t i = 0; i < std::min(Rows, NewRows); ++i) {
      for (size_t j = 0; j < std::min(Cols, NewCols); ++j) {
        result(i, j) = (*this)(i, j);
      }
    }
    
    if (NewRows > Rows || NewCols > Cols) {
      for (size_t i = Rows; i < NewRows && i < NewCols; ++i) {
        result(i, i) = 1.0f;
      }
    }
    
    return result;
  }
  
  void print(std::ostream& os = std::cout) const {
    os << "mat" << Rows << "x" << Cols << "(\n";
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t j = 0; j < Cols; ++j) {
        os << std::setw(7) << std::setprecision(4) << (*this)(i, j) << " ";
      }
      os << "\n";
    }
    os << ")\n";
  }
  
  void swapLine(mat& matToSwap, size_t l1, size_t l2){
    float temp;
    for(int i = 0; i < Rows; i++){
      temp = matToSwap(l1, i);
      matToSwap(l1, i) = matToSwap(l2, i);
      matToSwap(l2, i) = temp;
    }
  }
  
  template <typename T = mat>
  typename std::enable_if<(Rows == Cols), T>::type
  invert() {
    mat augmented = *this;
    mat result;
    
    for (size_t i = 0; i < Rows; ++i) {
      float pivot = augmented(i, i);
      
      if (pivot == 0) {
        bool found = false;
        for (size_t m = i + 1; m < Rows; ++m) {
          if (augmented(m, i) != 0) {
            swapLine(augmented, i, m);
            swapLine(result, i, m);
            pivot = augmented(i, i);
            found = true;
            break;
          }
        }
        if (!found) throw std::runtime_error("Matrice non inversible");
      }
      
      for (size_t j = 0; j < Rows; ++j) {
        augmented(i, j) /= pivot;
        result(i, j) /= pivot;
      }
      
      for (size_t j = i + 1; j < Rows; ++j) {
        float factor = augmented(j, i);
        for (size_t k = 0; k < Rows; ++k) {
          augmented(j, k) -= factor * augmented(i, k);
          result(j, k) -= factor * result(i, k);
        }
      }
    }
    
    for (size_t i = Rows - 1; i < Rows; --i) { // Décomptage
      for (size_t j = 0; j < i; ++j) {
        float factor = augmented(j, i);
        for (size_t k = 0; k < Rows; ++k) {
          augmented(j, k) -= factor * augmented(i, k);
          result(j, k) -= factor * result(i, k);
        }
      }
    }
    
    return result;
  }
  
  
  template <typename T = mat>
  typename std::enable_if<(Rows == 4 && Cols == 4), T>::type
  translate(const vec3& vector) {
    mat translateMatrix(1.0f);
    
    for (size_t i = 0; i < 3; ++i) {
      translateMatrix(i, 3) = vector[i];
    }
    
    *this *= translateMatrix;
    
    return *this;
  }
  
  template <typename T = mat>
  typename std::enable_if<(Rows == 4 && Cols == 4), T>::type
  rotate(const vec3& vector) {
    float alpha = vector[0] * M_PI / 180.0f;
    float beta = vector[1] * M_PI / 180.0f;
    float gamma = vector[2] * M_PI / 180.0f;
    
    float cosAlpha = cos(alpha), sinAlpha = sin(alpha);
    float cosBeta = cos(beta), sinBeta = sin(beta);
    float cosGamma = cos(gamma), sinGamma = sin(gamma);
    
    mat rotationMatrix(1.0f);
    rotationMatrix(0, 0) = cosGamma * cosBeta;
    rotationMatrix(0, 1) = cosGamma * sinBeta * sinAlpha - sinGamma * cosAlpha;
    rotationMatrix(0, 2) = cosGamma * sinBeta * cosAlpha + sinGamma * sinAlpha;
    
    rotationMatrix(1, 0) = sinGamma * cosBeta;
    rotationMatrix(1, 1) = sinGamma * sinBeta * sinAlpha + cosGamma * cosAlpha;
    rotationMatrix(1, 2) = sinGamma * sinBeta * cosAlpha - cosGamma * sinAlpha;
    
    rotationMatrix(2, 0) = -sinBeta;
    rotationMatrix(2, 1) = cosBeta * sinAlpha;
    rotationMatrix(2, 2) = cosBeta * cosAlpha;
    
    *this = (*this) * rotationMatrix;
    
    return *this;
  }
  
  template <typename T = mat>
  typename std::enable_if<(Rows == 4 && Cols == 4), T>::type
  scale(const vec3& vector) {
    for (size_t i = 0; i < 3; ++i) {
      (*this)(i, i) *= vector[i];
    }
    return *this;
  }
  
  template <typename T = mat>
  typename std::enable_if<(Rows == 4 && Cols == 4), T>::type
  scale(const float scaleValue) {
    for (size_t i = 0; i < 3; ++i) {
      (*this)(i, i) *= scaleValue;
    }
    return *this;
  }
  
};

template <size_t Rows, size_t Cols = Rows>
std::ostream& operator<<(std::ostream& os, const mat<Rows, Cols>& mat) {
  os << "mat" << Rows << "x" << Cols << "(\n";
  for (size_t i = 0; i < Rows; ++i) {
    for (size_t j = 0; j < Cols; ++j) {
      os << std::setw(7) << std::setprecision(4) << (mat)(i, j) << " ";
    }
    os << "\n";
  }
  return os << ")\n";
}

using mat2 = mat<2>;
using mat3 = mat<3>;
using mat4 = mat<4>;
