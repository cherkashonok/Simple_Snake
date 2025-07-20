#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

#include "GameInterface.hpp"
#include "my_lib.hpp"


GameInterface::GameInterface(sf::RenderWindow& window, tgui::Gui& gui, Counter& counter) 
: gui(gui), window(window), counter(counter)
{
    auto menu = tgui::Panel::create();
    menu->getRenderer()->setPadding(10);
    menu->setSize("40%", "50%");
    menu->setPosition("(parent.innersize - size) / 2", "25%");

    // play/continue
    auto button1 = tgui::Button::create();
    button1->setSize("100%", "32%");
    button1->setText("Play");
    button1->onClick([this](){
        this->counter.hide_end_count();
        hide_gui();
        start_game=true;
        show_play_or_continue = false;
    });
    menu->add(button1, "play_continue");
    
    // settings
    auto button2 = tgui::Button::create();
    button2->setSize(tgui::bindSize(button1));
    button2->setPosition({tgui::bindLeft(button1), tgui::bindBottom(button1)+5});
    button2->setText("settings");
    button2->onClick([this](){
        hide_gui();
        draw_settings();
    });
    menu->add(button2, "settings");
    
    // exit
    auto button3 = tgui::Button::create();
    button3->setSize(tgui::bindSize(button2));
    button3->setPosition({tgui::bindLeft(button2), tgui::bindBottom(button2)+5});
    button3->setText("Exit");
    button3->onClick([&window](){window.close();});
    menu->add(button3, "exit");


    auto menu_of_settings = tgui::Panel::create();
    menu_of_settings->setVisible(false);
    menu_of_settings->getRenderer()->setPadding(10);
    menu_of_settings->setSize("40%", "50%");
    menu_of_settings->setPosition("(parent.innersize - size) / 2", "25%");

    // back
    auto back_button = tgui::Button::create();
    back_button->setText("back");
    back_button->onClick([this](){
        hide_settings();
        draw_gui();
    });
    menu_of_settings->add(back_button, "back button");

    // with walls or not
    auto walls = tgui::CheckBox::create();
    walls->setPosition({tgui::bindLeft(back_button), tgui::bindBottom(back_button)+60});
    walls->setText("enable walls");
    walls->onChange([this](){s.with_walls=!s.with_walls;});
    menu_of_settings->add(walls, "with walls or not");

    // speed settings
    auto speed_sett = tgui::RadioButtonGroup::create();
    speed_sett->setPosition({tgui::bindLeft(walls), tgui::bindTop(walls)});

    auto low_speed = tgui::RadioButton::create();
    low_speed->setText("low speed");
    low_speed->setPosition({tgui::bindLeft(walls), tgui::bindTop(walls)});
    low_speed->onCheck([this](){s.speed=0.5f;});

    auto medium_speed = tgui::RadioButton::create();
    medium_speed->setText("medium speed");
    medium_speed->setPosition({tgui::bindLeft(low_speed), tgui::bindBottom(low_speed)+5});
    medium_speed->onCheck([this](){s.speed=1.0f;});
    medium_speed->setChecked(true);

    auto high_speed = tgui::RadioButton::create();
    high_speed->setText("high speed");
    high_speed->setPosition({tgui::bindLeft(medium_speed), tgui::bindBottom(medium_speed)+5});
    high_speed->onCheck([this](){s.speed=2.0f;});

    speed_sett->add(low_speed, "low speed");
    speed_sett->add(medium_speed, "medium speed");
    speed_sett->add(high_speed, "high speed");
    menu_of_settings->add(speed_sett, "speed settings");


    gui.add(menu, "menu");
    gui.add(menu_of_settings, "menu of settings");
}

void GameInterface::draw_gui()
{
    auto menu = gui.get("menu")->cast<tgui::Panel>();
    menu->setVisible(true);

    auto wid = menu->get("play_continue")->cast<tgui::Button>();
    wid->setText((show_play_or_continue) ? "play" : "continue");
}

void GameInterface::hide_gui()
{
    auto menu = gui.get("menu")->cast<tgui::Panel>();
    menu->setVisible(false);
}

void GameInterface::draw_settings()
{
    auto menu_of_settings = gui.get("menu of settings")->cast<tgui::Panel>();
    menu_of_settings->setVisible(true);
}

void GameInterface::hide_settings()
{
    auto menu_of_settings = gui.get("menu of settings")->cast<tgui::Panel>();
    menu_of_settings->setVisible(false);
}

// добавить надпись счёта(+потрачено)
void GameInterface::draw_end_game()
{
    start_game = false;
    show_play_or_continue = true;
    draw_gui();
    counter.draw_end_count();
}

settings& GameInterface::get_settings()
{
    return this->s;
}

bool GameInterface::get_start_game()
{
    return this->start_game;
}

void GameInterface::set_start_game(bool val)
{
    this->start_game = val;
}