#pragma once

#include <core/math_vector.h>
#include "cinder/gl/gl.h"
#include <vector>

namespace boidsimulation {

using boidsimulation::MathVector;

class Obstacle {
 public:
  Obstacle() = default;

  /**
   * Constructor that takes in position, size, and .
   * @param position The MathVector value of position.
   * @param velocity The MathVector value of velocity.
   * @param mass The double value of mass.
   */
  Obstacle(const MathVector& position, double size = 25,
       ci::Color8u color = ci::Color8u(10,10,255)) :
        position_(position), size_(size), color_(color) { is_wall_ = false; };

  /**
   * Draws the Obstacle
   */
  void Draw() const;

  //Getters & Setters
  const boidsimulation::MathVector& GetPosition() const;
  double GetSize() const;
  const ci::Color8u& GetColor() const;

 private:
  boidsimulation::MathVector position_;
  double size_;
  ci::Color8u color_;

  bool is_wall_ = false;
};

}  // namespace idealgas
