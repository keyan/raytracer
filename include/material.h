#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "hit_record.h"
#include "util.h"
#include "vec3.h"

// Pick random point in a unit square until it also lies in the unit sphere.
//
// Recall that radius of the unit sphere is 1, so R^2 = 1, therefore if the
// square_length of p is <= 1 then it lies within the unit sphere.
Vec3 rand_point_in_unit_sphere() {
  Vec3 point;
  do {
    // Randf will give a vector betwen (0, 0, 0) -> (1, 1, 1), instead remap
    // to (-1, -1, -1) -> (1, 1, 1).
    point = (2.0 * Vec3(randf(), randf(), randf())) - Vec3(1, 1, 1);
  } while (point.square_length() >= 1.0);

  return point;
}

// Compute specular reflection of a incident vector off a surface.
//
// The reflection R has the same angle (theta) as the incident vector V (with
// respect to the normal N). Given this visualization:
//
//                 \ V    N    ^ R
//                  \    |    /
//                   \   |   /
//                    \  |  /
//                     v | /
//                 ------x---------
//
// We can calculate the direction of R by finding a vector in the direction of
// N, then adding V, so R = (k * N) + V
//
// First we find the magnitude of V onto N:
//
//    dot(V, N) = ||V|| ||N|| cos(theta)
//
// V and N are unit vectors so ||V|| * ||N|| = 1, thus:
//
//    dot(V, N) = cos(theta) = ||Projection of V on N||
//
// Now scale N by that scalar magnitude to get a vector B, B = dot(V, N) * N
//
// B needs to be double the length, and is also pointing the wrong direction:
//
//    R = -1 * (2 * B) + V
//    R = V - (2 * B)
Vec3 reflect(Vec3 const& V, Vec3 const& N) { return V - (2 * dot(V, N) * N); }

class Material {
public:
  virtual bool scatter(
      Ray const& in_ray,
      HitRecord const& record,
      Vec3& attenuation,
      Ray& scatter_ray) const = 0;
};

// Diffuse reflection, gives "matte" appearance.
class Lambertian : public Material {
public:
  Lambertian(Vec3 const& a) { albedo_ = a; }

  // Diffuse reflections scatter randomly.
  virtual bool scatter(
      Ray const& in_ray,
      HitRecord const& record,
      Vec3& attenuation,
      Ray& scatter_ray) const {
    // Normal has xyz components between -1 -> 1, remap to 0 -> 1
    Vec3 target = record.point_ + record.normal_ + rand_point_in_unit_sphere();
    // Create a ray from the incident point towards the new target, subtracting
    // the original point removes the component of the vector from the camera
    // (or other origin) so only the incident point to the target is considered.
    scatter_ray = Ray(record.point_, target - record.point_);
    attenuation = albedo_;
    return true;
  }

  // Proportion of incident light that is reflected by the surface.
  Vec3 albedo_;
};

class Metal : public Material {
public:
  Metal(Vec3 const& a, float fuzz)
      : albedo_(a) {
    fuzz_ = std::min(fuzz, float(1.0));
  }

  virtual bool scatter(
      Ray const& in_ray,
      HitRecord const& record,
      Vec3& attenuation,
      Ray& scatter_ray) const {
    Vec3 reflected = reflect(unit_vector(in_ray.direction_), record.normal_);
    scatter_ray =
        Ray(record.point_, reflected + fuzz_ * rand_point_in_unit_sphere());
    attenuation = albedo_;

    return (dot(scatter_ray.direction_, record.normal_) > 0);
  }

  Vec3 albedo_;
  float fuzz_;
};

#endif // MATERIAL_H_
