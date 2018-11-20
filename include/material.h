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

Vec3 reflect(Vec3 const& v, Vec3 const& n) { return v - (2 * dot(v, n) * n); }

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
  Lambertian(Vec3 const& a) {
    albedo_ = a;
  }

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
  Metal(Vec3 const& a)
      : albedo_(a) {}

  virtual bool scatter(
      Ray const& in_ray,
      HitRecord const& record,
      Vec3& attenuation,
      Ray& scatter_ray) const {
    Vec3 reflected = reflect(unit_vector(in_ray.direction_), record.normal_);
    scatter_ray = Ray(record.point_, reflected);
    attenuation = albedo_;

    return (dot(scatter_ray.direction_, record.normal_) > 0);
  }

  Vec3 albedo_;
};

#endif // MATERIAL_H_
