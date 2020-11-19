#include <core/math_vector.h>
#include <catch2/catch.hpp>

using boidsimulation::MathVector;

TEST_CASE("Constructors") {
  SECTION("Default Constructor") {
    MathVector empty_vector;
    REQUIRE(empty_vector.x_ == Approx(0.0));
    REQUIRE(empty_vector.y_ == Approx(0.0));
    REQUIRE(empty_vector.z_ == Approx(0.0));
  }

  SECTION("Values Constructor") {
    MathVector vector(1.0,2.0,3.0);
    REQUIRE(vector.x_ == Approx(1.0));
    REQUIRE(vector.y_ == Approx(2.0));
    REQUIRE(vector.z_ == Approx(3.0));
  }
}

TEST_CASE("Setter Methods") {
  MathVector vec;
  vec.Set(MathVector(1,2,3));
  SECTION("Set") {
    REQUIRE(vec.x_ == Approx(1.0));
    REQUIRE(vec.y_ == Approx(2.0));
    REQUIRE(vec.z_ == Approx(3.0));
  }
  vec.Zero();
  SECTION("Zero") {
    REQUIRE(vec.x_ == Approx(0.0));
    REQUIRE(vec.y_ == Approx(0.0));
    REQUIRE(vec.z_ == Approx(0.0));
  }
}

TEST_CASE("Rule of 5") {
  MathVector vec(1,2,3);
  MathVector copy_vec(vec);
  SECTION("Copy Constructor") {
    bool same = vec == copy_vec;
    bool different = vec != copy_vec;
    REQUIRE(same);
    REQUIRE(!different);
  }

  MathVector move_vec(std::move(vec));
  SECTION("Move Constructor") {
    bool same = move_vec == vec;
    bool different = move_vec != vec;
    REQUIRE(!same);
    REQUIRE(different);

    REQUIRE(move_vec.x_ == Approx(1.0));
    REQUIRE(move_vec.y_ == Approx(2.0));
    REQUIRE(move_vec.z_ == Approx(3.0));
  }

  MathVector vector(4,5,6);
  MathVector copy_vector;
  copy_vector = vector;
  SECTION("Copy Assignment") {
    bool same = copy_vector == vector;
    bool different = copy_vector != vector;
    REQUIRE(same);
    REQUIRE(!different);
  }

  MathVector move_vector;
  move_vector = std::move(vector);
  SECTION("Move Assignment") {
    bool same = move_vector == vector;
    bool different = move_vector != vector;
    REQUIRE(!same);
    REQUIRE(different);

    REQUIRE(move_vector.x_ == Approx(4.0));
    REQUIRE(move_vector.y_ == Approx(5.0));
    REQUIRE(move_vector.z_ == Approx(6.0));
  }
}
