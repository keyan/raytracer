#include "ray.h"
#include "vec3.h"
#include <iostream>

Vec3 color(const ray& r) {
  Vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  // blended_value = (1-t)*start_value + t*end_value, where t moves 0->1
  // The vector multipliers 0.5/0.7/1.0 will produce a light blue color.
  return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
}

// Writes raw pixel values to display a PPM image.
// https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
int main() {
  int width = 200;
  int height = 100;
  std::cout << "P3\n" << width << " " << height << "\n255\n";
  for (int j = height - 1; j >= 0; j--) {
    for (int i = 0; i < width; i++) {
      Vec3 color(float(i) / float(width), float(j) / float(height), 0.2);
      int ir = int(255.99 * color[0]);
      int ig = int(255.99 * color[1]);
      int ib = int(255.99 * color[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
