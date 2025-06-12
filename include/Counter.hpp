#ifndef COUNTER_HPP
#define COUNTER_HPP

#include "SFML/Graphics/Text.hpp"


class Counter 
{

public:
    Counter();

    sf::Text& get_obj();
    int get_count();

    Counter& operator++();

private:
    sf::Text obj;
    sf::Font font;
    int count;
 
};

#endif