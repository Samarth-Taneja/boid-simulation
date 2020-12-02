#include <core/boid.h>

namespace boidsimulation {

void Boid::ApplyForce(const MathVector& force) {
  MathVector acceleration = force / mass_;
  acceleration_ += acceleration;
}

void Boid::Update(std::vector<Boid>& flock) {
  acceleration_ *= 0;
  FlockingBehavior(flock);
  velocity_ += acceleration_;
  if(velocity_.Length() > max_speed_) {
    velocity_.ChangeMagnitude(max_speed_);
  }
  position_ += velocity_;
}

void Boid::FlockingBehavior(std::vector<Boid>& flock) {
  ApplyForce(separation_scale_ * Separation(flock));
  ApplyForce(alignment_scale_ * Alignment(flock));
  ApplyForce(cohesion_scale_ * Cohesion(flock));
}
MathVector Boid::Separation(std::vector<Boid>& flock) {
  MathVector temp;
  return temp;
}
MathVector Boid::Alignment(std::vector<Boid>& flock) {
  MathVector temp;
  return temp;
}
MathVector Boid::Cohesion(std::vector<Boid>& flock) {
  MathVector temp;
  return temp;
}

void Boid::WallCollide(int axis) {
  if(axis == 0) {
    velocity_.x_ = -velocity_.x_;
  } else if (axis == 1) {
    velocity_.y_ = -velocity_.y_;
  } else if (axis == 2) {
    velocity_.z_ = -velocity_.z_;
  }
}

//Getters & Setters
const MathVector& Boid::GetPosition() const {
  return position_;
}
const MathVector& Boid::GetVelocity() const {
  return velocity_;
}
const MathVector& Boid::GetAcceleration() const {
  return acceleration_;
}
double Boid::GetMass() const {
  return mass_;
}
const ci::Color8u& Boid::GetColor() const {
  return color_;
}
double Boid::GetSeparationScale() const {
  return separation_scale_;
}
double Boid::GetAlignmentScale() const {
  return alignment_scale_;
}
double Boid::GetCohesionScale() const {
  return cohesion_scale_;
}
void Boid::SetSeparationScale(double separationScale) {
  separation_scale_ = separationScale;
}
void Boid::SetAlignmentScale(double alignmentScale) {
  alignment_scale_ = alignmentScale;
}
void Boid::SetCohesionScale(double cohesionScale) {
  cohesion_scale_ = cohesionScale;
}

}  // namespace idealgas

