#include "vettore.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

float vettore::get_x() const { return x; };
float vettore::get_y() const { return y; };
void vettore::set_value(float a, float b) {
  x = a;
  y = b;
};
vettore vettore::operator+(vettore b) {
  return {(get_x() + b.get_x()), (get_y() + b.get_y())};
};
vettore vettore::operator-(vettore b) {
  return {(get_x() - b.get_x()), (get_y() - b.get_y())};
};
vettore vettore::operator*(float b) { return {(get_x() * b), (get_y() * b)}; };
vettore vettore::operator/(float b) {
  assert(b != 0);
  return {get_x() / b, get_y() / b};
};
float vettore::norm() { return {sqrt(x * x + y * y)}; };
void vettore::print() {
  std::cout << "(" << get_x() << ", " << get_y() << ")" << '\n';
};

float scalar_prod(vettore a, vettore b) {
  return a.get_x() * b.get_x() + a.get_y() * b.get_y();
};
float angle_between_vectors(vettore a, vettore b) {
  return acos(scalar_prod(a, b) / (a.norm() * b.norm()));
};
