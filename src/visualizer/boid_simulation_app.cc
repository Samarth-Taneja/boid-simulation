#include <visualizer/boid_simulation_app.h>

namespace boidsimulation {

namespace visualizer {

BoidSimApp::BoidSimApp() : environment_(glm::vec2(kMargin, kMargin),
                   kWindowSizeX - (2*kMargin), kWindowSizeY - (2*kMargin)) {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void BoidSimApp::update() {
  environment_.Update();
}

void BoidSimApp::draw() {
  ci::gl::clear(ci::Color("black"));
  environment_.Draw();
}

void BoidSimApp::mouseDown(ci::app::MouseEvent event) {
}

void BoidSimApp::mouseDrag(ci::app::MouseEvent event) {
}

void BoidSimApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
