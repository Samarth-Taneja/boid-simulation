#include <visualizer/environment.h>

namespace boidsimulation {

namespace visualizer {

using glm::vec2;

GasTank::GasTank(const vec2& top_left_corner, double pixels_x, double pixels_y,
                 std::vector<size_t> particle_nums, std::vector<float> masses, std::vector<float> radii) :
      top_left_corner_(top_left_corner), pixels_x_(pixels_x), pixels_y_(pixels_y) {

  //Creating Template particles
  CreateParticleTemplates(particle_nums, masses, radii);
  if(!particle_types_.empty()) {
    current_index_ = 0;
  }

  //Adding particles to the simulation
  InitializeParticles(particle_nums);
}

void GasTank::CreateParticleTemplates(std::vector<size_t> particle_nums, std::vector<float> masses, std::vector<float> radii) {
  for(size_t particle_num = 0; particle_num < particle_nums.size(); ++particle_num) {
    particle_types_.push_back(boidsimulation::Particle(glm::vec2(0,0), glm::vec2(0,0),
                           masses.at(particle_num),radii.at(particle_num),
                           colors_.at(particle_num)));
  }
}

void GasTank::InitializeParticles(std::vector<size_t> particle_nums) {
  for(size_t type = 0; type < particle_nums.size(); ++type) {
    for(size_t particle_num = 0; particle_num < particle_nums.at(type); ++particle_num) {
      //Randomizing position and velocity
      glm::vec2 position =
          glm::vec2(rand() % (int)(pixels_x_ + 1 - spawn_margin) + top_left_corner_.x + spawn_margin,
                    rand() % (int)(pixels_y_ + 1 - spawn_margin) + top_left_corner_.y + spawn_margin);
      glm::vec2 velocity = glm::vec2(rand() % (2*(int)radius_) - (int)radius_,
                                     rand() % (2*(int)radius_) - (int)radius_);

      particles_.push_back(boidsimulation::Particle(position, velocity,
                                              particle_types_.at(type).GetMass(),
                                              particle_types_.at(type).GetRadius(),
                                              particle_types_.at(type).GetColor()));
    }
  }
}

void GasTank::Update() {
  for(size_t particle_num = 0; particle_num < particles_.size(); ++particle_num) {
    boidsimulation::Particle& current_particle = particles_.at(particle_num);

    //Checking wall collisions
    CheckWallCollisions(current_particle);

    //Checking particle collisions
    CheckParticleCollisions(particle_num);

    //Updating position of current Particle
    current_particle.UpdatePosition();
  }
}

void GasTank::CheckWallCollisions(boidsimulation::Particle& current_particle) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;
  //Collision with vertical walls
  //If particle is close to left wall and moving left
  if((current_particle.GetPosition().x - left) < current_particle.GetRadius() &&
      current_particle.GetVelocity().x < 0) {
      current_particle.WallCollide();
  }
  //If particle is close to right wall and moving right
  if ((right - current_particle.GetPosition().x) < current_particle.GetRadius()
      && current_particle.GetVelocity().x > 0) {
      current_particle.WallCollide();
  }
  //Collision with horizontal walls
  //If particle is close to top wall and moving up
  if((current_particle.GetPosition().y - top) < current_particle.GetRadius() &&
      current_particle.GetVelocity().y < 0) {
      current_particle.WallCollide(1);
  }
  //If particle is close to bottom wall and moving down
  if((bottom - current_particle.GetPosition().y) < current_particle.GetRadius()
      && current_particle.GetVelocity().y > 0) {
      current_particle.WallCollide(1);
  }
}

void GasTank::CheckParticleCollisions(size_t particle_index) {
  boidsimulation::Particle& current_particle = particles_.at(particle_index);
  for(size_t particle_num = 0; particle_num < particles_.size(); ++particle_num) {
    if(particle_num != particle_index) {
      boidsimulation::Particle& other_particle = particles_.at(particle_num);
      //if other particle in range perform collision calculation
      double distance = glm::distance(current_particle.GetPosition(), other_particle.GetPosition());
      if(distance < (current_particle.GetRadius() + other_particle.GetRadius())) {
        glm::vec2 new_v1 = current_particle.ParticleCollide(other_particle);
        glm::vec2 new_v2 = other_particle.ParticleCollide(current_particle);

        current_particle.SetVelocity(new_v1);
        other_particle.SetVelocity(new_v2);
      }
    }
  }
}

void GasTank::Draw() const {
  //Drawing tank
  ci::Rectf tank(top_left_corner_, glm::vec2(top_left_corner_.x + pixels_x_,
                                             top_left_corner_.y + pixels_y_));
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(tank);

  //Drawing particles
  for(size_t particle_num = 0; particle_num < particles_.size(); ++particle_num) {
    ci::gl::color(particles_.at(particle_num).GetColor());
    ci::gl::drawSolidCircle(particles_.at(particle_num).GetPosition(),
                            particles_.at(particle_num).GetRadius());
  }
}

void GasTank::AddParticle(const vec2& brush_screen_coords) {
  double left = top_left_corner_.x, right = top_left_corner_.x + pixels_x_,
      top = top_left_corner_.y, bottom = top_left_corner_.y + pixels_y_;
  //Only spawn's particle if within tank bounds
  if(brush_screen_coords.x > left && brush_screen_coords.x < right &&
      brush_screen_coords.y > top && brush_screen_coords.y < bottom) {
    glm::vec2 velocity = glm::vec2(rand() % (2*(int)radius_) - (int)radius_,
                                   rand() % (2*(int)radius_) - (int)radius_);
    particles_.push_back(boidsimulation::Particle(brush_screen_coords, velocity,
                                            particle_types_.at(current_index_).GetMass(),
                                            particle_types_.at(current_index_).GetRadius(),
                                            particle_types_.at(current_index_).GetColor()));
  }

}

void GasTank::Clear() {
  particles_.clear();
}

void GasTank::ChangeCurrentParticle() {
  current_index_ = ++current_index_ % particle_types_.size();
}

const boidsimulation::Particle& GasTank::GetCurrentParticle() const {
  return particle_types_.at(current_index_);
}
const std::vector<boidsimulation::Particle> & GasTank::GetParticleTypes() const {
  return particle_types_;
}
const std::vector<boidsimulation::Particle> & GasTank::GetParticles() const {
  return particles_;
}

}  // namespace visualizer

}  // namespace idealgas
