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

  /**
   * @return The magnitude of the vector
   */
  double Length();

  /**
   * Normalizes the vector. Divides each component by the magnitude.
   */
  void Normalize();

  /**
   * @return Vector component corresponding to the provided index.
   * Vector is 0-indexed.
   */
  double &operator[](const size_t index);
};

}

#endif  //MATH_VECTOR_H
