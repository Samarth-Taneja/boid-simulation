#include <core/boid.h>

namespace boidsimulation {

void Particle::UpdatePosition() {
  position_ += velocity_;
}

void Particle::WallCollide(int axis) {
  if(axis == 0) {
    velocity_.x = -velocity_.x;
  } else if (axis == 1) {
    velocity_.y = -velocity_.y;
  }
}

glm::vec2 Particle::ParticleCollide(const Particle& other_particle) {
  //Calculating relative velocity and relative position
  glm::vec2 relative_v = (velocity_ - other_particle.GetVelocity());
  glm::vec2 relative_x = (position_ - other_particle.GetPosition());

  //Checking if particles are moving towards each other
  if(glm::dot(relative_v, relative_x) < 0) {
    //Calculating orthogonal projection of relative velocity on relative position
    float projection_scalar = glm::dot(relative_v, relative_x) / glm::dot(relative_x, relative_x);
    float mass_adjustment = (2*other_particle.GetMass())/(mass_ + other_particle.GetMass());
    glm::vec2 projection = mass_adjustment * projection_scalar * relative_x;

    return (velocity_ - projection);
  }
  return velocity_;
}

//Getters & Setters
const glm::vec2& Particle::GetPosition() const {
  return position_;
}
const glm::vec2& Particle::GetVelocity() const {
  return velocity_;
}
float Particle::GetRadius() const {
  return radius_;
}
float Particle::GetMass() const {
  return mass_;
}
const ci::Color8u& Particle::GetColor() const {
  return color_;
}
void Particle::SetVelocity(const glm::vec2 velocity) {
  velocity_ = velocity;
}

}  // namespace idealgas

