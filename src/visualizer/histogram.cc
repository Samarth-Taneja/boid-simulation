#include <visualizer/histogram.h>

namespace idealgas {

namespace visualizer {

Histogram::Histogram(const glm::vec2 &top_left_corner, double pixels_x, double pixels_y,
                     float mass, float histogram_max, ci::Color8u color) :
    top_left_corner_(top_left_corner), pixels_x_(pixels_x), pixels_y_(pixels_y),
      mass_(mass), histogram_max_(histogram_max), color_(color) {
  origin_ = glm::vec2(top_left_corner_.x, top_left_corner_.y + pixels_y_);
  bottom_right_corner_ = glm::vec2(top_left_corner_.x + pixels_x_,top_left_corner_.y + pixels_y_);
}

void Histogram::Update(const std::vector<idealgas::Particle>& particles) {
  speeds_.clear(); sections_.clear(); counts_.clear();
  max_speed_ = 0;
  max_count_ = 0; //largest value on y-axis

  CalculateSpeeds(particles);

  if(!speeds_.empty()) {
    // creating sections for the histogram
    for (size_t section = 0; section < num_sections_; section++) {
      sections_.push_back((section + 1) * histogram_max_ / num_sections_);
    }
    //adding counts to the sections
    CountSpeeds();
  }
}

void Histogram::CalculateSpeeds(const std::vector<idealgas::Particle>& particles) {
  for(auto& particle : particles) {
    //checking if particle should be included in histogram
    if(particle.GetMass() == mass_) {
      color_ = particle.GetColor();
      float speed = glm::length(particle.GetVelocity());
      speeds_.push_back(speed);
      if(speed > max_speed_) {
        max_speed_ = speed;
      }
    }
  }

  if(max_speed_ > histogram_max_) {
    histogram_max_ = max_speed_;
  }
}

void Histogram::CountSpeeds() {
  for(auto& speed : speeds_) {
    float initial_value = 0;
    for(size_t section = 0; section < sections_.size(); ++section) {
      //checking if value is in the section
      if(speed > initial_value && speed <= sections_.at(section)) {
        if(counts_.find(sections_.at(section)) != counts_.end()) {
          counts_[sections_.at(section)] = counts_[sections_.at(section)] + 1;
        } else {
          counts_[sections_.at(section)] = 1;
        }

        //adjusting max count
        if(counts_[sections_.at(section)] > max_count_) {
          max_count_ = counts_[sections_.at(section)];
        }
        break;
      }

      initial_value = sections_.at(section);
    }
  }
}

void Histogram::Draw() {
  ci::gl::color(ci::Color("white"));

  //rounding mass to print
  std::ostringstream rounded_mass;
  rounded_mass.precision(2);
  rounded_mass << std::fixed << mass_;

  //title
  ci::gl::drawStringCentered("Speed Distribution of Particles with Mass: " + rounded_mass.str(),
      glm::vec2(top_left_corner_.x + pixels_x_/2,top_left_corner_.y - pixels_x_/10),
                             ci::Color("white"),ci::Font("Arial", 25));

  //y-axis
  ci::gl::drawLine(top_left_corner_, glm::vec2(origin_.x, origin_.y+1));

  //Print y-axis label rotated
  ci::gl::pushModelMatrix();
  ci::gl::translate(glm::vec2(top_left_corner_.x - pixels_x_/3.5f, top_left_corner_.y + pixels_y_/2));
  ci::gl::rotate(static_cast<float>(3*M_PI/2));
  ci::gl::drawStringCentered("Particle Counts", glm::vec2(0,0),
                             ci::Color("white"), ci::Font("Arial", 25));
  ci::gl::popModelMatrix();

  //Printing count labels
  if(!speeds_.empty())
  for(size_t count_label = count_labels_; count_label > 0; --count_label) {
    //Rounding max count to print
    std::ostringstream max_count;
    max_count.precision(2);
    max_count << std::fixed << max_count_ - (count_labels_ - count_label) * max_count_/count_labels_;
    std::string string = max_count.str();
    ci::gl::drawStringCentered(max_count.str(),
                               glm::vec2(top_left_corner_.x - pixels_x_/10,
                                         top_left_corner_.y + (pixels_y_/count_labels_)*(count_labels_-count_label)),
                               ci::Color("white"),ci::Font("Arial", 25));
  }

  //x-axis
  ci::gl::drawLine(glm::vec2(origin_.x, origin_.y+1),
                   glm::vec2(bottom_right_corner_.x, bottom_right_corner_.y + 1));
  ci::gl::drawStringCentered("Speeds",
      glm::vec2(top_left_corner_.x + pixels_x_/2,
                                       bottom_right_corner_.y + pixels_x_/10),
      ci::Color("white"),ci::Font("Arial", 25));

  //Drawing Bars of the Histogram
  DrawBars();
}

void Histogram::DrawBars() {
  if(!speeds_.empty()) {
    ci::gl::color(color_);

    //Drawing bars
    for(size_t bar_num = 0; bar_num < num_sections_; ++bar_num) {
      float count = counts_[sections_.at(bar_num)];
      glm::vec2 bottom_right(top_left_corner_.x + (bar_num+1) * pixels_x_ / num_sections_,
                             bottom_right_corner_.y);
      glm::vec2 top_left(top_left_corner_.x + bar_num * pixels_x_ / num_sections_,
                         top_left_corner_.y + pixels_y_ * (1 - count /max_count_));
      ci::Rectf bar(top_left, bottom_right);
      ci::gl::drawSolidRect(bar);

      //printing every other section's speed label
      if(bar_num % 2 != num_sections_ % 2) {
        //Rounding speed to print
        std::ostringstream speed;
        speed.precision(2);
        speed << std::fixed << sections_.at(bar_num);

        //Printing speed for the section
        ci::gl::drawStringCentered(speed.str(),
                                   glm::vec2((top_left.x + bottom_right.x) / 2, bottom_right.y + 5),
                                   ci::Color("white"),ci::Font("Arial", 25));
      }
    }
  }
}

}  // namespace visualizer

}  // namespace idealgas
