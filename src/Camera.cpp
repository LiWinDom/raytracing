#include <math.h>
#include <thread>

#include "Camera.h"

void Camera::move(const Vector& shift) {
  pos_ += shift;
}

void Camera::rotate(const Vector& angle) {
  angle_ += angle;
}

void Camera::render(Window &window, const std::vector<Object*> &objects) const {
  auto func = [&](const size_t threadNum, const size_t totalThreads) {
    for (uint16_t x = 0; x < window.getWidth(); ++x) {
      for (uint16_t y = 0; y < window.getHeight(); ++y) {
        if ((x * window.getHeight() + y) % totalThreads != threadNum) continue;

        Vector vec((x - window.getWidth() / 2.0) / (window.getWidth() / 2.0),
                   (y - window.getHeight() / 2.0) / (window.getWidth() / 2.0), 1);
        vec.rotate(angle_);
        vec.normalize();
        Vector color = castRay(objects, pos_, vec);

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

Vector Camera::castRay(const std::vector<Object*> &objects, const Vector& startPos, const Vector& vec, size_t iteration, size_t ignoreIndex) const {
  if (iteration > reflectionsLimit_) return Vector(0);

  Vector cur = startPos;
  while (true) {
    double minDistance = maxDistance_;
    size_t minIndex = -1;

    for (size_t i = 0; i < objects.size(); ++i) {
      if (i == ignoreIndex) continue;
      double distance = objects[i]->getDistance(cur);
      if (distance < minDistance) {
        minDistance = distance;
        minIndex = i;
      }
    }

    if (minIndex == -1) {
      return Vector(0);
    }

    if (minDistance <= minDistance_) {
      if (objects[minIndex]->isLuminosity()) {
        return objects[minIndex]->getColor();
      }

      Vector normal = objects[minIndex]->getNormal(cur);
      Vector reflectedColor = Vector(0);

      for (size_t i = 0; i < samplesNum_; ++i) {
        Vector reflection = vec - normal * (2 * vec.dot(normal));
        Vector diffusion = Vector(normal).rotate(Vector(std::rand(), std::rand(), std::rand()));
        if (diffusion.dot(normal) < 0) diffusion *= -1;

        reflection = (diffusion - reflection) * objects[minIndex]->getDiffusionLevel() + reflection;
        reflection.normalize();

        reflectedColor += castRay(objects, cur, reflection, iteration + 1, minIndex);
      }
      reflectedColor /= samplesNum_;

      return objects[minIndex]->getColor() * reflectedColor;
    }

    cur += vec * minDistance;
  }
}
