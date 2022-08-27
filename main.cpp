#include <SFML/Graphics.hpp>
#include <iostream>

#include "flock.cpp"
#include "vettore.cpp"
#include "Graphic.cpp"

int main() {
  int n;
  std::cout << "insert the number of birds you want in the flock" << '\n';
  std::cin >> n;
  game gioco;
  gioco.run(n);
  return 0;
}