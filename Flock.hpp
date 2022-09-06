#include <chrono>
#include <numeric>
#include <random>

#include "Vettore.hpp"

#ifndef FLOCK_HPP
#define FLOCK_HPP

class flock {
  float d;
  float s;
  float a;
  float c;
  int n;
  int width;
  int height;
  bool predator_check = true;

 public:
  flock(float d_, float s_, float a_, float c_, int n_, int w_, int h_)
      : d{d_}, s{s_}, a{a_}, c{c_}, n{n_}, width{w_}, height{h_} {}

  std::vector<vettore> velocities;
  std::vector<vettore> positions;
  std::vector<vettore> positions_;
  std::vector<vettore> velocities_;
  std::vector<vettore> positions_seen;
  std::vector<vettore> velocities_seen;

  vettore predator_p{0, 0};
  vettore predator_v{0, 0};

  void predator_simulation();
  vettore predator_repulsion(unsigned long int j);
  bool get_p_check() const;
  void set_p_check(bool const b);

  vettore v_separation_i(unsigned long int j);
  vettore v_allignement1_i(unsigned long int j);
  vettore v_cohesion_i(unsigned long int j);

  void initial_structure();
  void sight_angle(unsigned long int j);
  void rules(unsigned long int j);
  void set_velocities(unsigned long int j);
  void wall_hit(unsigned long int j);
  void simulation();
};

void initial_status_generation(float& p_x, float& p_y, float& v_x, float& v_y,
                               int w, int h);
vettore center_of_mass(std::vector<vettore>& positions);
float medium_distance(std::vector<vettore>& positions);
vettore medium_velocity(std::vector<vettore>& velocities);
vettore medium_velocity_j(std::vector<vettore>& velocities,
                          std::vector<vettore>& velocities_seen, int j);
float sdv_medium_velocity(std::vector<vettore>& velocities);
float sdv_center_of_mass(std::vector<vettore>& positions);
float sdv_medium_distance(std::vector<vettore>& positions);
void print_statistical_values(std::vector<vettore>& positions,
                              std::vector<vettore>& velocities);

#endif
