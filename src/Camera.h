#pragma once

#include <vector>

#include "IObject.h"
#include "Vector.h"
#include "Window.h"

class Camera {
 public:
  Camera(const Vector& pos = Vector(0, 0, 0), const Vector& angle = Vector(0, 0, 0)) : _pos(pos), _angle(angle) {}


  Vector getPos() const { return _pos; }

  void setPos(const Vector& pos) { _pos = pos; }

  Vector getAngle() const { return _angle; }

  void setAngle(const Vector& angle) { _angle = angle; }


  void move(const Vector& shift);

  void rotate(const Vector& angle);

  void render(Window& window, const std::vector<IObject*>& objects) const;

 private:
  Vector _pos = Vector(0, 0, 0), _angle = Vector(0, 0, 0);

  double _minDistance = 0.001;
  double _maxDistance = 1000;
  size_t _reflectionsLimit = 256;
  size_t _samplesNum = 1;

  Vector castRay(const std::vector<IObject*>& objects, const Vector& startPos, const Vector& vec, size_t iteration = 0, size_t ignoreIndex = -1) const;
};
