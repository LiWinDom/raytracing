#pragma once

class Vector {
 public:
  Vector(const double x, const double y, const double z) : x_(x), y_(y), z_(z) {}

  Vector(const double num) : Vector(num, num, num) {}


  double getX() const { return x_; }

  void setX(const double x) { x_ = x; }

  double getY() const { return y_; }

  void setY(const double y) { y_ = y; }

  double getZ() const { return z_; }

  void setZ(const double z) { z_ = z; }


  bool operator== (const Vector& other) const;

  bool operator!= (const Vector& other) const;

  bool operator< (const Vector& other) const;

  bool operator> (const Vector& other) const;

  bool operator<= (const Vector& other) const;

  bool operator>= (const Vector& other) const;


  Vector operator+ (const Vector& other) const;

  Vector operator- (const Vector& other) const;

  Vector operator- () const;

  Vector operator* (const Vector& other) const;

  Vector operator* (const double other) const;

  Vector operator/ (const Vector& other) const;

  Vector operator/ (const double other) const;


  Vector operator+= (const Vector& other);

  Vector operator-= (const Vector& other);

  Vector operator*= (const Vector& other);

  Vector operator*= (const double other);

  Vector operator/= (const Vector& other);

  Vector operator/= (const double other);



  double getLength() const;

  double dot(const Vector& other) const;

  Vector abs();

  Vector normalize();

  Vector rotate(const Vector& angle);

 private:
  double x_, y_, z_;
};
