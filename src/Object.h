#pragma once

#include <stdint.h>

#include "Vector.h"

class Object {
 public:
  Object(const Vector& pos = Vector(0, 0, 0), const Vector& angle = Vector(0, 0, 0))
  : pos_(pos), angle_(angle) {}


  Vector getPos() const { return pos_; }

  void setPos(const Vector& pos) { pos_ = pos; }

  Vector getAngle() const { return angle_; }

  void setAngle(const Vector& angle) { angle_ = angle; }

  bool isLuminosity() const { return isLuminosity_; }

  void setLuminosity(const bool isLuminosity) { isLuminosity_ = isLuminosity; }

  Vector getColor() const { return color_; }

  uint8_t getRed() const { return color_.getX() * 255; }

  uint8_t getGreen() const { return color_.getY() * 255; }

  uint8_t getBlue() const { return color_.getZ() * 255; }

  void setColor(const Vector& color) { color_ = color; }

  void setColor(const uint8_t red, const uint8_t green, const uint8_t blue) {
    setColor(Vector(red / 255.0, green / 255.0, blue / 255.0));
  }

  double getDiffusionLevel() const { return diffusionLevel_; }

  void setDiffusionLevel(const double diffusionLevel) { diffusionLevel_ = diffusionLevel; }


  virtual double getDistance(const Vector& pos) const {};

  virtual Vector getNormal(const Vector& pos) const {};

 protected:
  Vector pos_, angle_;
  bool isLuminosity_ = false;

  Vector color_ = Vector(1, 1, 1);
  double diffusionLevel_ = 0;
};
