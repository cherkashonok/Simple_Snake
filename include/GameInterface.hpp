#ifndef INNTERFACE_HPP
#define INNTERFACE_HPP

#include "SFML/Graphics/RenderWindow.hpp"
#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"


struct settings 
{
    uint32_t speed;
    bool with_walls;
};


class GameInterface 
{
public:
    GameInterface(sf::RenderWindow& window, tgui::Gui& gui);

    void enable_gui();
    void disable_gui();
    
    void end_game();   
    // void settings();  // ?
    
    // settings intialize_settings(); // ?
    bool get_start_game();
    void set_start_game(bool val);

private:
    sf::RenderWindow& window; 
    tgui::Gui& gui;

    // true -  show play
    // false - show continue
    bool show_play_or_continue = true;         
    bool start_game = false; 
};

#endif