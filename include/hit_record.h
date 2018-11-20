#ifndef HIT_RECORD_H_
#define HIT_RECORD_H_

class Material;

struct HitRecord {
  float t_;
  Vec3 point_;
  Vec3 normal_;
  Material* material_;
};

#endif // HIT_RECORD_H_
