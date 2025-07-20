#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

#include "Apple.hpp"
#include "Snake.hpp"
#include "my_lib.hpp"


Apple::Apple(std::shared_ptr<Snake>& snake) : snake(snake) 
{
    obj.setSize({APPLE_SIZE, APPLE_SIZE});
    obj.setFillColor(sf::Color::Red);
    update();
}

void Apple::update()
{
    auto tmp = rand_coordinates(WINDOW_X_SIZE - APPLE_SIZE, WINDOW_Y_SIZE - APPLE_SIZE);
    auto snake_koor = snake->get_snake(true);
    int status = 0;

    for(auto& el : snake_koor) 
    {
        // условие существования по x
        bool for_x = el.x > tmp.x+15 || el.x+RECT_SIZE < tmp.x;
        // условие существования по y
        bool for_y = el.y > tmp.y+15 || el.y+RECT_SIZE < tmp.y;
        // !(for_x || for_y)
        if (!for_x && !for_y) 
        {
            update();
            status = 1;
            break;
        }   
    }

    if (!status)
        obj.setPosition(tmp.x, tmp.y);
}

bool Apple::check_snake_in_apple() 
{
    auto snake_k = snake->get_lead_rect().get_position();
    auto apple_k = obj.getPosition();

    // условие существования по x
    bool for_x = snake_k.x > apple_k.x + 10 || snake_k.x + RECT_SIZE < apple_k.x;
    // условие существования по y
    bool for_y = snake_k.y > apple_k.y + 10 || snake_k.y + RECT_SIZE < apple_k.y;
    // !(for_x || for_y)
    if (!for_x && !for_y)
        // apple in snake
        return true;
    else
        // apple not in snake
        return false;
}

sf::RectangleShape& Apple::get_obj() 
{
    return obj;
}

sf::Vector2f Apple::get_position()
{
    return obj.getPosition();
}
