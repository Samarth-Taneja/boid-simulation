#include <core/math_vector.h>

namespace boidsimulation {
//Rule of 5
MathVector& MathVector::operator=(const MathVector& other_vector) {
  x_ = other_vector.x_;
  y_ = other_vector.y_;
  z_ = other_vector.z_;

  return *this;
}
MathVector::MathVector(const MathVector& other_vector) {
  x_ = other_vector.x_;
  y_ = other_vector.y_;
  z_ = other_vector.z_;
}
MathVector& MathVector::operator=(MathVector&& other_vector) {
  x_ = other_vector.x_; other_vector.x_ = 0;
  y_ = other_vector.y_; other_vector.y_ = 0;
  z_ = other_vector.z_; other_vector.z_ = 0;

  return *this;
}
MathVector::MathVector(MathVector&& other_vector) noexcept {
  x_ = other_vector.x_; other_vector.x_ = 0;
  y_ = other_vector.y_; other_vector.y_ = 0;
  z_ = other_vector.z_; other_vector.z_ = 0;
}
MathVector::~MathVector() {
  x_ = 0; y_ = 0; z_ = 0;
}

//Vector magnitude related methods
double MathVector::Length() const{
  return sqrt((x_*x_) + (y_*y_) + (z_*z_));
}
void MathVector::Normalize() {
  double magnitude = Length();
  x_ /= magnitude;
  y_ /= magnitude;
  z_ /= magnitude;
}
void MathVector::ChangeMagnitude(double magnitude) {
  Normalize();
  x_ *= magnitude; y_ *= magnitude; z_ *= magnitude;
}
void MathVector::ChangeMagnitude(const MathVector& other_vector) {
  double magnitude = other_vector.Length();
  ChangeMagnitude(magnitude);
}
void MathVector::ChangeDirection(const MathVector& other_vector) {
  double magnitude = Length();
  *this = other_vector;
  ChangeMagnitude(magnitude);
}
}