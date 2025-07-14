#include <iostream>
#include <cstdlib>

#include "SFML/Window/Event.hpp"
#include "SFML/Graphics.hpp"
// #include "imgui.h"
// #include "imgui-SFML.h"

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
    // ImGui::SFML::Init(window);

    Counter counter;
    Snake snake{false};
    Apple apple{snake};

    #ifdef START_INCREASE_SNAKE
        for(int r=1; r<=10; r++)
            ++snake;
    #endif
    
    sf::Clock delta;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // ImGui::SFML::ProcessEvent(window, event);

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
            }
        }
        // ImGui::SFML::Update(window, delta.restart());

        window.clear(sf::Color::Black);

        // try
        // {
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
            sf::Font font = load_font();
            sf::Text text;

            text.setFont(font);
            text.setString("GAME OVER");
            text.setCharacterSize(36);

            window.draw(text);
        }
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << e.what() << '\n';
        // }

        snake.draw(window);
        window.draw(counter.get_obj());
        window.draw(apple.get_obj());

        window.display();
        // ImGui::SFML::Render(window);

        // snake.log_snake();
    }
    // ImGui::SFML::Shutdown();

    return 0;
}