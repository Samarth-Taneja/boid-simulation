#include <core/math_vector.h>
#include <stdexcept>

namespace boidsimulation {
void MathVector::Set(const MathVector& other) {
  x_ = other.x_; y_ = other.y_; z_ = other.z_;
}
void MathVector::Zero() {
  x_ = 0; y_ = 0; z_ = 0;
}

//Rule of 5
MathVector& MathVector::operator=(const MathVector& other) {
  Set(other);
  return *this;
}
MathVector::MathVector(const MathVector& other) {
  Set(other);
}
MathVector& MathVector::operator=(MathVector&& other) {
  Set(other);
  other.Zero();
  return *this;
}
MathVector::MathVector(MathVector&& other) noexcept {
  Set(other);
  other.Zero();
}
MathVector::~MathVector() {
  Zero();
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

double MathVector::Distance(const MathVector& other_vector) {
  MathVector temp_vector = *this - other_vector;
  return temp_vector.Length();
}

double MathVector::Angle(const MathVector& other_vector) {
  double dot_product = *this * other_vector;
  return acos(dot_product / (this->Length() * other_vector.Length()));
}

//Vector operations
double& MathVector::operator[](size_t index) {
  if(index == 0) {
    return x_;
  } else if(index == 1) {
    return y_;
  } else if(index == 2) {
    return z_;
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}
//Relational Operations
bool MathVector::operator==(const MathVector& other) {
  return (x_ == other.x_ && y_ == other.y_ && z_ == other.z_);
}
bool MathVector::operator!=(const MathVector& other) {
  return !(operator==(other));
}
//Vector addition and subtraction
MathVector& MathVector::operator+=(const MathVector& other) {
  x_ += other.x_; y_ += other.y_; z_ += other.z_;
  return *this;
}
MathVector& MathVector::operator-=(const MathVector& other) {
  x_ -= other.x_; y_ -= other.y_; z_ -= other.z_;
  return *this;
}
MathVector operator+(const MathVector& first, const MathVector& second) {
  MathVector sum(first.x_ + second.x_, first.y_ + second.y_, first.z_ + second.z_);
  return sum;
}
MathVector operator-(const MathVector& first, const MathVector& second) {
  MathVector sum(first.x_ - second.x_, first.y_ - second.y_, first.z_ - second.z_);
  return sum;
}
//Scalar multiplication and division
MathVector& MathVector::operator*=(double scalar) {
  x_ *= scalar; y_ *= scalar; z_ *= scalar;
  return *this;
}
MathVector operator*(const MathVector& vector, const double& scalar) {
  MathVector product = vector;
  product *= scalar;
  return product;
}
MathVector operator*(const double& scalar, const MathVector& vector) {
  return (operator*(vector, scalar));
}
MathVector& MathVector::operator-() {
  *this *= -1;
  return *this;
}
MathVector& MathVector::operator/=(double scalar) {
  if(scalar != 0) {
    x_ /= scalar; y_ /= scalar; z_ /= scalar;
  }
  return *this;
}
MathVector operator/(const MathVector& vector, const double& scalar) {
  MathVector quotient = vector;
  quotient /= scalar;
  return quotient;
}
//Dot and cross product
double operator*(const MathVector& first, const MathVector& second) {
  return ((first.x_ * second.x_) + (first.y_ * second.y_) + (first.z_ * second.z_));
}
MathVector operator%(const MathVector& first, const MathVector& second) {
  MathVector cross(first.y_*second.z_ - first.z_*second.y_,
                   first.z_*first.x_ - first.x_*first.z_,
                   first.x_*second.y_ - first.y_*second.x_);
  return cross;
}
}