#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.h"
#include "sphere.h"
#include "vec3.h"

class Sphere {
public:
  Sphere(Vec3 center, float radius, Vec3 color = Vec3(1, 0, 0))
      : center_(center)
      , radius_(radius)
      , color_(color) {}

  // Returns ray intersection with the sphere using geometric methods.
  //
  // Recall, equation of a sphere with radius R is:
  //   x^2 + y^2 + z^2 = R^2
  // When the sphere is centered at a point C:
  //   (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = R^2
  // If we express this as vectors:
  //   dot(point - center, point - center) = R^2
  // Solving for any point on the ray, p(t), gives the quadratic:
  //  t^2 * dot(B, B) + 2t * dot(B, A - C) + dot(A - C, A - C) - R^2 = 0
  float intersection(Ray const& r) {
    Vec3 origin_center = r.origin_ - center_;
    float a = dot(r.direction_, r.direction_);
    float b = 2 * dot(r.direction_, origin_center);
    float c = dot(origin_center, origin_center) - (radius_ * radius_);
    float discriminant = (b * b) - (4 * a * c);

    if (discriminant > 0) {
      // Only solve for the smaller t, as this is the closest intersection.
      float t = (-b - sqrt(discriminant)) / (2.0 * a);
      if (t > 0) {
        return t;
      }
      t = (-b + sqrt(discriminant)) / (2.0 * a);
      if (t > 0) {
        return t;
      }
    }
    return -1.0;
  }

  Vec3 center_;
  float radius_;
  Vec3 color_;
};

#endif // SPHERE_H_
