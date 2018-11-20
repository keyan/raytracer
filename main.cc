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

const int WIDTH = 1000;
const int HEIGHT = 500;
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

// Loop through each pixel in the scene and trace rays, average colors to
// draw final pixel color for every pixel.
//
// Lots of magic numbers here, pretty much all are due to playing around
// with positioning, blur, aperature, etc until cool images are generated.
void render(Scene* world) {
  // Setup viewing plane, this requires a lot of manual configuration to get
  // interesting scenes.
  Vec3 look_from(-2.0, 2.0, 1.0);
  Vec3 look_at(0.0, 0, -1);
  Vec3 view_up(0, 1, 0);
  float dist_to_focus = (look_from - look_at).length();
  Camera cam(
      look_from, look_at, view_up, 40, float(WIDTH) / float(HEIGHT), 0.3,
      dist_to_focus);

  // Writes raw pixel values to display a PPM image.
  // https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
  std::cout << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
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
      Sphere(Vec3(-0.6, 0.3, -1.5), 0.8, new Metal(Vec3(0.5, 0.5, 0.5), 0.05)),
      Sphere(
          Vec3(-0.26, -0.36, -0.57), 0.20,
          new Lambertian(Vec3(1.0, 0.411, 0.384))),
      Sphere(
          Vec3(0.50, -0.36, -0.27), 0.24, new Lambertian(Vec3(1.0, 0.0, 0.3))),
      Sphere(
          Vec3(2.0, 0.0, -0.4), 0.6, new Metal(Vec3(0.964, 0.596, 1.0), 0.05)),
      Sphere(Vec3(1.3, 0.0, 1.0), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5))),
  };

  // Random spheres, can't quite make this look good yet.
  //
  // for (size_t i = 0; i < 10; ++i) {
  //   Vec3 center(randf() * i * 0.4, 0.2, randf() - (i * 0.8));
  //   center -= Vec3(0, 0.4, 0);
  //   if (center.length() < 0.9) {
  //     continue;
  //   }
  //   Vec3 color(randf(), randf(), randf());
  //   float radius = std::min(randf(), float(0.2));
  //   float blur = std::min(randf(), float(0.5));
  //   spheres.emplace_back(Sphere(center, radius, new Lambertian(color)));
  // }

  Scene* world = new Scene(spheres);
  render(world);

  return 0;
}
