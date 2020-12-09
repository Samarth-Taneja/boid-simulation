#include <core/boid.h>
#include <limits>

namespace boidsimulation {

void Boid::Update(std::vector<Boid>& flock) {
  velocity_ += FlockingBehavior(flock);
  if(velocity_.Length() > max_speed_) {
    velocity_.ChangeMagnitude(max_speed_);
  }
  position_ += velocity_;
}

MathVector Boid::FlockingBehavior(std::vector<Boid>& flock) {
  MathVector flocking;
  if(!predator_) {
    flocking += (separation_scale_ * Separation(flock));
    flocking += (alignment_scale_ * Alignment(flock));
    flocking += (cohesion_scale_ * Cohesion(flock));
  }
  flocking += (chase_scale_ * Chase(flock));
  return flocking;
}
MathVector Boid::Separation(std::vector<Boid>& flock) {
  MathVector separation;
  for(size_t boid_index = 0; boid_index < flock.size(); ++boid_index) {
    //Only calculating for same type of boid (predator/prey)
    if((!predator_ && !flock.at(boid_index).predator_) ||
        (predator_ && flock.at(boid_index).predator_)) {
      //checking if other Boid is visible to current Boid
      double distance = position_.Distance(flock.at(boid_index).position_);
      if(distance > 0 && distance <= 2.5 * size_) {
        MathVector difference = flock.at(boid_index).position_ - position_;
        separation -= difference;
      }
    }
  }
  return separation;
}
MathVector Boid::Alignment(std::vector<Boid>& flock) {
  MathVector heading;
  size_t count = 0;
  for(size_t boid_index = 0; boid_index < flock.size(); ++boid_index) {
    //Only calculating for same type of boid (predator/prey)
    if((!predator_ && !flock.at(boid_index).predator_) ||
       (predator_ && flock.at(boid_index).predator_)) {
      //checking if other Boid is visible to current Boid
      double distance = position_.Distance(flock.at(boid_index).position_);
      if(distance > 0 && distance <= vision_) {
        heading += flock.at(boid_index).velocity_;
        ++count;
      }
    }
  }
  //calculating average heading of flock
  if (count > 0) {
    heading /= count;
    //vector pointing from velocity to avg heading of visible flock
    MathVector alignment_force = (heading - velocity_) / 4;
    return alignment_force;
  } else {
    return heading;
  }
}
MathVector Boid::Cohesion(std::vector<Boid>& flock) {
  MathVector center;
  double count = 0;
  for(size_t boid_index = 0; boid_index < flock.size(); ++boid_index) {
    //Only calculating for same type of boid (predator/prey)
    if((!predator_ && !flock.at(boid_index).predator_) ||
       (predator_ && flock.at(boid_index).predator_)) {
      //checking if other Boid is visible to current Boid
      double distance = position_.Distance(flock.at(boid_index).position_);
      if(distance > 0 && distance <= vision_) {
        center += flock.at(boid_index).position_;
        ++count;
      }
    }
  }
  //calculating average position of flock
  if(count > 0) {
    center /= count;
    //vector pointing from position to center of visible flock
    MathVector cohesion_force = (center - position_) / 35;
    return cohesion_force;
  } else {
    return center;
  }
}
MathVector Boid::Chase(std::vector<Boid>& flock) {
  MathVector chase;
  if(!predator_) {
    //Flees from closest Predator boid
    size_t chase_index = -1;
    double closest_distance = std::numeric_limits<double>::max();

    for(size_t boid_index = 0; boid_index < flock.size(); ++boid_index) {
      //checking if Predator Boid is visible to current Boid and is the closest to it
      double distance = position_.Distance(flock.at(boid_index).position_);
      if(distance > 0 && distance <= vision_ && flock.at(boid_index).predator_
          && distance < closest_distance) {
        closest_distance = distance;
        chase_index = boid_index;
      }
    }

    if(chase_index != -1) {
      MathVector difference = flock.at(chase_index).position_ - position_;
      chase -= difference;
    }
  }

  if(predator_) {
    //Chooses one prey boid to chase
    size_t chase_index = -1;
    double closest_distance = std::numeric_limits<double>::max();

    for(size_t boid_index = 0; boid_index < flock.size(); ++boid_index) {
      //checking if prey Boid is visible to current Boid and is the closest to it
      double distance = position_.Distance(flock.at(boid_index).position_);
      if(distance > 0 && distance <= vision_ && !flock.at(boid_index).predator_
          && distance < closest_distance) {
        closest_distance = distance;
        chase_index = boid_index;
      }
    }

    if(chase_index != -1) {
      MathVector difference = flock.at(chase_index).position_ - position_;
      chase += difference;
    }
  }
  return chase;
}

void Boid::WallCollide(int axis) {
  if(axis == 0) {
    velocity_.x_ = -velocity_.x_;
  } else if (axis == 1) {
    velocity_.y_ = -velocity_.y_;
  } else if (axis == 2) {
    velocity_.z_ = -velocity_.z_;
  }
}

void Boid::Draw() const {
  ci::gl::color(color_);

  //Creating triangle for current boid
  ci::PolyLine2f triangle;

  //Vertex that points in the direction the boid is moving.
  MathVector velocity_direction = velocity_ / velocity_.Length();
  MathVector to_vertex = size_ * velocity_direction;
  MathVector head = position_ + 1.5 * to_vertex;
  triangle.push_back(glm::vec2(head.x_, head.y_));

  //Rotate to_vertex clockwise and counterclockwise to get other two vertices
  MathVector left_tail = position_ + 0.75 * MathVector(to_vertex.y_, -to_vertex.x_, position_.z_);
  MathVector right_tail = position_ + 0.75 * MathVector(-to_vertex.y_, to_vertex.x_, position_.z_);
  triangle.push_back(glm::vec2(left_tail.x_, left_tail.y_));
  triangle.push_back(glm::vec2(right_tail.x_, right_tail.y_));

  triangle.push_back(glm::vec2(head.x_, head.y_));

  ci::gl::drawSolid(triangle);
}

//Getters & Setters
const MathVector& Boid::GetPosition() const {
  return position_;
}
const MathVector& Boid::GetVelocity() const {
  return velocity_;
}
double Boid::GetSize() const {
  return size_;
}
const ci::Color8u& Boid::GetColor() const {
  return color_;
}
const bool Boid::IsPredator() const {
  return predator_;
}

double Boid::GetSeparationScale() const {
  return separation_scale_;
}
double Boid::GetAlignmentScale() const {
  return alignment_scale_;
}
double Boid::GetCohesionScale() const {
  return cohesion_scale_;
}
void Boid::SetSeparationScale(double separationScale) {
  separation_scale_ = separationScale;
}
void Boid::SetAlignmentScale(double alignmentScale) {
  alignment_scale_ = alignmentScale;
}
void Boid::SetCohesionScale(double cohesionScale) {
  cohesion_scale_ = cohesionScale;
}

}  // namespace idealgas

