#include <SFML/Graphics.hpp>
#include <iostream>

#include "flock.cpp"
#include "vettore.cpp"
#include "Graphic.cpp"

int main() {
  int n;
  std::cout << "insert the number of birds you want in the flock" << '\n';
  std::cin >> n;
  const int display_height=650;
  const int display_width=1200;
  game gioco;
  gioco.run(n);
  return 0;
}