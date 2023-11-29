#include <algorithm>
#include <cmath>

#include "Vector.h"

bool Vector::operator== (const Vector& other) const {
  return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
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
  return Vector(x_ + other.x_, y_ + other.y_, z_ + other.z_);
}

Vector Vector::operator- (const Vector& other) const {
  return Vector(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

Vector Vector::operator- () const {
  return Vector(-x_, -y_, -z_);
}

Vector Vector::operator* (const Vector& other) const {
  return Vector(x_ * other.x_, y_ * other.y_, z_ * other.z_);
}

Vector Vector::operator* (const double other) const {
  return operator*(Vector(other, other, other));
}

Vector Vector::operator/ (const Vector& other) const {
  return Vector(x_ / other.x_, y_ / other.y_, z_ / other.z_);
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
  return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

double Vector::dot(const Vector& other) const {
  return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

Vector Vector::abs() {
  x_ = std::abs(x_);
  y_ = std::abs(y_);
  z_ = std::abs(z_);
  return *this;
}

Vector Vector::normalize() {
  const double length = getLength();
  x_ /= length;
  y_ /= length;
  z_ /= length;
  return *this;
}

Vector Vector::rotate(const Vector& angle) {
  Vector rotX = Vector(
      x_ * std::cos(angle.y_) * std::cos(angle.z_),
      y_ * (std::sin(angle.x_) * std::sin(angle.y_) * std::cos(angle.z_) - std::cos(angle.x_) * std::sin(angle.z_)),
      z_ * (std::cos(angle.x_) * std::sin(angle.y_) * std::cos(angle.z_) + std::sin(angle.x_) * std::sin(angle.z_))
  );
  Vector rotY = Vector(
      x_ * std::cos(angle.y_) * std::sin(angle.z_),
      y_ * (std::sin(angle.x_) * std::sin(angle.y_) * std::sin(angle.z_) + std::cos(angle.x_) * std::cos(angle.z_)),
      z_ * (std::cos(angle.x_) * std::sin(angle.y_) * std::sin(angle.z_) - std::sin(angle.x_) * std::cos(angle.z_))
  );
  Vector rotZ = Vector(
      x_ * (-std::sin(angle.y_)),
      y_ * std::sin(angle.x_) * std::cos(angle.y_),
      z_ * std::cos(angle.x_) * std::cos(angle.y_)
  );

  x_ = rotX.x_ + rotX.y_ + rotX.z_;
  y_ = rotY.x_ + rotY.y_ + rotY.z_;
  z_ = rotZ.x_ + rotZ.y_ + rotZ .z_;

  return *this;
}
