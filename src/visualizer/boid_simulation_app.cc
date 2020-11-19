#include <visualizer/boid_simulation_app.h>

namespace boidsimulation {

namespace visualizer {

IdealGasApp::IdealGasApp()
    : tank_(glm::vec2(2 * kMargin + kHistSizeX, kMargin),
            kWindowSizeX - 3 * kMargin - kHistSizeX,
            kWindowSizeY - 2 * kMargin, particle_nums_,
            masses_, radii_) {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void IdealGasApp::update() {
  tank_.Update();
}

void IdealGasApp::draw() {
  ci::gl::clear(ci::Color("black"));
  tank_.Draw();

  double tank_middle_x = 2 * kMargin + kHistSizeX + (kWindowSizeX - 3 * kMargin - kHistSizeX)/2;
  ci::gl::drawStringCentered(
      "Current Particle: ",
      glm::vec2(tank_middle_x, kWindowSizeY - kMargin / 2), ci::Color("white"), ci::Font("Arial", 30));
  ci::gl::color(tank_.GetCurrentParticle().GetColor());
  ci::gl::drawSolidCircle(glm::vec2(tank_middle_x + kMargin, kWindowSizeY - kMargin / 2 + 12),
                          tank_.GetCurrentParticle().GetRadius());
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  tank_.AddParticle(event.getPos());
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
  tank_.AddParticle(event.getPos());
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      tank_.ChangeCurrentParticle();
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      tank_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
