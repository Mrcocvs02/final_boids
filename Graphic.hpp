#include <iostream>
#include <vector>

#include "Flock.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Vettore.hpp"

#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

class game {
 private:
  sf::RenderWindow window;
  const int fps = 30;
  const int display_height = 650;
  const int display_width = 1200;
  bool play_check = true;

 public:
  void run(flock& Flock);
  void close_window();

  bool get_play_check();
  void set_play_check(bool b);
  void play(flock& flock);
};
float angle();
void predator_movement(flock& Flock);

#endif
