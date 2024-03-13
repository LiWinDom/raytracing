#include <cmath>
#include <thread>

#include "Camera.h"

void Camera::move(const Vector& shift) {
  _pos += shift;
}

void Camera::rotate(const Vector& angle) {
  _angle += angle;
}
#include <iostream>

void Camera::render(Window &window, const std::vector<IObject*> &objects) const {
  auto func = [&](const size_t threadNum, const size_t totalThreads) {
    for (uint16_t x = 0; x < window.getWidth(); ++x) {
      for (uint16_t y = 0; y < window.getHeight(); ++y) {
        if ((x * window.getHeight() + y) % totalThreads != threadNum) continue;

        Vector vec((x - window.getWidth() / 2.0) / (window.getWidth() / 2.0),
                   (y - window.getHeight() / 2.0) / (window.getWidth() / 2.0), 1);
        vec.rotate(_angle);
        vec.normalize();
        Vector color = castRay(objects, _pos, vec);

        // Gamma correction
        color.setX(std::pow(color.getX(), 1 / 2.2));
        color.setY(std::pow(color.getY(), 1 / 2.2));
        color.setZ(std::pow(color.getZ(), 1 / 2.2));

        window.setPixel(x, y, color.getX() * 255, color.getY() * 255, color.getZ() * 255);
      }
    }
  };

  size_t threadsNum = std::thread::hardware_concurrency();
  std::vector<std::thread*> threads(threadsNum, nullptr);
  for (size_t i = 0; i < threadsNum; ++i) {
    threads[i] = new std::thread(func, i, threadsNum);
  }
  for (size_t i = 0; i < threadsNum; ++i) {
    threads[i]->join();
    delete threads[i];
  }

  window.addSample();
  window.draw();
}

Vector Camera::castRay(const std::vector<IObject*> &objects, const Vector& startPos, const Vector& vec, size_t iteration, size_t ignoreIndex) const {
  if (iteration > _reflectionsLimit) return Vector(0);

  Vector cur = startPos;
  while (true) {
    double minDistance = _maxDistance;
    size_t minIndex = -1;

    // Finding nearest object
    for (size_t i = 0; i < objects.size(); ++i) {
      if (i == ignoreIndex) continue;
      double distance = objects[i]->getDistance(cur);
      if (distance < minDistance) {
        minDistance = distance;
        minIndex = i;
      }
    }

    if (minIndex == -1) {
      // If the ray is too far away
      return Vector(0);
    }

    // Moving our point
    cur += vec * minDistance;

    // Checking if we are still hitting nearest object
    if (objects[minIndex]->getDistance(cur) <= _minDistance) {
      if (objects[minIndex]->isLuminosity()) {
        return objects[minIndex]->getColor();
      }

      Vector normal = objects[minIndex]->getNormal(cur);
      Vector reflectedColor = Vector(0);

      // Casting other rays from this point
      for (size_t i = 0; i < _samplesNum; ++i) {
        Vector reflection = vec - normal * (2 * vec.dot(normal));
        Vector diffusion = normal;
        diffusion.rotate(Vector(std::rand(), std::rand(), std::rand()));
        if (diffusion.dot(normal) < 0) diffusion *= -1;

        Vector newVec = (diffusion - reflection) * objects[minIndex]->getDiffusionLevel() + reflection;
        newVec.normalize();

        reflectedColor += castRay(objects, cur, newVec, iteration + 1, minIndex);
      }
      reflectedColor /= _samplesNum;

      return objects[minIndex]->getColor() * reflectedColor;
    }
  }
}
