#pragma once

#include <stdint.h>

#include "Vector.h"

class IObject {
 public:
  IObject(const Vector& pos = Vector(0, 0, 0), const Vector& angle = Vector(0, 0, 0))
  : _pos(pos), _angle(angle) {}


  Vector getPos() const { return _pos; }

  void setPos(const Vector& pos) { _pos = pos; }

  Vector getAngle() const { return _angle; }

  void setAngle(const Vector& angle) { _angle = angle; }

  bool isLuminosity() const { return _isLuminosity; }

  void setLuminosity(const bool isLuminosity) { _isLuminosity = isLuminosity; }

  Vector getColor() const { return _color; }

  uint8_t getRed() const { return _color.getX() * 255; }

  uint8_t getGreen() const { return _color.getY() * 255; }

  uint8_t getBlue() const { return _color.getZ() * 255; }

  void setColor(const Vector& color) { _color = color; }

  void setColor(const uint8_t red, const uint8_t green, const uint8_t blue) {
    setColor(Vector(red / 255.0, green / 255.0, blue / 255.0));
  }

  double getDiffusionLevel() const { return _diffusionLevel; }

  void setDiffusionLevel(const double diffusionLevel) { _diffusionLevel = diffusionLevel; }


  virtual double getDistance(const Vector& pos) const {};

  virtual Vector getNormal(const Vector& pos) const {};

 protected:
  Vector _pos, _angle;
  bool _isLuminosity = false;

  Vector _color = Vector(1, 1, 1);
  double _diffusionLevel = 0;
};
