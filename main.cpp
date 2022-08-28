#include <SFML/Graphics.hpp>
#include <iostream>

#include "flock.cpp"
#include "graphic.cpp"
#include "vettore.cpp"

int main() {
  int n;
  std::cout << "insert the number of birds you want in the flock" << '\n';
  std::cin >> n;
  std::cout << "press d to use default parameters," << '\n'
            << "or press s to choose them" << '\n';
  char condition;
  std::cin >> condition;
  std::cout << '\n';
  if ((condition != 100) && (condition != 115)) {
    throw std::runtime_error("invalid condition");
  }
  if (condition == 100) {
    std::cout << "P = stop-start flock movement" << '\n'
              << "C = stop predator movement" << '\n'
              << "A = start predator movement" << '\n'
              << "left-right-up-down = move the predator" << '\n'
              << "esc = close the simulation" << '\n'
              << '\n'
              << "insert any key to start the simulation" << '\n';
    char start;
    std::cin >> start;
    std::cout << '\n';
    game gioco;
    flock Flock_d{10., 0.5, 0.05, 0.01, n, display_width, display_height};
    gioco.run(Flock_d);
  }
  if (condition == 115) {
    std::cout << "insert separation distance" << '\n';
    float d;
    std::cin >> d;
    std::cout << '\n' << "insert separation coefficient" << '\n';
    float s;
    std::cin >> s;
    std::cout << '\n' << "insert allineament coefficient" << '\n';
    float a;
    std::cin >> a;
    std::cout << '\n' << "insert cohesion coefficient" << '\n';
    float c;
    std::cin >> c;
    std::cout << '\n'
              << "P = stop-start flock movement" << '\n'
              << "C = stop predator movement" << '\n'
              << "A = start predator movement" << '\n'
              << "left-right-up-down = move the predator" << '\n'
              << "esc = close the simulation" << '\n'
              << '\n'
              << "insert any key to start the simulation" << '\n';
    char start;
    std::cin >> start;
    std::cout << '\n';
    game gioco;
    flock Flock_s{d, s, a, c, n, display_width, display_height};
    gioco.run(Flock_s);
  }
  return 0;
}
