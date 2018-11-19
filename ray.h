#ifndef RAY
#define RAY

#include "vec3.h"

class Ray {
public:
  Ray() {}
  Ray(const Vec3& a, const Vec3& b) {
    A_ = a;
    B_ = b;
  }
  Vec3 origin() const { return A_; }
  Vec3 direction() const { return B_; }

  // We imagine a ray is a function p(t) = A + t*B, where:
  // A - is the ray's origin vector, "the eye"
  // B - is the ray's direction vector, the difference between the origin
  //     vector and the final ray position, C, on the image plane, B = (A - C).
  // t - is the "ray parameter", a fractional position along the vector B
  //
  // If A is the origin, then when  t < 0, p(t) is a position "behind" the
  // origin/eye, while when t == 1, p(t) is C.
  Vec3 point_at_parameter(float t) const { return A_ + (t * B_); }

  Vec3 A_;
  Vec3 B_;
};

#endif
