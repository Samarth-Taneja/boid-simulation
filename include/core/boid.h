#pragma once

#include <core/math_vector.h>
#include "cinder/gl/gl.h"
#include <vector>

namespace boidsimulation {

using boidsimulation::MathVector;

class Boid {
 public:
  Boid() = default;

  /**
   * Constructor that takes in optional position, velocity, and acceleration parameters.
   * @param position The MathVector value of position.
   * @param velocity The MathVector value of velocity.
   * @param mass The double value of mass.
   */
  Boid(const MathVector& position, const MathVector& velocity,
       const MathVector& acceleration, double size = 7, double mass = 1,
       ci::Color8u color = ci::Color8u(255,255,255)) :
        position_(position), velocity_(velocity), acceleration_(velocity),
        size_(size), mass_(mass), color_(color) {};

  /**
   * Adds current velocity to the current position.
   */
  void Update(std::vector<Boid>& flock);

  /**
   * Changes acceleration based on the 3 rules of flocking behavior.
   */
  void FlockingBehavior(std::vector<Boid>& flock);

  /**
   * @return A MathVector representing the force applied due to Separation.
   * i.e. moving away from local flockmates to not crowd them.
   */
  MathVector Separation(std::vector<Boid>& flock);
  /**
   * @return A MathVector representing the force applied due to Alignment.
   * i.e. facing the average direction of the flock.
   */
  MathVector Alignment(std::vector<Boid>& flock);
  /**
   * @return A MathVector representing the force applied due to Cohesion.
   * i.e. moving towards the center of the flock.
   */
  MathVector Cohesion(std::vector<Boid>& flock);

  /**
   * Changes acceleration based on provided force.
   * @param force Force to change the acceleration with.
   */
  void ApplyForce(const MathVector& force);

  /**
   * Negates Particle's velocity in x,y, or z axis.
   * @param axis Should be 0 if x-axis. 1 if y-axis. 2 if z-axis. 0 by default.
   */
  void WallCollide(int axis = 0);

  //Getters & Setters
  const boidsimulation::MathVector& GetPosition() const;
  const boidsimulation::MathVector& GetVelocity() const;
  const boidsimulation::MathVector& GetAcceleration() const;
  double GetMass() const;
  const ci::Color8u& GetColor() const;

  double GetSeparationScale() const;
  double GetAlignmentScale() const;
  double GetCohesionScale() const;
  void SetSeparationScale(double separationScale);
  void SetAlignmentScale(double alignmentScale);
  void SetCohesionScale(double cohesionScale);

 private:
  boidsimulation::MathVector position_;
  boidsimulation::MathVector velocity_;
  boidsimulation::MathVector acceleration_;
  double size_ = 7;
  double mass_ = 1;
  ci::Color8u color_;

  double max_speed_ = 10;
  double max_acceleration_ = 5;
  double vision_ = 35;

  double separation_scale_ = 1;
  double alignment_scale_ = 1;
  double cohesion_scale_ = 1;
};

}  // namespace idealgas
