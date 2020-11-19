#ifndef IDEAL_GAS_MATH_VECTOR_H

#include <math.h>

namespace boidsimulation {

class MathVector {
 public:
  double x_ = 0;
  double y_ = 0;

  MathVector() = default;
  MathVector(double x, double y) : x_(x), y_(y) {};
};

}

#define IDEAL_GAS_MATH_VECTOR_H

#endif  // IDEAL_GAS_MATH_VECTOR_H
