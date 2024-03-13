#include <algorithm>
#include <cmath>

#include "Vector.h"

bool Vector::operator== (const Vector& other) const {
  return _x == other._x && _y == other._y && _z == other._z;
}

bool Vector::operator!= (const Vector& other) const {
  return !operator==(other);
}

bool Vector::operator< (const Vector& other) const {
  return getLength() < other.getLength();
}

bool Vector::operator> (const Vector& other) const {
  return other.operator<(*this);
}

bool Vector::operator<= (const Vector& other) const {
  return !operator>(other);
}

bool Vector::operator>= (const Vector& other) const {
  return !operator<(other);
}


Vector Vector::operator+ (const Vector& other) const {
  return Vector(_x + other._x, _y + other._y, _z + other._z);
}

Vector Vector::operator- (const Vector& other) const {
  return Vector(_x - other._x, _y - other._y, _z - other._z);
}

Vector Vector::operator- () const {
  return Vector(-_x, -_y, -_z);
}

Vector Vector::operator* (const Vector& other) const {
  return Vector(_x * other._x, _y * other._y, _z * other._z);
}

Vector Vector::operator* (const double other) const {
  return operator*(Vector(other, other, other));
}

Vector Vector::operator/ (const Vector& other) const {
  return Vector(_x / other._x, _y / other._y, _z / other._z);
}

Vector Vector::operator/ (const double other) const {
  return operator/(Vector(other, other, other));
}


Vector Vector::operator+= (const Vector& other) {
  return *this = operator+(other);
}

Vector Vector::operator-= (const Vector& other) {
  return *this = operator-(other);
}

Vector Vector::operator*= (const Vector& other) {
  return *this = operator*(other);
}

Vector Vector::operator*= (const double other) {
  return *this = operator*(other);
}

Vector Vector::operator/= (const Vector& other) {
  return *this = operator/(other);
}

Vector Vector::operator/= (const double other) {
  return *this = operator/(other);
}


double Vector::getLength() const {
  return std::sqrt(_x * _x + _y * _y + _z * _z);
}

double Vector::dot(const Vector& other) const {
  return _x * other._x + _y * other._y + _z * other._z;
}

Vector Vector::abs() {
  _x = std::abs(_x);
  _y = std::abs(_y);
  _z = std::abs(_z);
  return *this;
}

Vector Vector::normalize() {
  const double length = getLength();
  _x /= length;
  _y /= length;
  _z /= length;
  return *this;
}

Vector Vector::rotate(const Vector& angle) {
  Vector rotX = Vector(
      _x * std::cos(angle._y) * std::cos(angle._z),
      _y * (std::sin(angle._x) * std::sin(angle._y) * std::cos(angle._z) - std::cos(angle._x) * std::sin(angle._z)),
      _z * (std::cos(angle._x) * std::sin(angle._y) * std::cos(angle._z) + std::sin(angle._x) * std::sin(angle._z))
  );
  Vector rotY = Vector(
      _x * std::cos(angle._y) * std::sin(angle._z),
      _y * (std::sin(angle._x) * std::sin(angle._y) * std::sin(angle._z) + std::cos(angle._x) * std::cos(angle._z)),
      _z * (std::cos(angle._x) * std::sin(angle._y) * std::sin(angle._z) - std::sin(angle._x) * std::cos(angle._z))
  );
  Vector rotZ = Vector(
      _x * (-std::sin(angle._y)),
      _y * std::sin(angle._x) * std::cos(angle._y),
      _z * std::cos(angle._x) * std::cos(angle._y)
  );

  _x = rotX._x + rotX._y + rotX._z;
  _y = rotY._x + rotY._y + rotY._z;
  _z = rotZ._x + rotZ._y + rotZ ._z;

  return *this;
}
