#include <cassert>
#include <string>

#include "SFML/Graphics/Text.hpp"

#include "Counter.hpp"
#include "my_lib.hpp"


Counter::Counter() : hide(true)
{
    if (!font.loadFromFile("my_font.ttf"))
    {
        printf("font is not loaded\n");
        system("pwd");
        assert(false);
    }
    
    // end count
    this->end_count.setFont(font);
    this->end_count.setCharacterSize(24);
    this->end_count.setPosition({300, 100});
    this->end_count.setFillColor(sf::Color::White);


    // счётчик
    this->obj.setFont(font);

    this->count = 0;
    this->obj.setString(std::to_string(0));
    this->obj.setCharacterSize(30);
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

void Counter::reset_count()
{
    this->count = -1;
    ++(*this);
}

bool Counter::get_hide()
{
    return this->hide;
}

sf::Text& Counter::get_end_count()
{
    return this->end_count;
}

void Counter::draw_end_count()
{
    std::string tmp = "Your count: ";
    tmp += std::to_string(this->count);
    this->end_count.setString(tmp);
    this->hide = false;
}

void Counter::hide_end_count()
{
    this->hide = true;
}

Counter& Counter::operator++()
{
    ++(this->count);
    this->obj.setString(std::to_string(this->count));
    return *this;
}