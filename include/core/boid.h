#pragma once

#include <core/math_vector.h>
#include <core/obstacle.h>
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
       double size = 10, double vision = 50, double max_speed = 8,
       ci::Color8u color = ci::Color8u(255,255,255)) :
        position_(position), velocity_(velocity),
        size_(size), vision_(vision), max_speed_(max_speed), color_(color) {};

  /**
   * Adds current velocity to the current position.
   */
  void Update(std::vector<Boid>& flock, std::vector<Boid>& preds,
              std::vector<Obstacle>& obstacles);

  /**
   * Returns velocity change vector based on the 3 rules of flocking behavior.
   */
  MathVector FlockingBehavior(std::vector<Boid>& flock, std::vector<Boid>& preds);

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
   * @return A MathVector representing the force applied to a Predator Boid in
   * order to chase prey or prey boid to run away from Predators.
   */
  MathVector Chase(std::vector<Boid>& flock);

  /**
   * Negates Particle's velocity in x,y, or z axis.
   * @param axis Should be 0 if x-axis. 1 if y-axis. 2 if z-axis. 0 by default.
   */
  void WallCollide(int axis = 0);

  /**
   * Draws the Boid
   */
  void Draw() const;

  //Getters & Setters
  const boidsimulation::MathVector& GetPosition() const;
  const boidsimulation::MathVector& GetVelocity() const;
  double GetSize() const;
  const ci::Color8u& GetColor() const;
  const bool IsPredator() const;

  double GetSeparationScale() const;
  double GetAlignmentScale() const;
  double GetCohesionScale() const;
  double GetChaseScale() const;
  void SetSeparationScale(double separation_scale);
  void SetAlignmentScale(double alignment_scale);
  void SetCohesionScale(double cohesion_scale);
  void SetChaseScale(double chase_scale);

 private:
  boidsimulation::MathVector position_;
  boidsimulation::MathVector velocity_;
  double size_;
  ci::Color8u color_;

  double max_speed_;
  double vision_;

  bool predator_ = false;

  double separation_scale_ = 1;
  double alignment_scale_ = 1;
  double cohesion_scale_ = 1;
  double chase_scale_ = 30; //affects predator and prey movement
};

}  // namespace idealgas
