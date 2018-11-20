#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>
#include <math.h>
#include <stdlib.h>

// Used to represent any 3D vector, intended for colors, location, offsets, etc.
class Vec3 {
public:
  Vec3() {}
  Vec3(float e0, float e1, float e2) {
    e_[0] = e0;
    e_[1] = e1;
    e_[2] = e2;
  }

  inline float x() const { return e_[0]; }
  inline float y() const { return e_[1]; }
  inline float z() const { return e_[2]; }
  inline float r() const { return e_[0]; }
  inline float g() const { return e_[1]; }
  inline float b() const { return e_[2]; }

  inline const Vec3& operator+() const { return *this; }
  inline Vec3 operator-() const { return Vec3(-e_[0], -e_[1], -e_[2]); }
  inline float operator[](int i) const { return e_[i]; }
  inline float& operator[](int i) { return e_[i]; }

  inline Vec3& operator+=(const Vec3& v) {
    e_[0] += v.e_[0];
    e_[1] += v.e_[1];
    e_[2] += v.e_[2];
    return *this;
  }
  inline Vec3& operator-=(const Vec3& v) {
    e_[0] -= v.e_[0];
    e_[1] -= v.e_[1];
    e_[2] -= v.e_[2];
    return *this;
  }
  inline Vec3& operator*=(const float k) {
    e_[0] *= k;
    e_[1] *= k;
    e_[2] *= k;
    return *this;
  }
  inline Vec3& operator/=(const float k) {
    e_[0] /= k;
    e_[1] /= k;
    e_[2] /= k;
    return *this;
  }

  inline float length() const { return sqrt(square_length()); }
  inline float square_length() const {
    return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
  }
  inline void normalize() {
    float len = length();
    if (len > 0) {
      float k = 1.0 / length();
      e_[0] *= k;
      e_[1] *= k;
      e_[2] *= k;
    }
  }

  float e_[3];
};

inline std::istream& operator>>(std::istream& is, Vec3& t) {
  is >> t.e_[0] >> t.e_[1] >> t.e_[2];
  return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vec3& t) {
  os << t.e_[0] << " " << t.e_[1] << " " << t.e_[2];
  return os;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.e_[0] + v2.e_[0], v1.e_[1] + v2.e_[1], v1.e_[2] + v2.e_[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.e_[0] - v2.e_[0], v1.e_[1] - v2.e_[1], v1.e_[2] - v2.e_[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.e_[0] * v2.e_[0], v1.e_[1] * v2.e_[1], v1.e_[2] * v2.e_[2]);
}

inline Vec3 operator*(float t, const Vec3& v) {
  return Vec3(v.e_[0] * t, v.e_[1] * t, v.e_[2] * t);
}

inline Vec3 operator*(const Vec3& v, float t) {
  return Vec3(v.e_[0] * t, v.e_[1] * t, v.e_[2] * t);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.e_[0] / v2.e_[0], v1.e_[1] / v2.e_[1], v1.e_[2] / v2.e_[2]);
}

inline Vec3 operator/(const Vec3& v, float t) {
  return Vec3(v.e_[0] / t, v.e_[1] / t, v.e_[2] / t);
}

// Dot product of two vectors can be defined as a scalar given by:
// a . b = (a1*b1 + a2*b2 + a3*b3)
inline float dot(const Vec3& v1, const Vec3& v2) {
  return (v1.e_[0] * v2.e_[0]) + (v1.e_[1] * v2.e_[1]) + (v1.e_[2] * v2.e_[2]);
}

// Cross product of two vectors can be defined as a vector given by:
// a x b = (a2*b3 - a3*b2, a3*b1 - a1*b3, a1*b2 - a2*b1)
inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
  return Vec3(
      (v1.e_[1] * v2.e_[2] - v1.e_[2] * v2.e_[1]),
      (v1.e_[2] * v2.e_[0] - v1.e_[0] * v2.e_[2]),
      (v1.e_[0] * v2.e_[1] - v1.e_[1] * v2.e_[0]));
}

inline Vec3 unit_vector(Vec3 v) { return v / v.length(); }

#endif // VEC3_H_
