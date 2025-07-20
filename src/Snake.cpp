#include <iostream>
#include <unordered_set>
#include <list>
#include <fstream>
#include <ios>

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "Snake.hpp"
#include "my_lib.hpp"


Snake::Snake(settings& sett) : count_logs(1), s(sett)
{
    file.open("snake_log.txt", std::ios::out | std::ios::trunc);

    snake.push_back(RectOsnova());
    snake.push_back(RectOsnova(&(snake.back())));
    all_directions.push_back(UP);
    all_directions.push_back(UP);
}

Snake::~Snake()
{
    file.close();
}

void Snake::log_snake()
{
    file << count_logs << "\n----------------------------------------\n";
    for(auto& el : snake)
        file << "x - " << el.get_position().x << ", "
             << "y - " << el.get_position().y << ";\n";
    file << "----------------------------------------\n\n";

    count_logs++;
}


RectOsnova& Snake::get_lead_rect()
{
    return snake.front();
}

std::unordered_set<sf::Vector2f, hash_Vector2f, equal_to_Vector2f> Snake::get_snake(bool with_head=true) 
{
    auto equal_to = [] (const sf::Vector2f& r_1, const sf::Vector2f& r_2) 
                    {return r_1.x == r_2.x && r_1.y == r_2.y;};
    // can be upgraded
    auto hash = [] (const sf::Vector2f& r) 
                {return r.x * 17 + r.y * 31;};

    std::unordered_set<sf::Vector2f, hash_Vector2f, equal_to_Vector2f> snake_koor(10, hash, equal_to);
    for(auto& el : snake)
        if (with_head || el != get_lead_rect())
            snake_koor.insert(el.get_position());
    
    return snake_koor;
}


void Snake::update()
{
    if (!s.with_walls)
    {
        for(auto it = snake.begin(); it != snake.end(); it++) 
            movement_through_walls(*it);
    }
    else
    {
        for(auto it = snake.begin(); it != snake.end(); it++) 
            movement(*it);
    }

    all_directions.pop_back();
    all_directions.push_front(all_directions.front());

    auto it_1 = all_directions.begin();
    for(auto& el : snake)
    {
        el.set_move_status(*it_1);
        ++it_1;
    }
}

void Snake::draw(sf::RenderWindow& window) 
{
    for(auto& el : snake) 
        window.draw(el.get_obj());
}


bool Snake::is_alive()
{
    auto tmp = get_lead_rect().get_position();
    if (s.with_walls && (tmp.x < 0 || tmp.y < 0))
    {
        #ifdef EXPLOSIVE
            throw std::exception("107 line Snake.cpp");
        #endif
        return false;
    }
    else if (s.with_walls)
    {
        bool usl_x = tmp.x > WINDOW_X_SIZE - RECT_SIZE;
        bool usl_y = tmp.y > WINDOW_Y_SIZE - RECT_SIZE;
        if (usl_x || usl_y)
        {
            #ifdef EXPLOSIVE
                throw std::exception("116 line Snake.cpp");
            #endif
            return false;
        }
    }

    for(auto& el : get_snake(false))
    {
        bool for_x = el.x >= tmp.x+RECT_SIZE || el.x+RECT_SIZE <= tmp.x;
        bool for_y = el.y >= tmp.y+RECT_SIZE || el.y+RECT_SIZE <= tmp.y;

        if (!for_x && !for_y)
        {
            #ifdef EXPLOSIVE
                throw std::exception("128 line Snake.cpp");
            #endif
            return false;
        }
    }

    return true;
}


void Snake::up()
{
    if (snake.front().get_move_status() != DOWN)
    {
        all_directions.front() = UP;
        snake.front().set_move_status(UP);
    }
}

void Snake::down()
{
    if (snake.front().get_move_status() != UP)
    {
        all_directions.front() = DOWN;
        snake.front().set_move_status(DOWN);
    }
}

void Snake::left()
{
    if (snake.front().get_move_status() != RIGHT)
    {
        all_directions.front() = LEFT;
        snake.front().set_move_status(LEFT);
    }
}

void Snake::right()
{
    if (snake.front().get_move_status() != LEFT)
    {
        all_directions.front() = RIGHT;
        snake.front().set_move_status(RIGHT);
    }
}


void Snake::operator++() 
{
    snake.push_back(RectOsnova(&(snake.back()))); 
    all_directions.push_back(snake.back().get_move_status());
}