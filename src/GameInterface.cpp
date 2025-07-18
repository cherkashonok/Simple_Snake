#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

#include "GameInterface.hpp"
#include "my_lib.hpp"


GameInterface::GameInterface(sf::RenderWindow& window, tgui::Gui& gui) : gui(gui), window(window) 
{
    // play/continue
    auto button1 = tgui::Button::create();
    button1->setSize("30%", "15%");
    button1->setPosition("(parent.innersize - size) / 2", "25%");
    button1->setText("Play");
    // спорный момент
    button1->onClick([this](){
                                disable_gui();
                                start_game=true;
                                show_play_or_continue = false;
                            });
    gui.add(button1, "play_continue");
    
    // settings
    auto button2 = tgui::Button::create();
    button2->setSize("30%", "15%");
    button2->setPosition("(parent.innersize - size) / 2", "40%");
    button2->setText("settings");
    gui.add(button2, "settings");
    
    // Exit
    auto button3 = tgui::Button::create();
    button3->setSize("30%", "15%");
    button3->setPosition("(parent.innersize - size) / 2", "55%");
    button3->setText("Exit");
    // спорный момент
    button3->onClick([&window](){window.close();});
    gui.add(button3, "exit");
}

bool GameInterface::get_start_game()
{
    return this->start_game;
}

void GameInterface::set_start_game(bool val)
{
    this->start_game = val;
}

void GameInterface::enable_gui()
{
    tgui::Button::Ptr wid = gui.get("play_continue")->cast<tgui::Button>();
    wid->setText((show_play_or_continue) ? "play" : "continue");

    const auto& gui_widgets = gui.getWidgets();
    for(auto el: gui_widgets)
        el->setVisible(true);
}

void GameInterface::disable_gui()
{
    const auto& gui_widgets = gui.getWidgets();
    for(auto el: gui_widgets)
        el->setVisible(false);
}

// void GameInterface::settings()
// {
// }

void GameInterface::end_game()
{
    start_game = false;
    show_play_or_continue = true;
    enable_gui();
}