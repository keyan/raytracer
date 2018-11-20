#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "hit_record.h"
#include "ray.h"
#include "sphere.h"

class Scene {
public:
  Scene() {}
  Scene(std::vector<Sphere> spheres) { spheres_ = spheres; }

  bool intersects(Ray const& r, float t_min, float t_max, HitRecord& record) {
    HitRecord tmp_record;
    bool intersected_something = false;
    float best_t = t_max;
    for (size_t i = 0; i < spheres_.size(); ++i) {
      if (spheres_[i].intersects(r, t_min, best_t, tmp_record)) {
        intersected_something = true;
        best_t = tmp_record.t_;
        record = tmp_record;
      }
    }

    return intersected_something;
  }

  std::vector<Sphere> spheres_;
};

#endif // SCENE_H_
