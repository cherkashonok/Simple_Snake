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
    uint32_t fps = 5;

    tgui::Gui gui{window};
    gui.setFont(tgui::Font("my_font.ttf"));
    gui.setTextSize(16);
    Counter counter;
    GameInterface interface{window, gui, counter};
    settings& s = interface.get_settings();

    std::shared_ptr<Snake> snake{new Snake(s)};
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
                    snake->left();
                if (event.text.unicode == sf::Keyboard::Key::D)
                    snake->right();
                if (event.text.unicode == sf::Keyboard::Key::S)
                    snake->up();
                if (event.text.unicode == sf::Keyboard::Key::Z)
                    snake->down();
                if (event.text.unicode == sf::Keyboard::Key::Escape)
                {
                    interface.set_start_game(false);
                    interface.draw_gui();
                }
            }
        }


        
        if (interface.get_start_game())
        {
            if(snake->is_alive()) 
            {
                if (apple.check_snake_in_apple())
                {
                    apple.update();
                    ++counter;
                    ++(*snake);
                    fps += s.speed;
                }
                snake->update(); 
            } 
            else
            {
                interface.draw_end_game();
                snake.reset(new Snake(s));
                counter.reset_count();
                fps = 5;
            }
        }
        window.setFramerateLimit(fps);
        
        
        window.clear(sf::Color::Black);

        snake->draw(window);
        window.draw(counter.get_obj());
        window.draw(apple.get_obj());
        if (!counter.get_hide())
            window.draw(counter.get_end_count());
        gui.draw();

        window.display();

        // snake.log_snake();
    }

    return 0;
}