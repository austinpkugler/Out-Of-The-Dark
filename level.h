#pragma once

#include "SFML/Graphics.hpp"

class Level
{
public:
    Level();                     // default constructor
    Level(char* levelName);      // constructor
    ~Level();                    // destructor

    const char* getName() const; // public member function to get level name
    void handleInput();          // void public member function to handle all input from keyboard/mouse
    void update();               // void public member function to update game objects
    void render();               // void public member function to render all game objects

private:
    sf::RenderWindow m_window;   // window for level
    const char* m_levelName;
    int background;
    int character;
    int enemies;
    int radar;

};