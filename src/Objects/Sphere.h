#pragma once

#include "../Object.h"

class Sphere : public Object {
 public:
  Sphere(const Vector& pos = Vector(0), const double radius = 1)
  : Object(pos, Vector(0)), radius_(radius) {}


  double getDistance(const Vector& pos) const override;

  Vector getNormal(const Vector& pos) const override;

 private:
  double radius_;
};
