#include "Sphere.h"

double Sphere::getDistance(const Vector &pos) const {
  return (pos - pos_).getLength() - radius_;
}

Vector Sphere::getNormal(const Vector &pos) const {
  return (pos - pos_).normalize();
}
