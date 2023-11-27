#pragma once

#include "../Object.h"

class Cube : public Object {
 public:
  Cube(const Vector& pos = Vector(0), const Vector& size = Vector(1), const Vector& angle = Vector(0))
      : Object(pos, angle), size_(size) {}


  double getDistance(const Vector& pos) const override;

  Vector getNormal(const Vector& pos) const override;

 private:
  Vector size_;
};
