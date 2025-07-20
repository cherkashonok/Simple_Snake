#ifndef APPLE_HPP
#define APPLE_HPP

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

#include "Snake.hpp"
#include <memory>


class Apple 
{

public:
    Apple(std::shared_ptr<Snake>& snake);

    sf::RectangleShape& get_obj();
    sf::Vector2f get_position();

    bool check_snake_in_apple();
    void update();

private:
    sf::RectangleShape obj;
    std::shared_ptr<Snake>& snake;

};

#endif