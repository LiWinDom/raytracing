#pragma once

#include "../IObject.h"

class Cube : public IObject {
 public:
  Cube(const Vector& pos = Vector(0), const Vector& size = Vector(1), const Vector& angle = Vector(0))
      : IObject(pos, angle), _size(size) {}


  double getDistance(const Vector& pos) const override;

  Vector getNormal(const Vector& pos) const override;

 private:
  Vector _size;
};
