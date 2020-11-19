#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

class Particle {
 public:
  Particle() = default;

  /**
   * Constructor that takes in optional position, velocity, and radius parameters.
   * @param position_x The vec2 value of position.
   * @param velocity_y The vec2 value of velocity.
   * @param radius The float value of radius.
   */
  Particle(const glm::vec2& position, const glm::vec2& velocity, float mass,
           float radius, ci::Color8u color = ci::Color8u(255,255,255)) :
        position_(position), velocity_(velocity), mass_(mass), radius_(radius), color_(color) {};

  /**
   * Constructor that takes in optional position x&y, velocity x&y, and radius parameters.
   * @param position_x The float X value of position.
   * @param position_y The float Y value of position.
   * @param velocity_x The float X value of velocity.
   * @param velocity_y The float Y value of velocity.
   * @param radius The float value of radius.
   */
  Particle(float position_x, float position_y, float velocity_x, float velocity_y,
float mass, float radius = 1, ci::Color8u color = ci::Color8u(255,255,255)) :
      position_(glm::vec2(position_x, position_y)), velocity_(glm::vec2(velocity_x, velocity_y)),
mass_(mass), radius_(radius), color_(color) {};

  /**
   * Adds current velocity to the current position.
   */
  void UpdatePosition();

  /**
   * Negates Particle's velocity in x or y axis.
   * @param axis Should be 0 if x-axis. 1 if y-axis. 0 by default.
   */
  void WallCollide(int axis = 0);

  /**
   * Returns the particle's new velocity after collision with another particle.
   * Other particle's velocity must be calculated with a separate function call.
   * @param other_particle The other particle in the collision.
   */
  glm::vec2 ParticleCollide(const Particle& other_particle);

  //Getters & Setters
  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  float GetRadius() const;
  float GetMass() const;
  const ci::Color8u& GetColor() const;
  void SetVelocity(const glm::vec2 velocity);

 private:
  glm::vec2 position_ = glm::vec2(0,0);
  glm::vec2 velocity_ = glm::vec2(0,0);
  float radius_ = 1;
  float mass_ = 1;
  ci::Color8u color_;
};

}  // namespace idealgas
