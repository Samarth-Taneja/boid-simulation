#include <visualizer/boid_simulation_app.h>

using boidsimulation::visualizer::BoidSimApp;

void prepareSettings(BoidSimApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(BoidSimApp, ci::app::RendererGl, prepareSettings);
