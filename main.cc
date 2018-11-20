#include <iostream>
#include <random>
#include <vector>

#include "camera.h"
#include "hit_record.h"
#include "ray.h"
#include "scene.h"
#include "sphere.h"
#include "util.h"
#include "vec3.h"

const int WIDTH = 800;
const int HEIGHT = 400;
// const int WIDTH = 200;
// const int HEIGHT = 100;
const int SAMPLE = 100;

Vec3 trace(Ray const& r, Scene* world, int depth) {
  HitRecord record;

  // Handle cases where the ray intersects with a sphere.
  if (world->intersects(r, 0.0001, INFINITY, record)) {
    Ray scatter_ray;
    Vec3 attenuation;
    if (depth < 50 and
        record.material_->scatter(r, record, attenuation, scatter_ray)) {
      return attenuation * trace(scatter_ray, world, ++depth);
    }
  }

  // Otherwise provide background gradient color.
  Vec3 unit_direction = unit_vector(r.direction_);
  float t = 0.5 * (unit_direction.y() + 1.0);
  // blended_value = (1-t)*start_value + t*end_value, where t moves 0->1
  // The vector multipliers (0.5, 0.7, 1.0) will produce a light blue color.
  return ((1.0 - t) * Vec3(1.0, 1.0, 1.0)) + (t * Vec3(0.5, 0.7, 1.0));
}

// Writes raw pixel values to display a PPM image.
// https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
void render(Scene* world) {
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
        float u = float(x + randf()) / float(WIDTH);
        float v = float(y + randf()) / float(HEIGHT);
        Ray r = cam.get_ray(u, v);
        Vec3 p = r.point_at_parameter(2.0);
        color += trace(r, world, 0);
      }
      color /= float(SAMPLE);
      color = Vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
      int ir = int(255.99 * color[0]);
      int ig = int(255.99 * color[1]);
      int ib = int(255.99 * color[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}

int main() {
  std::vector<Sphere> spheres = {
      Sphere(Vec3(0.0, -100.5, -1.0), 100, new Lambertian(Vec3(0.6, 0.6, 1.0))),
      // Sphere(Vec3(0.0, 0.0, -1), 0.5, new Lambertian(Vec3(0.8, 0.8, 0.0))),
      Sphere(Vec3(-0.6, 0.3, -1.5), 0.8, new Metal(Vec3(0.8, 0.0, 0.0))),
      // Sphere(Vec3(-0.2, 0.0, -1), 0.5, new Lambertian(Vec3(0.8, 0.8, 0.0))),
      Sphere(Vec3(0.4, -0.22, -0.8), 0.23, new Lambertian(Vec3(0.0, 0.2, 0.7))),
      Sphere(Vec3(2.1, -0.0, -2), 0.5, new Lambertian(Vec3(0.8, 0.8, 0.0))),
  };
  Scene* world = new Scene(spheres);
  render(world);

  return 0;
}
