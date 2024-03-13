#pragma once

class Vector {
 public:
  Vector(const double x, const double y, const double z) : _x(x), _y(y), _z(z) {}

  Vector(const double num) : Vector(num, num, num) {}


  double getX() const { return _x; }

  void setX(const double x) { _x = x; }

  double getY() const { return _y; }

  void setY(const double y) { _y = y; }

  double getZ() const { return _z; }

  void setZ(const double z) { _z = z; }


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
  double _x, _y, _z;
};
