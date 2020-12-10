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

TEST_CASE("Magnitude and Direction") {
  MathVector zero_vector;
  REQUIRE(zero_vector.Length() == 0);

  MathVector vect(1,2,3);
  REQUIRE(vect.Length() == Approx(3.7416573868));

  SECTION("Normalize") {
   REQUIRE_NOTHROW(zero_vector.Normalize());

   vect.Normalize();
   REQUIRE(vect.Length() == 1);
  }

  SECTION("Change Magnitude") {
    vect.ChangeMagnitude(3);
    REQUIRE(vect.Length() == 3);

    MathVector vect_2(2,5,7);
    vect.ChangeMagnitude(vect_2);
    REQUIRE(vect.Length() == vect_2.Length());
  }

  SECTION("Change Direction + Angle") {
    MathVector direction(1,1,1);
    vect.ChangeDirection(direction);

    REQUIRE(vect.Angle(direction) == 0);
  }

  SECTION("Distance") {
    MathVector other(4,5,6);
    REQUIRE(vect.Distance(other) == Approx(5.196152423));
  }
}

TEST_CASE("Operator Overloads") {
  MathVector vect(1,2,3);
  MathVector other(4,5,6);

  SECTION("Index") {
    REQUIRE(vect[0] == 1);
    REQUIRE(vect[1] == 2);
    REQUIRE(vect[2] == 3);
    REQUIRE_THROWS(vect[-1]);
    REQUIRE_THROWS(vect[100]);
  }

  SECTION("Equality and Inequality") {
    MathVector copy = vect;
    bool same = vect == copy;
    bool not_same = vect != copy;
    bool not_different = vect == other;
    bool different = vect != other;
    REQUIRE(same);
    REQUIRE(!not_same);
    REQUIRE(!not_different);
    REQUIRE(different);
  }

  SECTION("Addition") {
    MathVector sum = vect + other;
    vect += other;
    MathVector final(5,7,9);

    bool plus_equal = vect == final;
    bool plus_assignment = sum == final;

    REQUIRE(plus_equal);
    REQUIRE(plus_assignment);
  }

  SECTION("Subtraction") {
    MathVector difference = vect - other;
    vect -= other;
    MathVector final(-3,-3,-3);

    bool minus_equal = vect == final;
    bool minus_assignment = difference == final;

    REQUIRE(minus_equal);
    REQUIRE(minus_assignment);
  }

  SECTION("Scalar Multiplication") {
    other *= 2;
    MathVector multiplied(8,10,12);

    bool scalar_mul = other == multiplied;
    REQUIRE(scalar_mul);

    MathVector vect_first = vect * 5;
    MathVector vect_second = 5 * vect;
    MathVector product(5,10,15);
    bool same = vect_first == vect_second;
    bool first = vect_first == product;
    bool second = vect_second == product;
    REQUIRE(same);
    REQUIRE(first);
    REQUIRE(second);
  }

  SECTION("Scalar Division") {
    other /= 2;
    MathVector divided(2,2.5,3);

    bool scalar_div = other == divided;
    REQUIRE(scalar_div);

    MathVector div = vect / 2;
    MathVector product(0.5,1,1.5);
    bool same = div == product;
    REQUIRE(same);
  }

  SECTION("Dot Product") {
    double dot = vect * other;
    double dot_2 = other * vect;
    REQUIRE(dot == 32);
    REQUIRE(dot_2 == 32);
  }

  SECTION("Cross Product") {
    MathVector cross_1 = vect % other;
    MathVector product_1(-3,6,-3);
    bool same_1 = cross_1 == product_1;
    REQUIRE(same_1);

    MathVector cross_2 = other % vect;
    MathVector product_2(3,-6,3);
    bool same_2 = cross_2 == product_2;
    REQUIRE(same_2);
  }
}
