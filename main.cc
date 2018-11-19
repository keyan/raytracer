#include <iostream>
#include <random>
#include <vector>

#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

const int WIDTH = 200;
const int HEIGHT = 100;
const int SAMPLE = 100;

Vec3 trace(Ray const& r, std::vector<Sphere>& spheres) {
  float t;

  // Handle cases where the ray intersects with a sphere.
  float min_t = INFINITY;
  const Sphere* closest = nullptr;
  for (size_t i = 0; i < spheres.size(); ++i) {
    Sphere* s = &spheres.at(i);
    t = s->intersection(r);
    if (t > 0 and t < min_t) {
      min_t = t;
      closest = s;
    }
  }
  if (closest) {
    Vec3 normal = unit_vector(r.point_at_parameter(t) - closest->center_);
    // Normal has xyz components between -1 -> 1, remap to 0 -> 1
    return 0.5 * Vec3(normal.x() + 1, normal.y() + 1, normal.z() + 1);
  }

  // Otherwise provide background gradient color.
  Vec3 unit_direction = unit_vector(r.direction_);
  t = 0.5 * (unit_direction.y() + 1.0);
  // blended_value = (1-t)*start_value + t*end_value, where t moves 0->1
  // The vector multipliers (0.5, 0.7, 1.0) will produce a light blue color.
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

// Writes raw pixel values to display a PPM image.
// https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
void render(std::vector<Sphere>& spheres) {
  // Obtain a seed for the random number engine
  std::random_device rd;
  std::mt19937 gen(rd());
  // Random real distribution over [a, b)
  std::uniform_real_distribution<> dis(0, 1.0);

  std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
  Camera cam;
  for (int y = HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
      Vec3 color(0, 0, 0);
      // Antialiasing
      // Sample some number of locations near the pixel, and average the colors
      // to get the color for each pixel. This blends edges to include some
      // amount of foreground and background.
      for (size_t s = 0; s < SAMPLE; ++s) {
        float u = float(x + dis(gen)) / float(WIDTH);
        float v = float(y + dis(gen)) / float(HEIGHT);
        Ray r = cam.get_ray(u, v);
        Vec3 p = r.point_at_parameter(2.0);
        color += trace(r, spheres);
      }
      color /= float(SAMPLE);
      int ir = int(255.99 * color[0]);
      int ig = int(255.99 * color[1]);
      int ib = int(255.99 * color[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}

int main() {
  std::vector<Sphere> spheres = {
      Sphere(Vec3(0, -100.5, -1), 100),
      Sphere(Vec3(0, 0, -1), 0.5),
  };
  render(spheres);

  return 0;
}
