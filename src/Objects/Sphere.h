#pragma once

#include "../IObject.h"

class Sphere : public IObject {
 public:
  Sphere(const Vector& pos = Vector(0), const double radius = 1)
  : IObject(pos, Vector(0)), _radius(radius) {}


  double getDistance(const Vector& pos) const override;

  Vector getNormal(const Vector& pos) const override;

 private:
  double _radius;
};
