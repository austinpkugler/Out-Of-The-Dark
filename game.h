#pragma once

#include "SFML/Graphics.hpp"
#include "level.h"
class Game
{
public:
    Game(sf::RenderWindow& window, char* levelName); // default constructor for game
    ~Game();                   // destructor for game
    bool isDone();             // bool public member function to tell if game has been quit
    void handleInput();        // void public member function to handle all input from keyboard/mouse
    void update();             // void public member function to update game objects
    void render();             // void public member function to render all game objects

private:
    sf::RenderWindow& m_window; // window for game
    Level m_level;             // current level private member variable
    bool m_isDone;             // private member variable to see if game is done

};