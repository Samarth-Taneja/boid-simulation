#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_tank.h"
#include "histogram.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

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
  std::vector<float> masses_{10,25,50};
  std::vector<float> radii_{7,10,13};
  std::vector<size_t> particle_nums_ {25,25,25};
  GasTank tank_;
  std::vector<Histogram> histograms_;
};

}  // namespace visualizer

}  // namespace idealgas
