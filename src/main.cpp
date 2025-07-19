#include <iostream>
#include <cstdlib>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include "TGUI/Backend/SFML-Graphics.hpp"

#include "Snake.hpp"
#include "Apple.hpp"
#include "Counter.hpp"
#include "GameInterface.hpp"
#include "my_lib.hpp"


int main() 
{
    srand(time(NULL)); 

    sf::RenderWindow window(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Simple Snake");
    uint32_t fps = 4;
    window.setFramerateLimit(fps);

    tgui::Gui gui{window};
    gui.setFont(tgui::Font("my_font.ttf"));
    gui.setTextSize(16);
    GameInterface interface{window, gui};

    Counter counter;
    Snake snake{false};
    Apple apple{snake};

    // for debug ?
    #ifdef START_INCREASE_SNAKE
        for(int r=1; r<=5; r++)
            ++snake;
    #endif
    
    sf::Clock delta;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.text.unicode == sf::Keyboard::Key::A)
                    snake.left();
                if (event.text.unicode == sf::Keyboard::Key::D)
                    snake.right();
                if (event.text.unicode == sf::Keyboard::Key::S)
                    snake.up();
                if (event.text.unicode == sf::Keyboard::Key::Z)
                    snake.down();
                if (event.text.unicode == sf::Keyboard::Key::Escape)
                {
                    interface.set_start_game(false);
                    interface.enable_gui();
                    // snake = Snake(false); проблемка
                }
            }
        }


        
        if (interface.get_start_game())
        {
            if(snake.is_alive()) 
            {
                if (apple.check_snake_in_apple())
                {
                    apple.update();
                    ++counter;
                    ++snake;
                    
                    /* it will increase speed*/
                    fps += 1;
                    window.setFramerateLimit(fps);
                }
                snake.update(); 
            } 
            else
            {
                interface.end_game();
            }
        }
        
        
        window.clear(sf::Color::Black);

        snake.draw(window);
        window.draw(counter.get_obj());
        window.draw(apple.get_obj());
        gui.draw();

        window.display();

        // snake.log_snake();
    }

    return 0;
}