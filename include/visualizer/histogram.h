#pragma once

#include <core/particle.h>
#include "cinder/gl/gl.h"
#include "gas_tank.h"
#include <math.h>
#include <vector>
#include <map>

namespace idealgas {

namespace visualizer {

/**
 * A Gas Tank which will be displayed in the Cinder application and respond to
 * mouse events.
 */
class Histogram {
 public:
  /**
   * Creates a Histogram.
   * @param top_left_corner The screen coordinates of the top left corner of the Histogram
   * @param pixels_x The X length of the Histogram measured in screen pixels.
   * @param pixels_y The Y length of the Histogram measured in screen pixels.
   * @param mass The mass of particle to represent.
   */
  Histogram(const glm::vec2 &top_left_corner, double pixels_x, double pixels_y,
            float mass, float histogram_max, ci::Color8u color = ci::Color8u(255,255,255));

  /**
   * Updates the state of the Histogram with the current particle velocities.
   * @param particles Particles to analyze.
   */
  void Update(const std::vector<idealgas::Particle>& particles);

  /**
   * Displays the current state of the Histogram in the Cinder application.
   */
  void Draw();

 private:
  /**
   * Calculates the speeds from the provided vector of particles and saves them
   * in the speeds_ vector.
   * @param particles Particles to analyze.
   */
  void CalculateSpeeds(const std::vector<idealgas::Particle>& particles);

  /**
   * Counts the number of speeds in each section and stores them in the map counts_.
   */
  void CountSpeeds();

  /**
   * Displays the bars and speed labels of the histogram.
   */
  void DrawBars();

  glm::vec2 top_left_corner_;
  glm::vec2 origin_;
  glm::vec2 bottom_right_corner_;
  double pixels_x_;
  double pixels_y_;

  float mass_ = 0;
  size_t num_sections_ = 10;
  float histogram_max_ = 0; //largest value on x-axis
  size_t count_labels_ = 4; //number of count labels on the y-axis
  ci::Color8u color_;

  std::vector<float> speeds_; //speeds of all particles with the specified mass
  float max_speed_ = 0;
  std::vector<float> sections_; //speeds for each bar of the histogram
  float max_count_ = 0; //largest value on y-axis
  std::map<float, float> counts_; //counts of speeds in each section
};

}  // namespace visualizer

}  // namespace idealgas
