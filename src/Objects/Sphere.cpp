#include "Sphere.h"

double Sphere::getDistance(const Vector &pos) const {
  return (pos - _pos).getLength() - _radius;
}

Vector Sphere::getNormal(const Vector &pos) const {
  return (pos - _pos).normalize();
}
