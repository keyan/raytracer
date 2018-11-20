#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"
#include "util.h"
#include "vec3.h"

Vec3 rand_point_in_unit_disk() {
  Vec3 point;
  do {
    point = 2.0 * Vec3(randf(), randf(), randf()) - Vec3(1, 1, 0);
  } while (dot(point, point) >= 1.0);
  return point;
}

class Camera {
public:
  Camera(
      Vec3 look_from,
      Vec3 look_at,
      Vec3 view_up,
      float vertical_field_of_view,
      float aspect,
      float aperture,
      float focus_dist) {
    // Convert to radians.
    lens_radius_ = aperture / 2.0;
    float theta = vertical_field_of_view * (M_PI / 180);
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    origin_ = look_from;
    // Construct an orthonormal basis of the camera viewing position.
    w_ = unit_vector(look_from - look_at);
    u_ = unit_vector(cross(view_up, w_));
    // w and u are already unit vectors, so cross product is unit length too.
    v_ = cross(w_, u_);
    // lower_left_corner_ = Vec3(-half_width, -half_height, -1.0);
    lower_left_corner_ = origin_ - (half_width * u_ * focus_dist) -
                         (half_height * v_ * focus_dist) - w_ * focus_dist;
    horizontal_ = 2 * half_width * focus_dist * u_;
    vertical_ = 2 * half_height * focus_dist * v_;
  }

  Ray get_ray(float s, float t) {
    Vec3 direction = lens_radius_ * rand_point_in_unit_disk();
    Vec3 offset = (u_ * direction.x()) + (v_ * direction.y());
    return Ray(
        origin_ + offset, lower_left_corner_ + (s * horizontal_) +
                              (t * vertical_) - origin_ - offset);
  }

  Vec3 origin_;
  Vec3 lower_left_corner_;
  Vec3 horizontal_;
  Vec3 vertical_;
  float lens_radius_;
  Vec3 u_, v_, w_;
};

#endif // CAMERA_H_
