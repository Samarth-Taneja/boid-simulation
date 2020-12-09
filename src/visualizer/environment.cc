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
        position, velocity, pred_size_, 5*pred_size_,
        pred_max_speed_, true, ci::Color8u(255,10,10)));
  }
}

void Environment::Update() {
  for(auto& boid : boids_) {
    //Updating parameters
    boid.SetSize(boid_size_);
    boid.SetMaxSpeed(boid_max_speed_);
    boid.SetSeparationScale(separation_);
    boid.SetAlignmentScale(alignment_);
    boid.SetCohesionScale(cohesion_);
    //Update with flocking behavior
    boid.Update(boids_, predators_, obstacles_);
    //Checking if out of bounds
    WallBound(boid);
  }
  for(auto& pred : predators_) {
    //Updating parameters
    pred.SetSize(pred_size_);
    pred.SetMaxSpeed(pred_max_speed_);
    //Update with flocking behavior
    pred.Update(boids_, predators_, obstacles_);
    //Checking wall collisions
    WallBound(pred);
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
      if(distance <= it.GetSize()) {
        it2 = boids_.erase(it2);
      } else {
        ++it2;
      }
    }
  }
}

void Environment::WallBound(boidsimulation::Boid &boid) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;

  if(boid.GetPosition().x_ < left) {
    boid.SetVelocity(boid.GetMaxSpeed(), boid.GetVelocity().y_, boid.GetVelocity().z_);
  } else if(boid.GetPosition().x_ > right) {
    boid.SetVelocity(-boid.GetMaxSpeed(), boid.GetVelocity().y_, boid.GetVelocity().z_);
  }

  if(boid.GetPosition().y_ < top) {
    boid.SetVelocity(boid.GetVelocity().x_, boid.GetMaxSpeed(), boid.GetVelocity().z_);
  } else if(boid.GetPosition().y_ > bottom) {
    boid.SetVelocity(boid.GetVelocity().x_, -boid.GetMaxSpeed(), boid.GetVelocity().z_);
  }
}

void Environment::Draw() const {
  //Drawing Boids
  for(auto& boid : boids_) {
    boid.Draw();
  }
  //Drawing Predators
  for(auto& predator : predators_) {
    predator.Draw();
  }
  //Drawing Obstacles
  for(auto& obstacle : obstacles_) {
    obstacle.Draw();
  }
}

void Environment::AddBoid(const glm::vec2 &brush_screen_coords) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;
  //Only spawn Boid if within environment bounds
  if(brush_screen_coords.x > left && brush_screen_coords.x < right &&
     brush_screen_coords.y > top && brush_screen_coords.y < bottom) {
    MathVector position(brush_screen_coords.x, brush_screen_coords.y, 0);
    //Randomizing velocity
    if(!spawn_predator_) {
      MathVector velocity(rand() % (2*(int)boid_max_speed_) - (int)boid_max_speed_,
                          rand() % (2*(int)boid_max_speed_) - (int)boid_max_speed_, 0);

      boids_.push_back(boidsimulation::Boid(position, velocity, boid_size_,
                                            5*boid_size_, boid_max_speed_));
    } else {
      MathVector velocity(rand() % (2*(int)pred_max_speed_) - (int)pred_max_speed_,
                          rand() % (2*(int)pred_max_speed_) - (int)pred_max_speed_, 0);

      predators_.push_back(boidsimulation::Boid(
          position, velocity, pred_size_, 5*pred_size_,
          pred_max_speed_, true, ci::Color8u(255,10,10)));
    }
  }
}

void Environment::AddObstacle(const glm::vec2& brush_screen_coords) {
  double left = top_left_corner_.x + obstacle_size_ ,
         right = top_left_corner_.x + pixels_x_ - obstacle_size_ ,
         top = top_left_corner_.y + obstacle_size_,
         bottom = top_left_corner_.y + pixels_y_ - obstacle_size_ ;
  //Only spawn Obstacle if within tank bounds
  if(brush_screen_coords.x > left && brush_screen_coords.x < right &&
     brush_screen_coords.y > top && brush_screen_coords.y < bottom) {
    MathVector position(brush_screen_coords.x, brush_screen_coords.y, 0);
    obstacles_.push_back(Obstacle(position,obstacle_size_));
  }
}

void Environment::SwitchBoidType() {
  spawn_predator_ = !spawn_predator_;
}

void Environment::Clear() {
  boids_.clear();
  predators_.clear();
  obstacles_.clear();
}

const std::vector<boidsimulation::Boid> & Environment::GetBoids() const {
  return boids_;
}

}  // namespace visualizer

}  // namespace boidsimulation
