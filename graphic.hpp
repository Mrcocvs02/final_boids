#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "flock.hpp"
#include "vettore.hpp"

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class game {
 private:
  sf::RenderWindow window;
  const int fps;
  const int display_height;
  const int display_width;

 public:
  game() : display_height{650}, display_width{1200}, fps{30} {}
  void run(int n);
};
inline float angle();

#endif
