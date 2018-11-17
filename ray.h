#ifndef RAY
#define RAY

#include "vec3.h"

// We imagine a ray is a function p(t) = A + t*B, where:
// A -- is the ray's origin
// B -- is the ray's direction
// t -- is the "ray parameter"
class Ray {
public:
  ray() {}
  ray(const Vec3& a, const Vec3& b) {
    A_ = a;
    B_ = b;
  }
  Vec3 origin() const { return A_; }
  Vec3 direction() const { return B_; }
  Vec3 point_at_parameter(float t) const { return A_ + (t * B_); }

  Vec3 A_;
  Vec3 B_;
};

#endif
