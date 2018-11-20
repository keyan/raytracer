#ifndef CAMERA_H_
#define CAMERA_H_

#include "ray.h"
#include "vec3.h"

class Camera {
public:
  Camera() {
    origin_ = Vec3(0.0, 0.0, 0.0);
    lower_left_corner_ = Vec3(-2.0, -1.0, -1.0);
    horizontal_ = Vec3(4.0, 0.0, 0.0);
    vertical_ = Vec3(0.0, 2.0, 0.0);
  }

  Ray get_ray(float u, float v) {
    return Ray(
        origin_, lower_left_corner_ + (u * horizontal_) + (v * vertical_));
  }

  Vec3 origin_;
  Vec3 lower_left_corner_;
  Vec3 horizontal_;
  Vec3 vertical_;
};

#endif // CAMERA_H_
