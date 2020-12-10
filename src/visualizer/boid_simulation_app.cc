#include <visualizer/boid_simulation_app.h>

namespace boidsimulation {

namespace visualizer {

BoidSimApp::BoidSimApp() : environment_(glm::vec2(0, 0),
                   kWindowSizeX, kWindowSizeY) {
  ci::app::setWindowSize((int) kWindowSizeX, (int) kWindowSizeY);
}

void BoidSimApp::setup() {
  ui = ci::params::InterfaceGl("Parameters", glm::vec2(175, 400));

  ui.addParam("Spawn Predator", &environment_.spawn_predator_);
  ui.addText("Boid Parameters");
  ui.addParam("Boid Size", &environment_.boid_size_,
              "min=5 max=15 step=0.5 keyIncr=s keyDecr=a");
  ui.addParam("Boid Speed", &environment_.boid_max_speed_,
              "min=1 max=20 step=0.5 keyIncr=f keyDecr=d");
  ui.addParam("Separation", &environment_.separation_,
              "min=0.1 max=5 step=0.2 keyIncr=x keyDecr=z");
  ui.addParam("Alignment", &environment_.alignment_,
              "min=0.1 max=5 step=0.2 keyIncr=v keyDecr=c");
  ui.addParam("Cohesion", &environment_.cohesion_,
              "min=0.1 max=5 step=0.2 keyIncr=n keyDecr=b");
  ui.addSeparator();

  ui.addText("Predator Parameters");
  ui.addParam("Pred Size", &environment_.pred_size_,
              "min=5 max=25 step=0.5 keyIncr=w keyDecr=q");
  ui.addParam("Predator Speed", &environment_.pred_max_speed_,
              "min=1 max=15 step=0.5 keyIncr=r keyDecr=e");
  ui.addParam("Chase", &environment_.chase_,
              "min=1 max=50 step=0.5 keyIncr=y keyDecr=t");
  ui.addSeparator();

  ui.addText("Obstacle Parameters");
  ui.addParam("Obstacle Size", &environment_.obstacle_size_,
              "min=5 max=50 step=0.5 keyIncr=l keyDecr=k");
}

void BoidSimApp::update() {
  environment_.Update();
}

void BoidSimApp::draw() {
  ci::gl::clear(ci::Color("black"));
  environment_.Draw();
  ui.draw();
}

void BoidSimApp::mouseDown(ci::app::MouseEvent event) {
  if(event.isLeftDown()) {
    environment_.AddBoid(event.getPos());
  }

  if(event.isRightDown()) {
    environment_.AddObstacle(event.getPos());
  }
}

void BoidSimApp::mouseDrag(ci::app::MouseEvent event) {
  if(event.isLeftDown()) {
    environment_.AddBoid(event.getPos());
  }
}

void BoidSimApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      environment_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
