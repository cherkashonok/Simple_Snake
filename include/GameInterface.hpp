#ifndef INNTERFACE_HPP
#define INNTERFACE_HPP

#include "SFML/Graphics/RenderWindow.hpp"


struct settings 
{
    uint32_t speed;
    bool with_walls;
};

class GameInterface 
{

public:
    GameInterface(sf::RenderWindow& window);

    void draw_start_game();
    void draw_settings();
    void draw_game_over(); 

    settings intialize_settings();

private:
    sf::RenderWindow& window;
    
};


#endif