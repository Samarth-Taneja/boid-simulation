#include <core/particle.h>
#include <catch2/catch.hpp>

TEST_CASE("Constructors") {
  idealgas::Particle particle;
  SECTION("Default Constructor") {
    REQUIRE(particle.GetPosition() == glm::vec2(0,0));
    REQUIRE(particle.GetVelocity() == glm::vec2(0,0));
    REQUIRE(particle.GetRadius() == Approx(1.0));
    REQUIRE(particle.GetMass() == Approx(1.0));
  }

  idealgas::Particle vec2_particle(glm::vec2(1,1), glm::vec2(0.5,0.5), 1, 1);
  SECTION("Vector Constructor") {
    REQUIRE(vec2_particle.GetPosition() == glm::vec2(1,1));
    REQUIRE(vec2_particle.GetVelocity() == glm::vec2(0.5,0.5));
    REQUIRE(vec2_particle.GetRadius() == Approx(1.0));
    REQUIRE(vec2_particle.GetMass() == Approx(1.0));
  }

  idealgas::Particle float_particle(1,1, 0.5,0.5, 1, 1);
  SECTION("Float Constructor") {
    REQUIRE(float_particle.GetPosition() == glm::vec2(1,1));
    REQUIRE(float_particle.GetVelocity() == glm::vec2(0.5,0.5));
    REQUIRE(float_particle.GetRadius() == Approx(1.0));
    REQUIRE(float_particle.GetMass() == Approx(1.0));
  }
}

//Tests if the position is accurately updated after one unit of time.
TEST_CASE("Update Position") {
  idealgas::Particle particle(glm::vec2(1,1), glm::vec2(0.5,0.5), 1, 1);
  particle.UpdatePosition();
  REQUIRE(particle.GetPosition() == glm::vec2(1.5,1.5));
}

//Tests if new velocities are accurately calculated for collisions.
TEST_CASE("Collisions") {
  idealgas::Particle particle(glm::vec2(1,1), glm::vec2(0.5,0.5), 1, 1);
  idealgas::Particle particle1(glm::vec2(20,20), glm::vec2(0.1,0), 1, 1);
  idealgas::Particle particle2(glm::vec2(21.4,21.4), glm::vec2(-0.1,0), 1, 1);
  idealgas::Particle particle3(glm::vec2(21.4,21.4), glm::vec2(0.1,0), 1, 1);

  //Tests if Wall collisions appropriately negate x or y value for velocity vector.
  SECTION("Wall Collisions") {
    //Tests if x value of velocity vector is negated for axis 0
    SECTION("X direction") {
      float temp_velocity_x = particle.GetVelocity().x;
      particle.WallCollide();
      REQUIRE(particle.GetVelocity().x == -temp_velocity_x);
    }

    //Tests if y value of velocity vector is negated for axis 1
    SECTION("Y direction") {
      float temp_velocity_y = particle.GetVelocity().y;
      particle.WallCollide(1);
      REQUIRE(particle.GetVelocity().y == -temp_velocity_y);
    }

    //Tests if values remain unchanged for an invalid axis parameter
    SECTION("Invalid direction") {
      float temp_velocity_x = particle.GetVelocity().x;
      float temp_velocity_y = particle.GetVelocity().y;
      particle.WallCollide(1234567890);
      REQUIRE(particle.GetVelocity().x == temp_velocity_x);
      REQUIRE(particle.GetVelocity().y == temp_velocity_y);
    }
  }

  //Tests if new velocities are accurately calculated for particle collisions.
  SECTION("Particle Collisions") {
    //Tests if new velocities are accurately calculated when particles move towards each other.
    SECTION("Valid Collision") {
      glm::vec2 v_1 = particle1.ParticleCollide(particle2);
      glm::vec2 v_2 = particle2.ParticleCollide(particle1);

      Approx target = Approx(0).margin(0.00005);
      REQUIRE(v_1.x == target);
      REQUIRE((-0.1 - v_1.y) == target);
      REQUIRE(v_2.x == target);
      REQUIRE((0.1 - v_2.y) == target);
    }

    //Tests if velocities remain the same when particles are moving away from each other.
    SECTION("Invalid Collision") {
      idealgas::Particle temp_particle1 = particle1;
      idealgas::Particle temp_particle3 = particle3;

      particle1.SetVelocity(particle1.ParticleCollide(temp_particle3));
      particle3.SetVelocity(particle3.ParticleCollide(temp_particle1));

      REQUIRE(particle1.GetVelocity() == temp_particle1.GetVelocity());
      REQUIRE(particle3.GetVelocity() == temp_particle3.GetVelocity());
    }
  }
}

