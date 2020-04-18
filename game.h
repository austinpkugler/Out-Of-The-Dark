#pragma once

#include "SFML/Graphics.hpp"
#include "screen.h"
#include "settings.h"
#include <fstream>
class Game
{
public:
    Game();
    ~Game();                    // destructor for game
    bool isDone() const;        // bool public member function to tell if game has been quit
    void loadSettings();        // void public member function to load the settings into the settings struct
    void updateSettings();      // void public member function to update settings with m_settings info

    void handleInput();         // void public member function to handle all input from keyboard/mouse
    void update();              // void public member function to update game objects
    void render();              // void public member function to render all game objects

private:
    sf::RenderWindow* m_window; // window for game
    Screen m_screen;            // current screen private member variable
    sf::Vector2i m_resolution;  // vector with int values to hold monitor resolution
    Settings m_settings;        // struct of game settings ex: showFps, playMusic etc.
    bool m_isDone;              // private member variable to see if game is done

};