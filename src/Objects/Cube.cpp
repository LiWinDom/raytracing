#include <algorithm>
#include <cmath>

#include "Cube.h"

double Cube::getDistance(const Vector &pos) const {
  Vector newPos = (pos - _pos).rotate(-_angle).abs();
  newPos -= _size / 2;

  if (newPos.getX() < 0) {
    if (newPos.getY() < 0) {
      if (newPos.getZ() < 0) {
        return std::max(std::max(newPos.getX(), newPos.getY()), newPos.getZ());
      }
      return newPos.getZ();
    }
    if (newPos.getZ() < 0) {
      return newPos.getY();
    }
    newPos.setX(0);
    return newPos.getLength();
  }
  if (newPos.getY() < 0) {
    if (newPos.getZ() < 0) {
      return newPos.getX();
    }
    newPos.setY(0);
    return newPos.getLength();
  }
  if (newPos.getZ() < 0) {
    newPos.setZ(0);
    return newPos.getLength();
  }
  return newPos.getLength();
}

Vector Cube::getNormal(const Vector &pos) const {
  Vector newPos = (pos - _pos).rotate(-_angle);
  Vector absPos = newPos;
  absPos = absPos.abs() - _size / 2;
  absPos.abs();

  if (absPos.getX() < absPos.getY() && absPos.getX() < absPos.getZ()) {
    if (newPos.getX() < 0) {
      return Vector(-1, 0, 0).rotate(_angle);
    }
    return Vector(1, 0, 0).rotate(_angle);
  }
  if (absPos.getY() < absPos.getZ()) {
    if (newPos.getY() < 0) {
      return Vector(0, -1, 0).rotate(_angle);
    }
    return Vector(0, 1, 0).rotate(_angle);
  }
  if (newPos.getZ() < 0) {
    return Vector(0, 0, -1).rotate(_angle);
  }
  return Vector(0, 0, 1).rotate(_angle);
}
