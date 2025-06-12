#include <string>
#include <cassert>
#include <iostream>

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "my_lib.hpp"


/* class RectOsnova */
RectOsnova::RectOsnova(RectOsnova *obj) 
{
    this->obj.setSize({RECT_SIZE, RECT_SIZE}); 
    this->obj.setFillColor(sf::Color::Green);

    auto koor = obj->get_position();
    if (obj->get_move_status() == UP)
        this->obj.setPosition({koor.x, koor.y + RECT_SIZE});
    if (obj->get_move_status() == DOWN)
        this->obj.setPosition({koor.x, koor.y - RECT_SIZE});
    if (obj->get_move_status() == LEFT)
        this->obj.setPosition({koor.x + RECT_SIZE, koor.y});
    if (obj->get_move_status() == RIGHT)
        this->obj.setPosition({koor.x - RECT_SIZE, koor.y});
    this->status = obj->get_move_status();
}

RectOsnova::RectOsnova() : status(UP)
{
    this->obj.setSize({RECT_SIZE, RECT_SIZE});
    this->obj.setPosition(rand_coordinates(WINDOW_X_SIZE, WINDOW_Y_SIZE)); 
    this->obj.setFillColor(sf::Color::Yellow);
}

const sf::RectangleShape& RectOsnova::get_obj() const
{
    return obj;
}


const sf::Vector2f& RectOsnova::get_position() const
{
    return obj.getPosition();
}


void RectOsnova::set_position(const sf::Vector2f& pos) 
{
    obj.setPosition(pos);
}


const move_status& RectOsnova::get_move_status() const
{
    return status;
}


void RectOsnova::set_move_status(move_status external_move_status) 
{
    status = external_move_status;
}


/* other functions */
sf::Font load_font() 
{
    sf::Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        printf("font is not loaded\n");
        system("pwd");
        assert(false);
    }
    return font;
}

sf::Vector2f rand_coordinates(int x_limit, int y_limit) 
{
    sf::Vector2f tmp;
    tmp.x = rand() % x_limit;
    tmp.y = rand() % y_limit;

    return tmp;
}

void movement(RectOsnova& current)
{
    auto tmp_k = current.get_position();
    if (current.get_move_status() == UP)
        current.set_position({tmp_k.x, tmp_k.y - RECT_SIZE});
    if (current.get_move_status() == DOWN)
        current.set_position({tmp_k.x, tmp_k.y + RECT_SIZE});
    if (current.get_move_status() == LEFT)
        current.set_position({tmp_k.x - RECT_SIZE, tmp_k.y});
    if (current.get_move_status() == RIGHT)
        current.set_position({tmp_k.x + RECT_SIZE, tmp_k.y});
}

void movement_through_walls(RectOsnova& current)
{
    auto tmp_pos = current.get_position();

    if (tmp_pos.x < -RECT_SIZE)
        current.set_position({WINDOW_X_SIZE, tmp_pos.y});
    else if (tmp_pos.x > WINDOW_X_SIZE)
        current.set_position({-RECT_SIZE, tmp_pos.y});
    else if (tmp_pos.y < -RECT_SIZE)
        current.set_position({tmp_pos.x, WINDOW_Y_SIZE});
    else if (tmp_pos.y > WINDOW_Y_SIZE)
        current.set_position({tmp_pos.x, -RECT_SIZE});
    else
        movement(current);
}