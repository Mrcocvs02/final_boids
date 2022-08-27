#include <iostream>
#include <vector>

#include "flock.hpp"
#include "vettore.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

 #ifndef GRAPHIC_HPP
 #define GRAPHIC_HPP

class game {
    private:
    sf::RenderWindow window;
    const int fps;
    const int display_height;
    const int display_width;
    bool play_check = true;
    

    public:
    game():
    display_height{650}, display_width{1200}, fps{30}{}
    void run(int n);
    void close (sf::RenderWindow& window);
    
    bool get_play_check(){return play_check;}
    void set_play_check(bool b){play_check=b;}
    void play(flock& flock);

};
inline float angle();
inline void predator_movement(sf::CircleShape& predator_shape, flock& Flock);

#endif