#ifndef INNTERFACE_HPP
#define INNTERFACE_HPP

#include "SFML/Graphics/RenderWindow.hpp"
#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"

#include "my_lib.hpp"
#include "Counter.hpp"

class GameInterface 
{
public:
    GameInterface(sf::RenderWindow& window, tgui::Gui& gui, Counter& counter);

    void draw_gui();
    void hide_gui();
    void draw_settings();
    void hide_settings();
    void draw_end_game();    
    
    settings& get_settings(); 
    bool get_start_game();
    void set_start_game(bool val);

private:
    sf::RenderWindow& window; 
    tgui::Gui& gui;
    Counter& counter;
    settings s;

    // true -  show play
    // false - show continue
    bool show_play_or_continue = true;         
    bool start_game = false; 
};

#endif