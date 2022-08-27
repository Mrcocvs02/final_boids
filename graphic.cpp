#include "graphic.hpp"

#include <math.h>

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "flock.hpp"
#include "vettore.hpp"

float angle(vettore v) {
  float angle = (float)(atan2(v.get_x(), -v.get_y()) * 180 / M_PI);
  return angle;
}

void game::run(int n) {
  flock Flock{10., 0.5, 0.05, 0.01, n, display_width, display_height};
  Flock.initial_structure();

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Simulation");
  window.setFramerateLimit(fps);

  sf::CircleShape boid(2.f, 3);
  boid.setOutlineThickness(1.f);
  boid.setFillColor(sf::Color(28, 229, 198));

  sf::CircleShape predator_shape(4.f);
  predator_shape.setOutlineThickness(1.f);
  predator_shape.setFillColor(sf::Color::Red);

  sf::CircleShape storm_center(2.f);
  storm_center.setOutlineThickness(1.f);
  storm_center.setFillColor(sf::Color::Red);

  const float data_height = (display_height / 5);
  const float data_width = (display_width / 5 + 15);
  sf::RectangleShape data(sf::Vector2f(data_width, data_height));
  data.setFillColor(sf::Color::Transparent);
  data.setOutlineThickness(2.f);
  data.setPosition(2., (display_height - data_height - 2));

  sf::RectangleShape error(sf::Vector2f(10.f, 2.f));
  error.setFillColor(sf::Color::Blue);

  int t = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }
    while (t < 2400) {
      std::cout << "t=" << t << '\n';
      window.clear(sf::Color(22, 28, 72));
      Flock.simulation();
      for (int i = 0; i < Flock.positions.size(); i++) {
        boid.setPosition(Flock.positions[i].get_x(),
                         Flock.positions[i].get_y());
        float theta = angle(Flock.velocities[i]);
        boid.setRotation(theta);
        window.draw(boid);
      }
      predator_shape.setPosition(Flock.predator_p.get_x(),
                                 Flock.predator_p.get_y());
      window.draw(predator_shape);

      float graph_height =
          display_height -
          (data_height * (medium_velocity(Flock.velocities).norm() / 75));
      sf::RectangleShape graph(sf::Vector2f(10, graph_height));
      graph.setFillColor(sf::Color::Red);
      graph.setOutlineThickness(1.f);
      graph.setPosition(10, graph_height);

      storm_center.setFillColor(sf::Color::Red);
      storm_center.setPosition(
          (center_of_mass(Flock.positions).get_x() / 5) - 3,
          display_height - data_height +
              (center_of_mass(Flock.positions).get_y() / 5) - 3);

      sf::CircleShape sdv_storm_center(sdv_center_of_mass(Flock.positions) / 5);
      sdv_storm_center.setOutlineThickness(1.f);
      sdv_storm_center.setFillColor(sf::Color::Transparent);
      sdv_storm_center.setPosition(
          storm_center.getPosition() -
          sf::Vector2f(sdv_center_of_mass(Flock.positions) / 5 - 3,
                       sdv_center_of_mass(Flock.positions) / 5 - 3));

      window.draw(storm_center);
      window.draw(sdv_storm_center);

      error.setPosition(10.,
                        (graph_height - sdv_medium_velocity(Flock.velocities)));
      window.draw(error);
      error.setPosition(10.,
                        (graph_height + sdv_medium_velocity(Flock.velocities)));
      t++;
      window.draw(graph);
      window.draw(error);
      window.draw(data);
      window.display();
    }
  }
}
