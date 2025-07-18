#include <cassert>
#include <string>

#include "SFML/Graphics/Text.hpp"

#include "Counter.hpp"
#include "my_lib.hpp"


Counter::Counter() 
{
    this->obj.setFont(FONT);

    this->count = 0;
    this->obj.setString(std::to_string(0));
    this->obj.setCharacterSize(24);
    this->obj.setFillColor(sf::Color::White);
    this->obj.setPosition(0.0f, 0.0f);
}


sf::Text& Counter::get_obj() 
{
    return this->obj;
}

int Counter::get_count() 
{  
    return this->count;
}


Counter& Counter::operator++()
{
    ++(this->count);
    this->obj.setString(std::to_string(this->count));
    return *this;
}