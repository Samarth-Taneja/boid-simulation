#pragma once

#include <core/boid.h>

#include <vector>

#include "cinder/gl/gl.h"

namespace boidsimulation {

namespace visualizer {

/**
 * An Environment for Boids which will be displayed in the Cinder application
 * and respond to mouse events.
 */
class Environment {
 public:
  /**
   * Creates an Environment.
   * @param top_left_corner The screen coordinates of the top left corner of the Environment
   * @param pixels_x The X length of the Environment measured in screen pixels.
   * @param pixels_y The Y length of the Environment measured in screen pixels.
   * @param boid_num The initial numbers of Boids.
   * @param mass The mass of the Boids.
   * @param size The size of the Boids.
   */
  Environment(const glm::vec2& top_left_corner, double pixels_x, double pixels_y,
          size_t boid_num = 40, double mass = 1, double size = 7);

  /**
   * Initializes Boids in the Environment based on the constructor parameters.
   * Helper function to the constructor.
   */
  void InitializeBoids(size_t boid_num);


  /**
   * Performs wall collisions and updates Boid velocities.
   */
  void Update();

  /**
   * Checks if the current Boid is colliding with a wall and updates its
   * velocity accordingly. Helper function for Update method.
   * @param current_boid The current Boid.
   */
  void CheckWallCollisions(boidsimulation::Boid& current_boid);

  /**
   * Displays the current state of the Environment in the Cinder application.
   */
  void Draw() const;

  /**
   * Adds a Boid at the brush's location with a randomized velocity from
   * -size to +size.
   * @param brush_screen_coords The screen coordinates at which the cursor is located.
   */
  void AddBoid(const glm::vec2& brush_screen_coords);

  /**
   * Remove all Boids from the simulation.
   */
  void Clear();

  /**
   * Returns a vector of the Boids in the tank.
   */
  const std::vector<boidsimulation::Boid>& GetBoids() const;

 private:
  glm::vec2 top_left_corner_;
  double spawn_margin = 10;
  double pixels_x_;
  double pixels_y_;
  const std::vector<ci::Color8u> colors_{ci::Color8u(0,0,255),
                                         ci::Color8u(0,255,0),
                                         ci::Color8u(255,0,0)};

  std::vector<boidsimulation::Boid> boids_;
  double boid_size_ = 7;
  double boid_mass_ = 1;
};

}  // namespace visualizer

}  // namespace boidsimulation
