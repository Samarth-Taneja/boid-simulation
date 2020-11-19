#pragma once

#include <core/boid.h>

#include <vector>

#include "cinder/gl/gl.h"

namespace boidsimulation {

namespace visualizer {

/**
 * A Gas Tank which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class GasTank {
 public:
  /**
   * Creates a Gas Tank.
   * @param top_left_corner The screen coordinates of the top left corner of the GasTank
   * @param pixels_x The X length of the Gas Tank measured in screen pixels.
   * @param pixels_y The Y length of the Gas Tank measured in screen pixels.
   * @param particle_nums The initial numbers of the different particle types.
   * @param masses The masses of the different particle types.
   * @param radii The radius of the different particle types.
   */
  GasTank(const glm::vec2& top_left_corner, double pixels_x, double pixels_y,
          std::vector<size_t> particle_nums, std::vector<float> masses, std::vector<float> radii);
  GasTank();

  /**
   * Creates default particles with the parameters specified in the constructor
   * to base other particles on and for printing purposes. Helper function to
   * the constructor.
   */
  void CreateParticleTemplates(std::vector<size_t> particle_nums, std::vector<float> masses, std::vector<float> radii);

  /**
   * Initializes particles in the tank based on the constructor parameters.
   * Helper function to the constructor.
   */
  void InitializeParticles(std::vector<size_t> particle_nums);


  /**
   * Performs particle/wall collisions and changes velocities accordingly.
   */
  void Update();

  /**
   * Checks if the current Particle is colliding with a wall and updates its
   * velocity accordingly. Helper function for Update method.
   * @param current_particle The current Particle.
   */
  void CheckWallCollisions(boidsimulation::Particle& current_particle);

  /**
   * Checks if the current Particle is colliding with any other particles and
   * updates their velocities accordingly. Helper function for Update method.
   * @param particle_index The current Particle's index in vector particles_
   */
  void CheckParticleCollisions(size_t particle_index);

  /**
   * Displays the current state of the Gas Tank in the Cinder application.
   */
  void Draw() const;

  /**
   * Adds a Particles at the brush's location with a randomized velocity from
   * -radius to +radius.
   * @param brush_screen_coords The screen coordinates at which the cursor is located.
   */
  void AddParticle(const glm::vec2& brush_screen_coords);

  /**
   * Remove all particles from the simulation.
   */
  void Clear();

  /**
   * Returns the current Particle type that will be called by AddParticle()
   */
  const boidsimulation::Particle& GetCurrentParticle() const;

  /**
   * Changes the current particle to the next one in the vector of Particle types.
   */
  void ChangeCurrentParticle();

  /**
   * Returns the particles in the tank.
   */
  const std::vector<boidsimulation::Particle>& GetParticles() const;

  /**
   * Returns the particle types.
   */
  const std::vector<boidsimulation::Particle>& GetParticleTypes() const;

 private:
  glm::vec2 top_left_corner_;
  double spawn_margin = 10;
  double pixels_x_;
  double pixels_y_;
  const std::vector<ci::Color8u> colors_{ci::Color8u(0,0,255),
                                   ci::Color8u(0,255,0),
                                   ci::Color8u(255,0,0)};

  std::vector<boidsimulation::Particle> particle_types_;
  size_t current_index_ = -1;

  std::vector<boidsimulation::Particle> particles_;
  float radius_ = 7.5;
};

}  // namespace visualizer

}  // namespace idealgas
