#pragma once

#include <core/boid.h>
#include <core/obstacle.h>

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
              size_t boid_num = 50, double boid_speed = 8, double boid_size = 10,
              size_t pred_num = 6, double pred_speed = 5, double pred_size = 15);

  /**
   * Initializes Boids in the Environment based on the constructor parameters.
   * Helper function to the constructor.
   * @param boid_num Number of regular boids to spawn.
   * @param pred_num Number of predator boids to spawn.
   */
  void InitializeBoids(size_t boid_num, size_t pred_num);

  /**
   * Performs wall collisions and updates Boid velocities.
   */
  void Update();

  /**
   * Checks if the current Boid is colliding with a wall and updates its
   * velocity accordingly. Helper function for Update method.
   * @param current_boid The current Boid.
   */
  void WallBound(boidsimulation::Boid& current_boid);

  /**
   * Checks if the Predator Boids have caught any prey Boids and
   * deletes Prey boids accordingly. Helper function for Update method.
   */
  void CheckPredatorCatch();

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
   * Adds an Obstacle at the click location.
   * @param brush_screen_coords
   */
  void AddObstacle(const glm::vec2& brush_screen_coords);

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

  std::vector<boidsimulation::Boid> boids_;
  double boid_size_ = 10;
  double boid_max_speed_ = 8;

  std::vector<boidsimulation::Boid> predators_;
  double pred_size_ = 15;
  double pred_max_speed_ = 5;

  std::vector<boidsimulation::Obstacle> obstacles_;
  double obstacle_size_ = 25;
};

}  // namespace visualizer

}  // namespace boidsimulation
