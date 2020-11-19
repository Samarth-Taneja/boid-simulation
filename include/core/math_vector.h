#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include <math.h>

namespace boidsimulation {

class MathVector {
 public:
  double x_ = 0;
  double y_ = 0;
  double z_ = 0;

  MathVector() = default;
  MathVector(double x, double y, double z) : x_(x), y_(y), z_(z) {};

  //Rule of 5
  /**
   * Copy assignment operator. Performs a deep copy.
   */
  MathVector &operator=(const MathVector&);
  /**
   * Copy constructor. Performs a deep copy.
   */
  MathVector(const MathVector&);
  /**
   * Move assignment operator.
   */
  MathVector& operator=(MathVector&&);
  /**
   * Move constructor.
   */
  MathVector(MathVector&&) noexcept;
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
};

}

#endif  //MATH_VECTOR_H
