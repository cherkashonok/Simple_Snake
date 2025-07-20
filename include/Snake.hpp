#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <functional>
#include <unordered_set>
#include <vector>
#include <list>
#include <fstream>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include "my_lib.hpp"

using hash_Vector2f = std::function<int(const sf::Vector2f&)>;
using equal_to_Vector2f = std::function<bool(const sf::Vector2f&, const sf::Vector2f&)>;


class Snake 
{

public:
    Snake(settings& sett);
    ~Snake();
    void log_snake();

    RectOsnova& get_lead_rect();
    std::unordered_set<sf::Vector2f, hash_Vector2f, equal_to_Vector2f> get_snake(bool with_head);

    void draw(sf::RenderWindow& window);
    void update();

    bool is_alive();
    
    void up();
    void down();
    void left();
    void right();

    void operator++(); // increase snake

private:
    std::vector<RectOsnova> snake;
    std::list<move_status> all_directions;

    std::ofstream file;
    uint64_t count_logs;

    settings& s;
};


#endif