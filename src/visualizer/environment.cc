#include <visualizer/environment.h>

namespace boidsimulation {

namespace visualizer {

using glm::vec2;

Environment::Environment(const glm::vec2 &top_left_corner, double pixels_x, double pixels_y,
                         size_t boid_num, double boid_speed, double boid_size,
                         size_t pred_num, double pred_speed, double pred_size) :
      top_left_corner_(top_left_corner), pixels_x_(pixels_x), pixels_y_(pixels_y),
      boid_size_(boid_size), boid_max_speed_(boid_size),
      pred_size_(pred_size), pred_max_speed_(pred_speed) {
  //Spawn Boids based on initial specifications
  InitializeBoids(boid_num, pred_num);
}

void Environment::InitializeBoids(size_t boid_num, size_t pred_num) {
  for(size_t current = 0; current < boid_num; ++current) {
    //Randomizing position and velocity
    MathVector position(rand() % (int)(pixels_x_ + 1 - spawn_margin) + top_left_corner_.x + spawn_margin,
                  rand() % (int)(pixels_y_ + 1 - spawn_margin) + top_left_corner_.y + spawn_margin, 0);
    MathVector velocity(rand() % (2*(int)boid_max_speed_) - (int)boid_max_speed_,
                                   rand() % (2*(int)boid_max_speed_) - (int)boid_max_speed_, 0);

    boids_.push_back(boidsimulation::Boid(
        position, velocity, boid_size_, 5*boid_size_, boid_max_speed_));
  }

  for(size_t current = 0; current < pred_num; ++current) {
    //Randomizing position and velocity
    MathVector position(rand() % (int)(pixels_x_ + 1 - spawn_margin) + top_left_corner_.x + spawn_margin,
                        rand() % (int)(pixels_y_ + 1 - spawn_margin) + top_left_corner_.y + spawn_margin, 0);
    MathVector velocity(rand() % (2*(int)pred_max_speed_) - (int)pred_max_speed_,
                        rand() % (2*(int)pred_max_speed_) - (int)pred_max_speed_, 0);

    predators_.push_back(boidsimulation::Boid(
        position, velocity, pred_size_, 5*pred_size_, pred_max_speed_, ci::Color8u(255,10,10)));
  }
}

void Environment::Update() {
  for(auto& it : boids_) {
    //Checking wall collisions
    CheckWallCollisions(it);
    //Update with flocking behavior
    it.Update(boids_);
  }
  for(auto& it : predators_) {
    //Checking wall collisions
    CheckWallCollisions(it);
    //Update with flocking behavior
    it.Update(boids_);
  }

  //Check if Predators caught Prey
  CheckPredatorCatch();
}

void Environment::CheckPredatorCatch() {
  for(auto& it : predators_) {
    for(auto it2 = boids_.begin(); it2 != boids_.end();) {
      //checking if other Boid is within reach of current Predator Boid
      MathVector pred_position = it.GetPosition();
      MathVector boid_position = it2->GetPosition();
      double distance = pred_position.Distance(boid_position);

      //remove boid if caught or iterate forward
      if(distance <= 0.5*it.GetSize()) {
        it2 = boids_.erase(it2);
      } else {
        ++it2;
      }
    }
  }
}

void Environment::CheckWallCollisions(boidsimulation::Boid &current_boid) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;

  //Collision with vertical walls
  //If Boid is close to left wall and moving left
  if((current_boid.GetPosition().x_ - left) < current_boid.GetSize() &&
      current_boid.GetVelocity().x_ < 0) {
    current_boid.WallCollide();
  }
  //If Boid is close to right wall and moving right
  if ((right - current_boid.GetPosition().x_) < current_boid.GetSize()
      && current_boid.GetVelocity().x_ > 0) {
    current_boid.WallCollide();
  }

  //Collision with horizontal walls
  //If Boid is close to top wall and moving up
  if((current_boid.GetPosition().y_ - top) < current_boid.GetSize() &&
      current_boid.GetVelocity().y_ < 0) {
    current_boid.WallCollide(1);
  }
  //If Boid is close to bottom wall and moving down
  if((bottom - current_boid.GetPosition().y_) < current_boid.GetSize()
     && current_boid.GetVelocity().y_ > 0) {
    current_boid.WallCollide(1);
  }
}

void Environment::Draw() const {
  //Drawing borders
  ci::Rectf borders(top_left_corner_, glm::vec2(top_left_corner_.x + pixels_x_,
                                             top_left_corner_.y + pixels_y_));
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(borders);

  //Drawing Boids
  for(auto& boid : boids_) {
    boid.Draw();
  }
  //Drawing Predators
  for(auto& predator : predators_) {
    predator.Draw();
  }
}

void Environment::AddBoid(const glm::vec2 &brush_screen_coords) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;
  //Only spawn Boid if within tank bounds
  if(brush_screen_coords.x > left && brush_screen_coords.x < right &&
     brush_screen_coords.y > top && brush_screen_coords.y < bottom) {
    MathVector position(brush_screen_coords.x, brush_screen_coords.y, 0);
    //Randomizing velocity
    MathVector velocity(rand() % (2*(int)boid_size_) - (int)boid_size_,
                        rand() % (2*(int)boid_size_) - (int)boid_size_, 0);

    boids_.push_back(boidsimulation::Boid(position, velocity));
  }
}

void Environment::Clear() {
  boids_.clear();
}

const std::vector<boidsimulation::Boid> & Environment::GetBoids() const {
  return boids_;
}

}  // namespace visualizer

}  // namespace boidsimulation
