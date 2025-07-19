#ifndef MY_LIB_HPP
#define MY_LIB_HPP

// #define START_INCREASE_SNAKE
// #define EXPLOSIVE

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Font.hpp"


static const float RECT_SIZE = 16.0f;   // float because of Vector2f
static const float APPLE_SIZE = 16.0f;  // float because of Vector2f
static const int WINDOW_X_SIZE = 800;
static const int WINDOW_Y_SIZE = 600;

enum move_status {UP=1, DOWN, LEFT, RIGHT};
enum speed {LOW, MEDIUM, HIGH};


class RectOsnova 
{
public:
    RectOsnova(RectOsnova *obj); 
    RectOsnova();

    const sf::RectangleShape& get_obj() const;

    const sf::Vector2f& get_position() const;
    void set_position(const sf::Vector2f&);

    const move_status& get_move_status() const;
    void set_move_status(move_status external_move_status);


    bool operator!=(const RectOsnova& R) const
    {
        return &(this->obj) != &(R.get_obj());
    };

private:
    sf::RectangleShape obj;
    move_status status;
};


sf::Vector2f rand_coordinates(int x_limit, int y_limit); 
void movement(RectOsnova& current);
void movement_through_walls(RectOsnova& current);

#endif