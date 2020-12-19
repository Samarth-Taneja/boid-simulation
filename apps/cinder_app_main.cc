#include <visualizer/boid_simulation_app.h>

using boidsimulation::visualizer::BoidSimApp;

void prepareSettings(BoidSimApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(BoidSimApp, ci::app::RendererGl, prepareSettings);
