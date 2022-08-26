#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "flock.cpp"
#include "vettore.cpp"

TEST_CASE("testing vettore.cpp") {
  SUBCASE("testing vettore::set_value()") {
    vettore a{0., 0.};
    vettore b{2., 3.};
    a.set_value(2., 3.);
    CHECK(a.get_x() == 2.);
    CHECK(a.get_y() == 3.);
    vettore c{-2., 6.};
    c.set_value(b.get_x(), a.get_y());
    CHECK(c.get_x() == 2.);
    CHECK(c.get_y() == 3.);
  }

  SUBCASE("testing vettore::operator+()") {
    vettore a{2., 0.};
    vettore b{-4., 10.};
    vettore res_1 = a + b;
    CHECK(res_1.get_x() == -2.);
    CHECK(res_1.get_y() == 10.);
    vettore c{2.6, -9.2};
    vettore res_2 = b + c;
    CHECK(res_2.get_x() == doctest::Approx(-1.4));
    CHECK(res_2.get_y() == doctest::Approx(0.8));
    vettore res_3 = a + b + c;
    CHECK(res_3.get_x() == doctest::Approx(0.6));
    CHECK(res_3.get_y() == doctest::Approx(0.8));
  }

  SUBCASE("testing vettore::operator-()") {
    vettore a{2., 1.};
    vettore b{5., 6.};
    vettore res_1 = a - b;
    CHECK(res_1.get_x() == -3);
    CHECK(res_1.get_y() == -5);
    vettore c{2.3, 7.1};
    vettore res_2 = b - c;
    CHECK(res_2.get_x() == doctest::Approx(2.7));
    CHECK(res_2.get_y() == doctest::Approx(-1.1));
    vettore res_3 = a - b - c;
    CHECK(res_3.get_x() == doctest::Approx(-5.3));
    CHECK(res_3.get_y() == doctest::Approx(-12.1));
  }

  SUBCASE("testing vettore::operator*()") {
    vettore a{2., 3.};
    vettore res_1 = a * 3.;
    CHECK(res_1.get_x() == 6.);
    CHECK(res_1.get_y() == 9.);
    vettore b{1.2, -5.6};
    vettore res_2 = b * 2.6;
    CHECK(res_2.get_x() == doctest::Approx(3.12));
    CHECK(res_2.get_y() == doctest::Approx(-14.56));
    vettore res_3 = null * 4.6;
    CHECK(res_3.get_x() == 0.);
    CHECK(res_3.get_y() == 0.);
    vettore res_4 = b * 0.;
    CHECK(res_4.get_x() == 0.);
    CHECK(res_4.get_y() == 0.);
  }

  SUBCASE("testing vettore::operator/()") {
    vettore a{1., 6.};
    vettore res_1 = a / 2.;
    CHECK(res_1.get_x() == 0.5);
    CHECK(res_1.get_y() == 3.);
    vettore b{2.4, 5.1};
    vettore res_2 = b / 2.7;
    CHECK(res_2.get_x() == doctest::Approx(0.8889));
    CHECK(res_2.get_y() == doctest::Approx(1.8889));
    vettore res_3 = null / 4.7;
    CHECK(res_3.get_x() == 0.);
    CHECK(res_3.get_y() == 0.);
  }

  SUBCASE("testing vettore::norm()") {
    vettore a{0., 0.};
    CHECK(a.norm() == 0.);
    vettore b{10., -2};
    CHECK(b.norm() == doctest::Approx(10.198));
    vettore c{13.2, 0.};
    CHECK(c.norm() == doctest::Approx(13.2));
  }

  SUBCASE("testing scalar_prod()") {
    vettore a{0., 0.};
    vettore b{1., 2.};
    CHECK(scalar_prod(a, b) == 0.);
    vettore c{1., 1.};
    vettore d{1., -1.};
    CHECK(scalar_prod(c, d) == 0.);
    vettore e{3.56, -2.3};
    vettore f{1.11, 76.57};
    CHECK(scalar_prod(e, f) == doctest::Approx(-172.159));
    CHECK(scalar_prod(f, e) == doctest::Approx(-172.159));
  }

  SUBCASE("angle_between_vectors()") {
    vettore a{1., 0.};
    vettore b{0., 1.};
    CHECK(angle_between_vectors(a, b) == doctest::Approx(M_PI / 2));
    vettore c{0., -1};
    CHECK(angle_between_vectors(a, c) == doctest::Approx(M_PI / 2));
    vettore d{1., 1.};
    CHECK(angle_between_vectors(a, d) == doctest::Approx(M_PI / 4));
    vettore e{1., -1.};
    CHECK(angle_between_vectors(a, e) == doctest::Approx(M_PI / 4));
    vettore f{-1., 1.};
    CHECK(angle_between_vectors(a, f) == doctest::Approx(3 * M_PI / 4));
    vettore g{-1., 1.};
    CHECK(angle_between_vectors(a, g) == doctest::Approx(3 * M_PI / 4));
    vettore h{-1., 0.};
    CHECK(angle_between_vectors(a, h) == doctest::Approx(M_PI));
  }
}

TEST_CASE("testing flock.cpp") {
  flock stormo_1{3, 1.5, 0.01, 0.001, 2};
  flock stormo_2{6, 3, 0.02, 0.002, 2};
  flock stormo_3{15, 7.5, 0.05, 0.005, 2};

  SUBCASE("testing flock::centre of mass") {
    vettore a{150., 400.};
    vettore b{500., 968.};
    std::vector<vettore> positions{a, b};
    vettore res_1 = center_of_mass(positions);
    CHECK(res_1.get_x() == 325.);
    CHECK(res_1.get_y() == 684.);
    vettore c{0.57, -567.2};
    positions.push_back(c);
    vettore res_2 = center_of_mass(positions);
    CHECK(res_2.get_x() == doctest::Approx(216.857));
    CHECK(res_2.get_y() == doctest::Approx(266.933));
    positions.clear();
    positions.push_back(null);
    vettore res_3 = center_of_mass(positions);
    CHECK(res_3.get_x() == 0);
    CHECK(res_3.get_y() == 0.);
    positions.clear();
    vettore d{12.5, 13.6};
    positions.push_back(d);
    vettore res_4 = center_of_mass(positions);
    CHECK(res_4.get_x() == 12.5);
    CHECK(res_4.get_y() == 13.6);
  }

  SUBCASE("testing flock::medium_velocity") {
    vettore a{120., 300.};
    vettore b{23.56, -378.77};
    std::vector<vettore> velocities{a, b};
    vettore res_1 = medium_velocity(velocities);
    CHECK(res_1.get_x() == doctest::Approx(71.78));
    CHECK(res_1.get_y() == doctest::Approx(-39.385));
    velocities.push_back(null);
    vettore res_2 = medium_velocity(velocities);
    CHECK(res_2.get_x() == doctest::Approx(47.853));
    CHECK(res_2.get_y() == doctest::Approx(-26.2568));
    velocities.clear();
    velocities = {null, null};
    vettore res_3 = medium_velocity(velocities);
    CHECK(res_3.get_x() == 0.);
    CHECK(res_3.get_y() == 0.);
    velocities.clear();
    vettore c{22.3, 12.7};
    velocities.push_back(c);
    vettore res_4 = medium_velocity(velocities);
    CHECK(res_4.get_x() == 22.3);
    CHECK(res_4.get_y() == 12.7);
  }

  SUBCASE("testing medium_velocities_j()") {
    vettore a{10., 20.};
    vettore b{24.6, 88.5};
    vettore c{3.2, 6.5};
    vettore d{44.3, 76.2};
    std::vector<vettore> velocities{a, b, c, d};
    std::vector<vettore> velocities_seen{a, b, c};
    vettore res_1 = medium_velocity_j(velocities, velocities_seen, 0);
    CHECK(res_1.get_x() == 13.9);
    CHECK(res_1.get_y() == 47.5);
    vettore res_2 = medium_velocity_j(velocities, velocities_seen, 1);
    CHECK(res_2.get_x() == 6.6);
    CHECK(res_2.get_y() == 13.25);
    velocities_seen.clear();
    velocities_seen.push_back(d);
    vettore res_3 = medium_velocity_j(velocities, velocities_seen, 0);
    CHECK(res_3.get_x() == 44.3);
    CHECK(res_3.get_y() == 76.2);
    stormo_1.velocities_seen.clear();
    stormo_1.positions_seen.clear();
  }

  SUBCASE("testing flock::sdv_center_of_mass()") {
    vettore p_1{150., 400.};
    vettore p_2{500., 968.};
    std::vector<vettore> positions{p_1, p_2};
    double res_1 = sdv_center_of_mass(positions);
    CHECK(res_1 == doctest::Approx(468.324));
    vettore p_3{0.57, -567.2};
    positions.push_back(p_3);
    double res_2 = sdv_center_of_mass(positions);
    CHECK(res_2 == doctest::Approx(553.485));
    positions.clear();
    vettore p_4{200.2, 387.5};
    vettore p_5{200.2, 387.5};
    positions = {p_4, p_5};
    double res_3 = sdv_center_of_mass(positions);
    CHECK(res_3 == 0.);
    positions.clear();
    positions.push_back(p_1);
    double res_4 = sdv_center_of_mass(positions);
    CHECK(res_4 == 0.);
  }

  SUBCASE("testing flock::sdv_medium_velocity()") {
    vettore v_1{120., 300.};
    vettore v_2{23.56, -378.77};
    std::vector<vettore> velocities{v_1, v_2};
    double res_1 = sdv_medium_velocity(velocities);
    CHECK(res_1 == doctest::Approx(383.1134));
    vettore v_3{56.3, 158.6};
    velocities.push_back(v_3);
    double res_2 = sdv_medium_velocity(velocities);
    CHECK(res_2 == doctest::Approx(289.1628));
    velocities.clear();
    vettore v_4{24.5, 67.4};
    vettore v_5{24.5, 67.4};
    velocities = {v_4, v_5};
    double res_3 = sdv_medium_velocity(velocities);
    CHECK(res_3 == 0.);
    velocities.clear();
    velocities.push_back(v_1);
    double res_4 = sdv_medium_velocity(velocities);
    CHECK(res_4 == 0.);
  }

  SUBCASE("testing flock::v_separation_j()") {
    vettore p_1{300.1, 350.4};
    vettore p_2{360.3, 270.7};
    stormo_1.positions = {p_1, p_2};
    vettore res_1 = stormo_1.v_separation_i(0);
    vettore res_2 = stormo_1.v_separation_i(1);
    CHECK(res_1.get_x() == 0.);
    CHECK(res_1.get_y() == 0.);
    CHECK(res_2.get_x() == 0.);
    CHECK(res_2.get_y() == 0.);
    vettore p_3{301.1, 351.3};
    stormo_1.positions.push_back(p_3);
    vettore res_3 = stormo_1.v_separation_i(0);
    vettore res_4 = stormo_1.v_separation_i(2);
    CHECK(res_3.get_x() == doctest::Approx(-1.5));
    CHECK(res_3.get_y() == doctest::Approx(-1.35));
    CHECK(res_4.get_x() == doctest::Approx(1.5));
    CHECK(res_4.get_y() == doctest::Approx(1.35));
    stormo_2.positions = stormo_1.positions;
    vettore res_5 = stormo_2.v_separation_i(0);
    vettore res_6 = stormo_2.v_separation_i(2);
    CHECK(res_5.get_x() == doctest::Approx(-3));
    CHECK(res_5.get_y() == doctest::Approx(-2.70));
    CHECK(res_6.get_x() == doctest::Approx(3));
    CHECK(res_6.get_y() == doctest::Approx(2.70));
    stormo_3.positions = stormo_1.positions;
    vettore res_7 = stormo_3.v_separation_i(0);
    vettore res_8 = stormo_3.v_separation_i(2);
    CHECK(res_7.get_x() == doctest::Approx(-7.5));
    CHECK(res_7.get_y() == doctest::Approx(-6.75));
    CHECK(res_8.get_x() == doctest::Approx(7.5));
    CHECK(res_8.get_y() == doctest::Approx(6.75));
  }

  SUBCASE("testing flock::v_allignement_i") {
    vettore p_1{300.1, 361.5};
    vettore p_2{365.2, 388.3};
    vettore v_1{20.1, 30.3};
    vettore v_2{12.4, 32.2};
    stormo_1.positions = {p_1, p_2};
    stormo_1.velocities = {v_1, v_2};
    stormo_1.sight_angle(0);
    vettore res_1 = stormo_1.v_allignement1_i(0);
    CHECK(res_1.get_x() == doctest::Approx(-0.077));
    CHECK(res_1.get_y() == doctest::Approx(0.019));
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    vettore p_3{250., 270.};
    vettore v_3{17.0, 28.2};
    stormo_1.positions.push_back(p_3);
    stormo_1.velocities.push_back(v_3);
    stormo_1.sight_angle(2);
    vettore res_2 = stormo_1.v_allignement1_i(2);
    CHECK(res_2.get_x() == doctest::Approx(-0.0075));
    CHECK(res_2.get_y() == doctest::Approx(0.0305));
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    stormo_1.velocities[1].set_value(-12.4, -32.2);
    stormo_1.sight_angle(2);
    vettore res_3 = stormo_1.v_allignement1_i(2);
    CHECK(res_3.get_x() == doctest::Approx(-0.1315));
    CHECK(res_3.get_y() == doctest::Approx(-0.2915));
    stormo_2.positions = stormo_1.positions;
    stormo_2.velocities = stormo_1.velocities;
    stormo_2.sight_angle(2);
    vettore res_4 = stormo_2.v_allignement1_i(2);
    CHECK(res_4.get_x() == doctest::Approx(-0.263));
    CHECK(res_4.get_y() == doctest::Approx(-0.583));
    stormo_3.positions = stormo_1.positions;
    stormo_3.velocities = stormo_1.velocities;
    stormo_3.sight_angle(2);
    vettore res_5 = stormo_3.v_allignement1_i(2);
    CHECK(res_5.get_x() == doctest::Approx(-0.6575));
    CHECK(res_5.get_y() == doctest::Approx(-1.4575));
  }

  SUBCASE("testing flock::v_cohesion_i()") {
    vettore p_1{100.2, 165.3};
    vettore v_1{10.2, 15.1};
    vettore p_2{276.8, 245.6};
    vettore v_2{12.7, 13.4};
    stormo_1.positions = {p_1, p_2};
    stormo_1.velocities = {v_1, v_2};
    stormo_1.sight_angle(0);
    vettore res_1 = stormo_1.v_cohesion_i(0);
    CHECK(res_1.get_x() == doctest::Approx(0.0883));
    CHECK(res_1.get_y() == doctest::Approx(0.04015));
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    vettore p_3{298.7, 301.2};
    vettore v_3{22.3, 18.5};
    stormo_1.positions.push_back(p_3);
    stormo_1.velocities.push_back(v_3);
    stormo_1.sight_angle(0);
    vettore res_2 = stormo_1.v_cohesion_i(0);
    CHECK(res_2.get_x() == doctest::Approx(0.125033));
    CHECK(res_2.get_y() == doctest::Approx(0.0720667));
    stormo_2.positions = stormo_1.positions;
    stormo_2.velocities = stormo_1.velocities;
    stormo_2.sight_angle(0);
    vettore res_3 = stormo_2.v_cohesion_i(0);
    CHECK(res_3.get_x() == doctest::Approx(0.250067));
    CHECK(res_3.get_y() == doctest::Approx(0.144133));
    stormo_3.positions = stormo_1.positions;
    stormo_3.velocities = stormo_1.velocities;
    stormo_3.sight_angle(0);
    vettore res_4 = stormo_3.v_cohesion_i(0);
    CHECK(res_4.get_x() == doctest::Approx(0.625167));
    CHECK(res_4.get_y() == doctest::Approx(0.360333));
  }

  SUBCASE("testing flock::sight_angle()") {
    vettore p_1{200.4, 300.2};
    vettore v_1{10.3, 15.3};
    vettore p_2{400.7, 500.9};
    vettore v_2{20.1, 10.4};
    stormo_1.positions = {p_1, p_2};
    stormo_1.velocities = {v_1, v_2};
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 2);
    CHECK(stormo_1.velocities_seen.size() == 2);
    CHECK(stormo_1.positions_seen[0].get_x() == 200.4);
    CHECK(stormo_1.velocities_seen[0].get_x() == 10.3);
    CHECK(stormo_1.positions_seen[1].get_x() == 400.7);
    CHECK(stormo_1.velocities_seen[1].get_x() == 20.1);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    vettore p_3{950., 930.5};
    vettore v_3{15.1, 10.2};
    stormo_1.positions.push_back(p_3);
    stormo_1.velocities.push_back(v_3);
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 2);
    CHECK(stormo_1.velocities_seen.size() == 2);
    CHECK(stormo_1.positions_seen[0].get_x() == 200.4);
    CHECK(stormo_1.velocities_seen[0].get_x() == 10.3);
    CHECK(stormo_1.positions_seen[1].get_x() == 400.7);
    CHECK(stormo_1.velocities_seen[1].get_x() == 20.1);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    vettore p_4{152.7, 149.8};
    vettore v_4{15.1, -13.2};
    stormo_1.positions = {p_1, p_2, p_3, p_4};
    stormo_1.velocities = {v_1, v_2, v_3, v_4};
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 3);
    CHECK(stormo_1.velocities_seen.size() == 3);
    CHECK(stormo_1.positions_seen[0].get_x() == 200.4);
    CHECK(stormo_1.velocities_seen[0].get_x() == 10.3);
    CHECK(stormo_1.positions_seen[1].get_x() == 400.7);
    CHECK(stormo_1.velocities_seen[1].get_x() == 20.1);
    CHECK(stormo_1.positions_seen[2].get_x() == 152.7);
    CHECK(stormo_1.velocities_seen[2].get_x() == 15.1);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    stormo_1.positions[0].set_value(500.5, 102.4);
    stormo_1.sight_angle(1);
    CHECK(stormo_1.positions_seen.size() == 1);
    CHECK(stormo_1.velocities_seen.size() == 1);
    CHECK(stormo_1.positions_seen[0].get_x() == 400.7);
    CHECK(stormo_1.velocities_seen[0].get_x() == 20.1);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    stormo_1.positions.clear();
    stormo_1.velocities.clear();
    vettore p_5{300.2, 200.3};
    vettore v_5{3., 0.};
    vettore p_6{299.2, 202.3};
    vettore v_6{12., 4.};
    stormo_1.positions = {p_5, p_6};
    stormo_1.velocities = {v_5, v_6};
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 2);
    CHECK(stormo_1.velocities_seen.size() == 2);
    CHECK(stormo_1.positions_seen[0].get_x() == 300.2);
    CHECK(stormo_1.velocities_seen[0].get_x() == 3.);
    CHECK(stormo_1.positions_seen[1].get_x() == 299.2);
    CHECK(stormo_1.velocities_seen[1].get_x() == 12.);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    vettore p_7{300.2, 630.5};
    vettore v_7{25.7, 42.1};
    stormo_1.positions.push_back(p_7);
    stormo_1.velocities.push_back(v_7);
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 3);
    CHECK(stormo_1.velocities_seen.size() == 3);
    CHECK(stormo_1.positions_seen[0].get_y() == 200.3);
    CHECK(stormo_1.velocities_seen[0].get_x() == 3.);
    CHECK(stormo_1.positions_seen[1].get_y() == 202.3);
    CHECK(stormo_1.velocities_seen[1].get_x() == 12.);
    CHECK(stormo_1.positions_seen[2].get_y() == 630.5);
    CHECK(stormo_1.velocities_seen[2].get_x() == 25.7);
    stormo_1.positions.clear();
    stormo_1.velocities.clear();
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    stormo_1.positions = {p_5, p_7};
    stormo_1.velocities = {v_5, v_7};
    stormo_1.velocities[1].set_value(0., 4.);
    stormo_1.sight_angle(0);
    CHECK(stormo_1.positions_seen.size() == 2);
    CHECK(stormo_1.velocities_seen.size() == 2);
    CHECK(stormo_1.positions_seen[0].get_y() == 200.3);
    CHECK(stormo_1.positions_seen[1].get_y() == 630.5);
    CHECK(stormo_1.velocities_seen[0].get_x() == 3.);
    CHECK(stormo_1.velocities_seen[1].get_x() == 0.);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    stormo_1.sight_angle(1);
    CHECK(stormo_1.positions_seen.size() == 1);
    CHECK(stormo_1.velocities_seen.size() == 1);
    CHECK(stormo_1.positions_seen[0].get_y() == 630.5);
    CHECK(stormo_1.velocities_seen[0].get_x() == 0.);
    stormo_1.positions_seen.clear();
    stormo_1.velocities_seen.clear();
    v_7.set_value(0., 4.);
    stormo_1.positions = {p_5, p_6, p_7};
    stormo_1.velocities = {v_5, v_6, v_7};
    stormo_1.sight_angle(1);
    CHECK(stormo_1.positions_seen.size() == 3);
    CHECK(stormo_1.velocities_seen.size() == 3);
    CHECK(stormo_1.positions_seen[0].get_y() == 200.3);
    CHECK(stormo_1.positions_seen[1].get_x() == 299.2);
    CHECK(stormo_1.positions_seen[2].get_y() == 630.5);
    CHECK(stormo_1.velocities_seen[0].get_x() == 3.);
    CHECK(stormo_1.velocities_seen[1].get_x() == 12.);
    CHECK(stormo_1.velocities_seen[2].get_x() == 0.);
  };

  SUBCASE("testing flock::wall_hit()") {
    vettore p_1{971.3, 400.5};
    vettore v_1{23.3, 25.4};
    stormo_1.positions_.push_back(p_1);
    stormo_1.velocities_.push_back(v_1);
    stormo_1.wall_hit(0);
    CHECK(stormo_1.velocities_[0].get_x() == -23.3);
    CHECK(stormo_1.velocities_[0].get_y() == 25.4);
    vettore p_2{356.4, 972.6};
    vettore v_2{17.2, 14.5};
    stormo_1.positions_.push_back(p_2);
    stormo_1.velocities_.push_back(v_2);
    stormo_1.wall_hit(1);
    CHECK(stormo_1.velocities_[1].get_x() == 17.2);
    CHECK(stormo_1.velocities_[1].get_y() == -14.5);
    vettore p_3{971.3, 973.2};
    vettore v_3{21.2, 18.3};
    stormo_1.positions_.push_back(p_3);
    stormo_1.velocities_.push_back(v_3);
    stormo_1.wall_hit(2);
    CHECK(stormo_1.velocities_[2].get_x() == -21.2);
    CHECK(stormo_1.velocities_[2].get_y() == -18.3);
    vettore p_4{29.3, 56.9};
    vettore v_4{-12.2, 8.7};
    stormo_1.positions_.push_back(p_4);
    stormo_1.velocities_.push_back(v_4);
    stormo_1.wall_hit(3);
    CHECK(stormo_1.velocities_[3].get_x() == 12.2);
    CHECK(stormo_1.velocities_[3].get_y() == 8.7);
    vettore p_5{28.6, 29.4};
    vettore v_5{-11.2, -9.4};
    stormo_1.positions_.push_back(p_5);
    stormo_1.velocities_.push_back(v_5);
    stormo_1.wall_hit(4);
    CHECK(stormo_1.velocities_[4].get_x() == 11.2);
    CHECK(stormo_1.velocities_[4].get_y() == 9.4);
    vettore p_6{971.4, 28.9};
    vettore v_6{17.2, -7.4};
    stormo_1.positions_.push_back(p_6);
    stormo_1.velocities_.push_back(v_6);
    stormo_1.wall_hit(5);
    CHECK(stormo_1.velocities_[5].get_x() == -17.2);
    CHECK(stormo_1.velocities_[5].get_y() == 7.4);
  }
}
