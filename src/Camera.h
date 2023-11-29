#pragma once

#include <vector>

#include "IObject.h"
#include "Vector.h"
#include "Window.h"

class Camera {
 public:
  Camera(const Vector& pos = Vector(0, 0, 0), const Vector& angle = Vector(0, 0, 0)) : pos_(pos), angle_(angle) {}


  Vector getPos() const { return pos_; }

  void setPos(const Vector& pos) { pos_ = pos; }

  Vector getAngle() const { return angle_; }

  void setAngle(const Vector& angle) { angle_ = angle; }


  void move(const Vector& shift);

  void rotate(const Vector& angle);

  void render(Window& window, const std::vector<IObject*>& objects) const;

 private:
  Vector pos_ = Vector(0, 0, 0), angle_ = Vector(0, 0, 0);

  double minDistance_ = 0.001;
  double maxDistance_ = 1000;
  size_t reflectionsLimit_ = 256;
  size_t samplesNum_ = 1;

  Vector castRay(const std::vector<IObject*>& objects, const Vector& startPos, const Vector& vec, size_t iteration = 0, size_t ignoreIndex = -1) const;
};
