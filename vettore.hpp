#include <vector>

#ifndef VETTORE_HPP
#define VETTORE_HPP

class vettore {
  float x;
  float y;

 public:
  vettore(float x_, float y_) : x{x_}, y{y_} {}

  float get_x() const;
  float get_y() const;
  void set_value(float a, float b);

  vettore operator+(vettore b);
  vettore operator-(vettore b);
  vettore operator*(float b);
  vettore operator/(float b);
  float norm();
  void print();
};

inline float scalar_prod(vettore a, vettore b);
inline float angle_between_vectors(vettore a, vettore b);

#endif
