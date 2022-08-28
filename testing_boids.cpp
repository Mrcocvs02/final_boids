#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "flock.cpp"
#include "vettore.cpp"

TEST_CASE("testing vettore.cpp") {
  SUBCASE("testing vettore::set_value()") {
    vettore a{0.f, 0.f};
    vettore b{2.f, 3.f};
    a.set_value(2.f, 3.f);
    CHECK(a.get_x() == 2.f);
    CHECK(a.get_y() == 3.f);
    vettore c{-2.f, 6.f};
    c.set_value(b.get_x(), a.get_y());
    CHECK(c.get_x() == 2.f);
    CHECK(c.get_y() == 3.f);
  }

  SUBCASE("testing vettore::operator+()") {
    vettore a{2.f, 0.f};
    vettore b{-4.f, 10.f};
    vettore res_1 = a + b;
    CHECK(res_1.get_x() == -2.f);
    CHECK(res_1.get_y() == 10.f);
    vettore c{2.6f, -9.2f};
    vettore res_2 = b + c;
    CHECK(res_2.get_x() == doctest::Approx(-1.4f));
    CHECK(res_2.get_y() == doctest::Approx(0.8f));
    vettore res_3 = a + b + c;
    CHECK(res_3.get_x() == doctest::Approx(0.6f));
    CHECK(res_3.get_y() == doctest::Approx(0.8f));
  }

  SUBCASE("testing vettore::operator-()") {
    vettore a{2.f, 1.f};
    vettore b{5.f, 6.f};
    vettore res_1 = a - b;
    CHECK(res_1.get_x() == -3.f);
    CHECK(res_1.get_y() == -5.f);
    vettore c{2.3f, 7.1f};
    vettore res_2 = b - c;
    CHECK(res_2.get_x() == doctest::Approx(2.7f));
    CHECK(res_2.get_y() == doctest::Approx(-1.1f));
    vettore res_3 = a - b - c;
    CHECK(res_3.get_x() == doctest::Approx(-5.3f));
    CHECK(res_3.get_y() == doctest::Approx(-12.1f));
  }

  SUBCASE("testing vettore::operator*()") {
    vettore a{2.f, 3.f};
    vettore res_1 = a * 3.f;
    CHECK(res_1.get_x() == 6.f);
    CHECK(res_1.get_y() == 9.f);
    vettore b{1.2f, -5.6f};
    vettore res_2 = b * 2.6;
    CHECK(res_2.get_x() == doctest::Approx(3.12f));
    CHECK(res_2.get_y() == doctest::Approx(-14.56f));
    vettore res_3 = null * 4.6f;
    CHECK(res_3.get_x() == 0.f);
    CHECK(res_3.get_y() == 0.f);
    vettore res_4 = b * 0.f;
    CHECK(res_4.get_x() == 0.f);
    CHECK(res_4.get_y() == 0.f);
  }

  SUBCASE("testing vettore::operator/()") {
    vettore a{1.f, 6.f};
    vettore res_1 = a / 2.f;
    CHECK(res_1.get_x() == 0.5f);
    CHECK(res_1.get_y() == 3.f);
    vettore b{2.4f, 5.1f};
    vettore res_2 = b / 2.7;
    CHECK(res_2.get_x() == doctest::Approx(0.8889f));
    CHECK(res_2.get_y() == doctest::Approx(1.8889f));
    vettore res_3 = null / 4.7f;
    CHECK(res_3.get_x() == 0.f);
    CHECK(res_3.get_y() == 0.f);
  }

  SUBCASE("testing vettore::norm()") {
    vettore a{0.f, 0.f};
    CHECK(a.norm() == 0.f);
    vettore b{10.f, -2.f};
    CHECK(b.norm() == doctest::Approx(10.198f));
    vettore c{13.2f, 0.f};
    CHECK(c.norm() == doctest::Approx(13.2f));
  }

  SUBCASE("testing scalar_prod()") {
    vettore a{0.f, 0.f};
    vettore b{1.f, 2.f};
    CHECK(scalar_prod(a, b) == 0.f);
    vettore c{1.f, 1.f};
    vettore d{1.f, -1.f};
    CHECK(scalar_prod(c, d) == 0.f);
    vettore e{3.56f, -2.3f};
    vettore f{1.11f, 76.57f};
    CHECK(scalar_prod(e, f) == doctest::Approx(-172.159f));
    CHECK(scalar_prod(f, e) == doctest::Approx(-172.159f));
  }

  SUBCASE("angle_between_vectors()") {
    vettore a{1.f, 0.f};
    vettore b{0.f, 1.f};
    CHECK(angle_between_vectors(a, b) == doctest::Approx(M_PI / 2));
    vettore c{0.f, -1.f};
    CHECK(angle_between_vectors(a, c) == doctest::Approx(M_PI / 2));
    vettore d{1.f, 1.f};
    CHECK(angle_between_vectors(a, d) == doctest::Approx(M_PI / 4));
    vettore e{1.f, -1.f};
    CHECK(angle_between_vectors(a, e) == doctest::Approx(M_PI / 4));
    vettore f{-1.f, 1.f};
    CHECK(angle_between_vectors(a, f) == doctest::Approx(3 * M_PI / 4));
    vettore g{-1.f, 1.f};
    CHECK(angle_between_vectors(a, g) == doctest::Approx(3 * M_PI / 4));
    vettore h{-1.f, 0.f};
    CHECK(angle_between_vectors(a, h) == doctest::Approx(M_PI));
  }
}

TEST_CASE("testing flock.cpp") {
  flock Flock_1{10.f, 0.5f, 0.05f, 0.01f, 2, display_width, display_height};
  flock Flock_2{20.f, 1.f, 0.1f, 0.02f, 2, display_width, display_height};
  flock Flock_3{50.f, 2.5f, 0.25f, 0.05f, 2, display_width, display_height};

  SUBCASE("testing flock::centre of mass") {
    vettore a{150.f, 400.f};
    vettore b{500.f, 968.f};
    std::vector<vettore> positions{a, b};
    vettore res_1 = center_of_mass(positions);
    CHECK(res_1.get_x() == 325.f);
    CHECK(res_1.get_y() == 684.f);
    vettore c{0.57f, -567.2f};
    positions.push_back(c);
    vettore res_2 = center_of_mass(positions);
    CHECK(res_2.get_x() == doctest::Approx(216.857f));
    CHECK(res_2.get_y() == doctest::Approx(266.933f));
    positions.clear();
    positions.push_back(null);
    vettore res_3 = center_of_mass(positions);
    CHECK(res_3.get_x() == 0);
    CHECK(res_3.get_y() == 0.);
    positions.clear();
    vettore d{12.5f, 13.6f};
    positions.push_back(d);
    vettore res_4 = center_of_mass(positions);
    CHECK(res_4.get_x() == 12.5f);
    CHECK(res_4.get_y() == 13.6f);
  }

  SUBCASE("testing flock::medium_velocity") {
    vettore a{120.f, 300.f};
    vettore b{23.56f, -378.77f};
    std::vector<vettore> velocities{a, b};
    vettore res_1 = medium_velocity(velocities);
    CHECK(res_1.get_x() == doctest::Approx(71.78f));
    CHECK(res_1.get_y() == doctest::Approx(-39.385f));
    velocities.push_back(null);
    vettore res_2 = medium_velocity(velocities);
    CHECK(res_2.get_x() == doctest::Approx(47.853f));
    CHECK(res_2.get_y() == doctest::Approx(-26.2568f));
    velocities.clear();
    velocities = {null, null};
    vettore res_3 = medium_velocity(velocities);
    CHECK(res_3.get_x() == 0.f);
    CHECK(res_3.get_y() == 0.f);
    velocities.clear();
    vettore c{22.3f, 12.7f};
    velocities.push_back(c);
    vettore res_4 = medium_velocity(velocities);
    CHECK(res_4.get_x() == 22.3f);
    CHECK(res_4.get_y() == 12.7f);
  }

  SUBCASE("testing medium_velocities_j()") {
    vettore a{10.f, 20.f};
    vettore b{24.6f, 88.5f};
    vettore c{3.2f, 6.5f};
    vettore d{44.3f, 76.2f};
    std::vector<vettore> velocities{a, b, c, d};
    std::vector<vettore> velocities_seen{a, b, c};
    vettore res_1 = medium_velocity_j(velocities, velocities_seen, 0);
    CHECK(res_1.get_x() == doctest::Approx(13.9f));
    CHECK(res_1.get_y() == 47.5f);
    vettore res_2 = medium_velocity_j(velocities, velocities_seen, 1);
    CHECK(res_2.get_x() == 6.6f);
    CHECK(res_2.get_y() == 13.25f);
    velocities_seen.clear();
    velocities_seen.push_back(d);
    vettore res_3 = medium_velocity_j(velocities, velocities_seen, 0);
    CHECK(res_3.get_x() == 44.3f);
    CHECK(res_3.get_y() == 76.2f);
    Flock_1.velocities_seen.clear();
    Flock_1.positions_seen.clear();
  }

  SUBCASE("testing flock::sdv_center_of_mass()") {
    vettore p_1{150.f, 400.f};
    vettore p_2{500.f, 968.f};
    std::vector<vettore> positions{p_1, p_2};
    double res_1 = sdv_center_of_mass(positions);
    CHECK(res_1 == doctest::Approx(468.324));
    vettore p_3{0.57f, -567.2f};
    positions.push_back(p_3);
    double res_2 = sdv_center_of_mass(positions);
    CHECK(res_2 == doctest::Approx(553.485f));
    positions.clear();
    vettore p_4{200.2f, 387.5f};
    vettore p_5{200.2f, 387.5f};
    positions = {p_4, p_5};
    double res_3 = sdv_center_of_mass(positions);
    CHECK(res_3 == 0.f);
    positions.clear();
    positions.push_back(p_1);
    double res_4 = sdv_center_of_mass(positions);
    CHECK(res_4 == 0.f);
  }

  SUBCASE("testing flock::sdv_medium_velocity()") {
    vettore v_1{120.f, 300.f};
    vettore v_2{23.56f, -378.77f};
    std::vector<vettore> velocities{v_1, v_2};
    double res_1 = sdv_medium_velocity(velocities);
    CHECK(res_1 == doctest::Approx(383.1134f));
    vettore v_3{56.3f, 158.6f};
    velocities.push_back(v_3);
    double res_2 = sdv_medium_velocity(velocities);
    CHECK(res_2 == doctest::Approx(289.1628f));
    velocities.clear();
    vettore v_4{24.5f, 67.4f};
    vettore v_5{24.5f, 67.4f};
    velocities = {v_4, v_5};
    double res_3 = sdv_medium_velocity(velocities);
    CHECK(res_3 == 0.f);
    velocities.clear();
    velocities.push_back(v_1);
    double res_4 = sdv_medium_velocity(velocities);
    CHECK(res_4 == 0.f);
  }

  SUBCASE("testing flock::v_separation_j()") {
    vettore p_1{300.1f, 350.4f};
    vettore p_2{360.3f, 270.7f};
    Flock_1.positions = {p_1, p_2};
    vettore res_1 = Flock_1.v_separation_i(0);
    vettore res_2 = Flock_1.v_separation_i(1);
    CHECK(res_1.get_x() == 0.f);
    CHECK(res_1.get_y() == 0.f);
    CHECK(res_2.get_x() == 0.f);
    CHECK(res_2.get_y() == 0.f);
    vettore p_3{301.1f, 351.3f};
    Flock_1.positions.push_back(p_3);
    vettore res_3 = Flock_1.v_separation_i(0);
    vettore res_4 = Flock_1.v_separation_i(2);
    CHECK(res_3.get_x() == doctest::Approx(-0.5f));
    CHECK(res_3.get_y() == doctest::Approx(-0.45f));
    CHECK(res_4.get_x() == doctest::Approx(0.5f));
    CHECK(res_4.get_y() == doctest::Approx(0.45f));
    Flock_2.positions = Flock_1.positions;
    vettore res_5 = Flock_2.v_separation_i(0);
    vettore res_6 = Flock_2.v_separation_i(2);
    CHECK(res_5.get_x() == doctest::Approx(-1.f));
    CHECK(res_5.get_y() == doctest::Approx(-0.9f));
    CHECK(res_6.get_x() == doctest::Approx(1.f));
    CHECK(res_6.get_y() == doctest::Approx(0.9f));
    Flock_3.positions = Flock_1.positions;
    vettore res_7 = Flock_3.v_separation_i(0);
    vettore res_8 = Flock_3.v_separation_i(2);
    CHECK(res_7.get_x() == doctest::Approx(-2.5f));
    CHECK(res_7.get_y() == doctest::Approx(-2.25f));
    CHECK(res_8.get_x() == doctest::Approx(2.5f));
    CHECK(res_8.get_y() == doctest::Approx(2.25f));
  }

  SUBCASE("testing flock::v_allignement_i") {
    vettore p_1{300.1f, 361.5f};
    vettore p_2{365.2f, 388.3f};
    vettore v_1{20.1f, 30.3f};
    vettore v_2{12.4f, 32.2f};
    Flock_1.positions = {p_1, p_2};
    Flock_1.velocities = {v_1, v_2};
    Flock_1.sight_angle(0);
    vettore res_1 = Flock_1.v_allignement1_i(0);
    CHECK(res_1.get_x() == doctest::Approx(-0.385f));
    CHECK(res_1.get_y() == doctest::Approx(0.095f));
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_3{250.f, 270.f};
    vettore v_3{17.0f, 28.2f};
    Flock_1.positions.push_back(p_3);
    Flock_1.velocities.push_back(v_3);
    Flock_1.sight_angle(2);
    vettore res_2 = Flock_1.v_allignement1_i(2);
    CHECK(res_2.get_x() == doctest::Approx(-0.0375f));
    CHECK(res_2.get_y() == doctest::Approx(0.1525f));
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.velocities[1].set_value(-12.4f, -32.2f);
    Flock_1.sight_angle(2);
    vettore res_3 = Flock_1.v_allignement1_i(2);
    CHECK(res_3.get_x() == doctest::Approx(-0.6575f));
    CHECK(res_3.get_y() == doctest::Approx(-1.4575f));
    Flock_2.positions = Flock_1.positions;
    Flock_2.velocities = Flock_1.velocities;
    Flock_2.sight_angle(2);
    vettore res_4 = Flock_2.v_allignement1_i(2);
    CHECK(res_4.get_x() == doctest::Approx(-1.315f));
    CHECK(res_4.get_y() == doctest::Approx(-2.915f));
    Flock_3.positions = Flock_1.positions;
    Flock_3.velocities = Flock_1.velocities;
    Flock_3.sight_angle(2);
    vettore res_5 = Flock_3.v_allignement1_i(2);
    CHECK(res_5.get_x() == doctest::Approx(-3.2875f));
    CHECK(res_5.get_y() == doctest::Approx(-7.2875f));
  }

  SUBCASE("testing flock::v_cohesion_i()") {
    vettore p_1{100.2f, 165.3f};
    vettore v_1{10.2f, 15.1f};
    vettore p_2{276.8f, 245.6f};
    vettore v_2{12.7f, 13.4f};
    Flock_1.positions = {p_1, p_2};
    Flock_1.velocities = {v_1, v_2};
    Flock_1.sight_angle(0);
    vettore res_1 = Flock_1.v_cohesion_i(0);
    CHECK(res_1.get_x() == doctest::Approx(0.883f));
    CHECK(res_1.get_y() == doctest::Approx(0.4015f));
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_3{298.7f, 301.2f};
    vettore v_3{22.3f, 18.5f};
    Flock_1.positions.push_back(p_3);
    Flock_1.velocities.push_back(v_3);
    Flock_1.sight_angle(0);
    vettore res_2 = Flock_1.v_cohesion_i(0);
    CHECK(res_2.get_x() == doctest::Approx(1.25033f));
    CHECK(res_2.get_y() == doctest::Approx(0.720667f));
    Flock_2.positions = Flock_1.positions;
    Flock_2.velocities = Flock_1.velocities;
    Flock_2.sight_angle(0);
    vettore res_3 = Flock_2.v_cohesion_i(0);
    CHECK(res_3.get_x() == doctest::Approx(2.50067f));
    CHECK(res_3.get_y() == doctest::Approx(1.44133f));
    Flock_3.positions = Flock_1.positions;
    Flock_3.velocities = Flock_1.velocities;
    Flock_3.sight_angle(0);
    vettore res_4 = Flock_3.v_cohesion_i(0);
    CHECK(res_4.get_x() == doctest::Approx(6.25167f));
    CHECK(res_4.get_y() == doctest::Approx(3.60333f));
  }

  SUBCASE("testing flock::sight_angle()") {
    vettore p_1{200.4f, 300.2f};
    vettore v_1{10.3f, 15.3f};
    vettore p_2{400.7f, 500.9f};
    vettore v_2{20.1f, 10.4f};
    Flock_1.positions = {p_1, p_2};
    Flock_1.velocities = {v_1, v_2};
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 2);
    CHECK(Flock_1.velocities_seen.size() == 2);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.4f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 10.3f);
    CHECK(Flock_1.positions_seen[1].get_x() == 400.7f);
    CHECK(Flock_1.velocities_seen[1].get_x() == 20.1f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_3{950.f, 930.5f};
    vettore v_3{15.1f, 10.2f};
    Flock_1.positions.push_back(p_3);
    Flock_1.velocities.push_back(v_3);
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 2);
    CHECK(Flock_1.velocities_seen.size() == 2);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.4f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 10.3f);
    CHECK(Flock_1.positions_seen[1].get_x() == 400.7f);
    CHECK(Flock_1.velocities_seen[1].get_x() == 20.1f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_4{152.7f, 149.8f};
    vettore v_4{15.1f, -13.2f};
    Flock_1.positions = {p_1, p_2, p_3, p_4};
    Flock_1.velocities = {v_1, v_2, v_3, v_4};
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 2);
    CHECK(Flock_1.velocities_seen.size() == 2);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.4f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 10.3f);
    CHECK(Flock_1.positions_seen[1].get_x() == 400.7f);
    CHECK(Flock_1.velocities_seen[1].get_x() == 20.1f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.positions[0].set_value(500.5f, 102.4f);
    Flock_1.sight_angle(1);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 400.7f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 20.1f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.positions.clear();
    Flock_1.velocities.clear();
    vettore p_5{300.2f, 200.3f};
    vettore v_5{3.f, 0.f};
    vettore p_6{299.2f, 202.3f};
    vettore v_6{12.f, 4.f};
    Flock_1.positions = {p_5, p_6};
    Flock_1.velocities = {v_5, v_6};
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 300.2f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 3.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_7{300.2f, 630.5f};
    vettore v_7{25.7f, 42.1f};
    Flock_1.positions.push_back(p_7);
    Flock_1.velocities.push_back(v_7);
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_y() == 200.3f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 3.f);
    Flock_1.positions.clear();
    Flock_1.velocities.clear();
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.positions = {p_5, p_7};
    Flock_1.velocities = {v_5, v_7};
    Flock_1.velocities[1].set_value(0.f, 4.f);
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_y() == 200.3f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 3.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.sight_angle(1);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_y() == 630.5f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 0.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    v_7.set_value(0.f, 4.f);
    Flock_1.positions = {p_5, p_6, p_7};
    Flock_1.velocities = {v_5, v_6, v_7};
    Flock_1.sight_angle(1);
    CHECK(Flock_1.positions_seen.size() == 2);
    CHECK(Flock_1.velocities_seen.size() == 2);
    CHECK(Flock_1.positions_seen[0].get_y() == 200.3f);
    CHECK(Flock_1.positions_seen[1].get_x() == 299.2f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 3.f);
    CHECK(Flock_1.velocities_seen[1].get_x() == 12.f);
    Flock_1.positions.clear();
    Flock_1.velocities.clear();
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_8{200.f, 300.f};
    vettore v_8{0.f, 2.f};
    vettore p_9{200.f, 300.f};
    vettore v_9{3.f, 0.f};
    Flock_1.positions = {p_8, p_9};
    Flock_1.velocities = {v_8, v_9};
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 0.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    vettore p_10{500.f, 300.f};
    vettore v_10{0.f, 3.f};
    Flock_1.positions.push_back(p_10);
    Flock_1.velocities.push_back(v_10);
    Flock_1.sight_angle(0);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 0.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.sight_angle(1);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 200.f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 3.f);
    Flock_1.positions_seen.clear();
    Flock_1.velocities_seen.clear();
    Flock_1.sight_angle(2);
    CHECK(Flock_1.positions_seen.size() == 1);
    CHECK(Flock_1.velocities_seen.size() == 1);
    CHECK(Flock_1.positions_seen[0].get_x() == 500.f);
    CHECK(Flock_1.velocities_seen[0].get_x() == 0.f);
  };

  SUBCASE("testing flock::wall_hit()") {
    vettore p_1{1176.3f, 400.5f};
    vettore v_1{23.3f, 25.4f};
    Flock_1.positions_.push_back(p_1);
    Flock_1.velocities_.push_back(v_1);
    Flock_1.wall_hit(0);
    CHECK(Flock_1.velocities_[0].get_x() == doctest::Approx(-34.95f));
    CHECK(Flock_1.velocities_[0].get_y() == 25.4f);
    vettore p_2{356.4f, 1177.6f};
    vettore v_2{17.2f, 14.5f};
    Flock_1.positions_.push_back(p_2);
    Flock_1.velocities_.push_back(v_2);
    Flock_1.wall_hit(1);
    CHECK(Flock_1.velocities_[1].get_x() == 17.2f);
    CHECK(Flock_1.velocities_[1].get_y() == doctest::Approx(-21.75f));
    vettore p_3{1175.3f, 1178.2f};
    vettore v_3{21.2f, 18.3f};
    Flock_1.positions_.push_back(p_3);
    Flock_1.velocities_.push_back(v_3);
    Flock_1.wall_hit(2);
    CHECK(Flock_1.velocities_[2].get_x() == doctest::Approx(-31.8f));
    CHECK(Flock_1.velocities_[2].get_y() == doctest::Approx(-27.45f));
    vettore p_4{24.3f, 56.9f};
    vettore v_4{-12.2f, 8.7f};
    Flock_1.positions_.push_back(p_4);
    Flock_1.velocities_.push_back(v_4);
    Flock_1.wall_hit(3);
    CHECK(Flock_1.velocities_[3].get_x() == doctest::Approx(18.3f));
    CHECK(Flock_1.velocities_[3].get_y() == 8.7f);
    vettore p_5{23.6f, 24.4f};
    vettore v_5{-11.2f, -9.4f};
    Flock_1.positions_.push_back(p_5);
    Flock_1.velocities_.push_back(v_5);
    Flock_1.wall_hit(4);
    CHECK(Flock_1.velocities_[4].get_x() == doctest::Approx(16.8f));
    CHECK(Flock_1.velocities_[4].get_y() == doctest::Approx(14.1f));
    vettore p_6{1176.4f, 24.9f};
    vettore v_6{17.2f, -7.4f};
    Flock_1.positions_.push_back(p_6);
    Flock_1.velocities_.push_back(v_6);
    Flock_1.wall_hit(5);
    CHECK(Flock_1.velocities_[5].get_x() == doctest::Approx(-25.8f));
    CHECK(Flock_1.velocities_[5].get_y() == doctest::Approx(11.1f));
  };

  SUBCASE("testing flock::predator_simulation()") {
    Flock_1.predator_p = {300.f, 300.f};
    Flock_1.predator_v = {10.f, 20.f};
    vettore a{150.f, 400.f};
    vettore b{500.f, 968.f};
    Flock_1.positions = {a, b};
    Flock_1.predator_simulation();
    CHECK(Flock_1.predator_v.get_x() == doctest::Approx(11.25f));
    CHECK(Flock_1.predator_v.get_y() == doctest::Approx(39.2f));
    CHECK(Flock_1.predator_p.get_x() == doctest::Approx(300.333f));
    CHECK(Flock_1.predator_p.get_y() == doctest::Approx(300.667f));
    Flock_1.predator_simulation();
    CHECK(Flock_1.predator_v.get_x() == doctest::Approx(9.98667f));
    CHECK(Flock_1.predator_v.get_y() == doctest::Approx(46.6933f));
    CHECK(Flock_1.predator_p.get_x() == doctest::Approx(300.708f));
    CHECK(Flock_1.predator_p.get_y() == doctest::Approx(301.973f));
  }

  SUBCASE("testing flock::predator_repulsion()") {
    Flock_1.predator_p = {300.f, 300.f};
    Flock_1.predator_v = {10.f, 20.f};
    vettore p_1{325.f, 280.f};
    vettore v_1{12.2f, 21.3f};
    Flock_1.positions_ = {p_1};
    Flock_1.velocities_ = {v_1};
    vettore res_1 = Flock_1.predator_repulsion(0);
    CHECK(res_1.get_x() == doctest::Approx(62.4695f));
    CHECK(res_1.get_y() == doctest::Approx(-49.9756f));
    Flock_1.positions_.clear();
    Flock_1.velocities_.clear();
    vettore p_2{345.f, 250.f};
    vettore v_2{12.2f, 21.3f};
    Flock_1.positions_.push_back(p_2);
    Flock_1.velocities_.push_back(v_2);
    vettore res_2 = Flock_1.predator_repulsion(0);
    CHECK(res_2.get_x() == doctest::Approx(0.f));
    CHECK(res_2.get_y() == doctest::Approx(0.f));
  }
}
