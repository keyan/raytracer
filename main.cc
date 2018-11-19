#include <iostream>
#include <vector>

#include "ray.h"
#include "sphere.h"
#include "vec3.h"

const int WIDTH = 200;
const int HEIGHT = 100;

Vec3 compute_color(Ray const& r, std::vector<Sphere>& spheres) {
  for (Sphere& s : spheres) {
    if (s.intersects(r)) { return s.color_; }
  }
  Vec3 unit_direction = unit_vector(r.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  // blended_value = (1-t)*start_value + t*end_value, where t moves 0->1
  // The vector multipliers 0.5/0.7/1.0 will produce a light blue color.
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

// Writes raw pixel values to display a PPM image.
// https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
void render(std::vector<Sphere>& spheres) {
  std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);
  Vec3 origin(0.0, 0.0, 0.0);

  for (int y = HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
      float u = float(x) / float(WIDTH);
      float v = float(y) / float(HEIGHT);

      Ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));
      Vec3 color = compute_color(r, spheres);
      int ir = int(255.99 * color[0]);
      int ig = int(255.99 * color[1]);
      int ib = int(255.99 * color[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}

int main() {
  std::vector<Sphere> spheres = {
      Sphere(Vec3(1, 1, 1), 0.3, Vec3(0, 0, 1)),
      Sphere(Vec3(2, 0, 0), 0.1, Vec3(0, 1, 0)),
  };
  render(spheres);

  return 0;
}
