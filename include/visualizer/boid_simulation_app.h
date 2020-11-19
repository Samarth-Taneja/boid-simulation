#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "environment.h"

namespace boidsimulation {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class BoidSimApp : public ci::app::App {
 public:
  BoidSimApp();

  void draw() override;
  void update() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSizeY = 875;
  const double kWindowSizeX = 1500;
  const double kMargin = 125;
  const double kHistSizeX = 275;
  const double kHistSizeY = 125;

 private:
};

}  // namespace visualizer

}  // namespace idealgas
