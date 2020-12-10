#include <core/obstacle.h>

namespace boidsimulation {

void Obstacle::Draw() const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(glm::vec2(position_.x_,position_.y_),(float)size_);
}

const boidsimulation::MathVector & Obstacle::GetPosition() const {
  return position_;
}
double Obstacle::GetSize() const {
  return size_;
}
const ci::Color8u & Obstacle::GetColor() const {
  return color_;
}

}  // namespace idealgas

