#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <math.h>

namespace boidsimulation {

class MathVector {
 public:
  double x_ = 0, y_ = 0, z_ = 0;

  MathVector() = default;
  MathVector(double x, double y, double z) : x_(x), y_(y), z_(z) {};

  void Set(const MathVector& other);
  void Zero();

  //Rule of 5
  /**
   * Copy assignment operator. Performs a deep copy.
   */
  MathVector &operator=(const MathVector& other);
  /**
   * Copy constructor. Performs a deep copy.
   */
  MathVector(const MathVector& other);
  /**
   * Move assignment operator.
   */
  MathVector& operator=(MathVector&& other);
  /**
   * Move constructor.
   */
  MathVector(MathVector&& other) noexcept;
  /**
   * Destructor.
   */
  ~MathVector();

  //Vector magnitude related methods
  /**
   * @return The magnitude of the vector
   */
  double Length() const;
  /**
   * Normalizes the vector. Divides each component by the magnitude.
   */
  void Normalize();
  /**
   * Changes the magnitude of the vector to the provided value while keeping the
   * direction the same.
   * @param magnitude The new magnitude of the vector.
   */
  void ChangeMagnitude(double magnitude);
  /**
   * Copies the magnitude of the provided vector while keeping the direction the
   * same.
   * @param other_vector The vector to copy the magnitude from.
   */
  void ChangeMagnitude(const MathVector& other_vector);
  /**
   * Copies the direction of the provided vector while keeping the magnitude the
   * same.
   * @param other_vector The vector to copy the direction from.
   */
  void ChangeDirection(const MathVector& other_vector);

  //Operator Overloads
  /**
   * @return Vector component corresponding to the provided index.
   * Vector is 0-indexed.
   */
  double &operator[](size_t index);
  //Equality operator
  bool operator==(const MathVector& other);
  //Inequality operator
  bool operator!=(const MathVector& other);

  //Addition and Subtraction
  /**
   * Vector addition and assignment.
   * Adds components of other to the current MathVector.
   * @param other MathVector to add to the current MathVector.
   */
  MathVector& operator+=(const MathVector& other);
  /**
   * Vector subtraction and assignment.
   * Subtracts components of other from the current MathVector.
   * @param other MathVector to subtract from the current MathVector.
   */
  MathVector& operator-=(const MathVector& other);
  /**
   * Vector addition. Adds components of first and second.
   */
  friend MathVector operator+(const MathVector& first, const MathVector& second);
  /**
   * Vector subtraction. Subtracts components of second from first.
   */
  friend MathVector operator-(const MathVector& first, const MathVector& second);

  //Scalar multiplication and division
  /**
   * Scalar multiplication and assignment.
   * @param scalar Scalar value to multiply the MathVector by.
   */
  MathVector& operator*=(double scalar);
  /**
   * Scalar Multiplication.
   * @param scalar Scalar value to multiply the MathVector by.
   * @param vector MathVector to be multiplied by the scalar.
   */
  friend MathVector operator*(const double& scalar, const MathVector& vector);
  /**
   * Scalar Multiplication.
   * @param vector MathVector to be multiplied by the scalar.
   * @param scalar Scalar value to multiply the MathVector by.
   */
  friend MathVector operator*(const MathVector& vector, const double& scalar);
  //Negates components.
  MathVector& operator-();
  /**
   * Scalar division and assignment.
   * @param scalar Scalar value to divide the MathVector by.
   */
  MathVector& operator/=(double scalar);
  /**
   * Scalar Division.
   * @param vector MathVector to be divided by the scalar.
   * @param scalar Scalar value to divide the MathVector by.
   */
  friend MathVector operator/(const MathVector& vector, const double& scalar);

  //Dot and Cross product
  /**
   * Dot product. Sum of products of components of first and second.
   */
  friend double operator*(const MathVector& first, const MathVector& second);
  /**
   * Cross product.
   */
  friend MathVector operator%(const MathVector& first, const MathVector& second);
};

}

#endif  //MATH_VECTOR_H
