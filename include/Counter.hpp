#ifndef COUNTER_HPP
#define COUNTER_HPP

#include "SFML/Graphics/Text.hpp"


class Counter 
{
public:
    Counter();

    sf::Text& get_obj();
    int get_count();
    void reset_count();

    sf::Text& get_end_count();
    bool get_hide();
    void draw_end_count();
    void hide_end_count();

    Counter& operator++();

private:
    sf::Text end_count;
    bool hide;

    sf::Text obj;
    sf::Font font;
    int count;
};

#endif