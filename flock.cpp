#include "flock.hpp"

#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

#include "cassert"

vettore null{0, 0};

int const fps = 30;
int const display_width = 1200;
int const display_height = 650;

void flock::initial_structure() {
  if (n <= 0) {
    throw std::runtime_error("invalid number of boids");
  }
  for (float i = 0; i < n; i++) {
    float p_x, p_y, v_x, v_y;
    initial_status_generation(p_x, p_y, v_x, v_y, width, height);
    vettore position{p_x, p_y};
    vettore velocity{v_x, v_y};
    positions.push_back(position);
    velocities.push_back(velocity);
    std::cout << "Bird number " << i + 1 << " position " << '\n';
    positions[i].print();
    std::cout << "Bird number " << i + 1 << " velocity " << '\n';
    velocities[i].print();
  };
  float p_x, p_y, v_x, v_y;
  initial_status_generation(p_x, p_y, v_x, v_y, width, height);
  predator_p = {p_x, p_y};
  predator_v = {v_x, v_y};

  assert(positions.empty() == 0);
  assert(velocities.empty() == 0);
}

vettore flock::v_separation_i(unsigned long int j) {
  vettore v = null;
  for (auto it : positions) {
    if ((it - positions[j]).norm() <= d) {
      v = v - ((it - positions[j]) * s);
    }
  }
  return v;
}
vettore flock::v_allignement1_i(unsigned long int j) {
  return (medium_velocity_j(velocities, velocities_seen, j) - velocities[j]) *
         a;
}

vettore flock::v_cohesion_i(unsigned long int j) {
  return (center_of_mass(positions_seen) - positions[j]) * c;
}
void flock::set_velocities(long unsigned int j) {
  if (velocities_[j].norm() <= 30) {
    velocities_[j] = velocities_[j] * 1.8;
  }
  if (velocities_[j].norm() >= 75.0) {
    velocities_[j] = velocities_[j] * 0.8;
  }
}
void flock::sight_angle(unsigned long int j) {
  for (unsigned long int i = 0; i < positions.size(); i++) {
    vettore distance = positions[i] - positions[j];
    float const max_sight_distance = 300.;
    if ((angle_between_vectors(distance, velocities[j]) > 0) &&
        (angle_between_vectors(distance, velocities[j]) < (M_PI / 2)) &&
        (distance.norm() <= max_sight_distance)) {
      positions_seen.push_back(positions[i]);
      velocities_seen.push_back(velocities[i]);
    }
    if (i == j) {
      positions_seen.push_back(positions[i]);
      velocities_seen.push_back(velocities[i]);
    }
  }
  assert(positions_seen.empty() == 0);
  assert(velocities_seen.empty() == 0);
}
void flock::rules(unsigned long int j) {
  positions_.push_back((velocities[j] / fps) + positions[j]);
  velocities_.push_back((velocities[j] + v_allignement1_i(j) + v_cohesion_i(j) +
                         v_separation_i(j) + predator_repulsion(j)));
  positions_seen.clear();
  velocities_seen.clear();
}
void flock::wall_hit(unsigned long int j) {
  if ((positions_[j].get_y() <= 25) || (positions_[j].get_y() >= height - 25)) {
    velocities_[j].set_value(velocities_[j].get_x(),
                             -1.5 * (velocities_[j].get_y()));
  };
  if ((positions_[j].get_x() <= 25) || (positions_[j].get_x() >= width - 25)) {
    velocities_[j].set_value(-1.5 * (velocities_[j].get_x()),
                             velocities_[j].get_y());
  };
}
bool flock::get_p_check() { return predator_check; }
void flock::set_p_check(bool b) { predator_check = b; }
void flock::predator_simulation() {
  vettore p_temp = predator_p + predator_v / 30;
  vettore v_temp =
      predator_v + ((center_of_mass(positions) - predator_p) * 5 * c);
  if (predator_v.norm() > 35) {
    v_temp = v_temp * 0.8;
  }
  predator_p = p_temp;
  predator_v = v_temp;
}

vettore flock::predator_repulsion(unsigned long int j) {
  vettore res = null;
  vettore distance_ = predator_p - positions_[j];
  if (distance_.norm() < 40) {
    res = distance_ * 80 / (-distance_.norm());
  }
  return res;
}

void flock::simulation() {
  for (unsigned long int j = 0; j < positions.size(); j++) {
    sight_angle(j);
    rules(j);
    wall_hit(j);
    set_velocities(j);
    print_boid_status(positions_, velocities_, j);
    assert(positions_seen.empty() == 1);
    assert(velocities_seen.empty() == 1);
    assert(positions_.empty() == 0);
    assert(velocities_.empty() == 0);
  }
  positions = positions_;
  velocities = velocities_;
  if (get_p_check()) {
    predator_simulation();
  }
  print_statistical_values(positions, velocities);
  positions_.clear();
  velocities_.clear();
};

void initial_status_generation(float& p_x, float& p_y, float& v_x, float& v_y,
                               int w, int h) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 random_generator(seed);
  std::uniform_real_distribution<float> positions_distribution_x((w - h) / 2,
                                                                 (w + h) / 2);
  std::uniform_real_distribution<float> positions_distribution_y(50, h - 50);
  p_x = positions_distribution_x(random_generator);
  p_y = positions_distribution_y(random_generator);
  std::normal_distribution<float> velocities_distribution(200., 30.);
  std::uniform_int_distribution<int> sign_x(0, 1);
  std::uniform_int_distribution<int> sign_y(0, 1);
  int s_x{0};
  int s_y{0};
  if (sign_x(random_generator) == 0) {
    s_x = -1;
  } else {
    s_x = 1;
  };
  if (sign_y(random_generator) == 0) {
    s_y = -1;
  } else {
    s_y = 1;
  };
  v_x = velocities_distribution(random_generator) * s_x;
  v_y = velocities_distribution(random_generator) * s_y;
}
vettore center_of_mass(std::vector<vettore>& positions) {
  vettore res = null;
  if (positions.size() == 1) {
    res = positions[0];
  }
  if (positions.size() > 1) {
    res = (std::accumulate(positions.begin(), positions.end(), null)) /
          positions.size();
  }
  return res;
}
vettore medium_velocity(std::vector<vettore>& velocities) {
  return (std::accumulate(velocities.begin(), velocities.end(), null)) /
         velocities.size();
}
vettore medium_velocity_j(std::vector<vettore>& velocities,
                          std::vector<vettore>& velocities_seen, int j) {
  vettore res = null;
  if (velocities_seen.size() == 1) {
    res = velocities_seen[0];
  }
  if (velocities_seen.size() != 1) {
    res = (std::accumulate(velocities_seen.begin(), velocities_seen.end(),
                           (velocities[j]) * (-1)) /
           (velocities_seen.size() - 1));
  }
  return res;
}
float sdv_medium_velocity(std::vector<vettore>& velocities) {
  float res;
  std::vector<float> mv_scarti_quadratici;
  if (velocities.size() == 1) {
    res = 0.;
  }
  if (velocities.size() != 1) {
    for (unsigned long int i = 0; i < velocities.size(); i++) {
      mv_scarti_quadratici.push_back(
          (velocities[i].norm() - medium_velocity(velocities).norm()) *
          (velocities[i].norm() - medium_velocity(velocities).norm()));
    };
    res = sqrt(std::accumulate(mv_scarti_quadratici.begin(),
                               mv_scarti_quadratici.end(), null.norm()) /
               (velocities.size() - 1));
  }
  return res;
}
float sdv_center_of_mass(std::vector<vettore>& positions) {
  float res;
  std::vector<float> cm_scarti_quadratici;
  if (positions.size() == 1) {
    res = 0.;
  }
  if (positions.size() != 1) {
    for (unsigned long int i = 0; i < positions.size(); i++) {
      cm_scarti_quadratici.push_back(
          (positions[i].norm() - center_of_mass(positions).norm()) *
          (positions[i].norm() - center_of_mass(positions).norm()));
    };
    res = sqrt(std::accumulate(cm_scarti_quadratici.begin(),
                               cm_scarti_quadratici.end(), null.norm()) /
               (positions.size() - 1));
  }
  return res;
}
void print_boid_status(std::vector<vettore>& positions_,
                       std::vector<vettore>& velocities_, int j) {
  std::cout << "boid " << j + 1 << ": " << '\n';
  std::cout << "position = ";
  positions_[j].print();
  std::cout << "velocity = ";
  velocities_[j].print();
}
void print_statistical_values(std::vector<vettore>& positions,
                              std::vector<vettore>& velocities) {
  std::cout << '\n';
  std::cout << "center of mass: ";
  center_of_mass(positions).print();
  std::cout << "sdv center of mass " << sdv_center_of_mass(positions) << '\n';
  std::cout << "medium velocity: ";
  medium_velocity(velocities).print();
  std::cout << "sdv medium velocity " << sdv_medium_velocity(velocities)
            << '\n';
  std::cout << "------------------------" << '\n';
}
