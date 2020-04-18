#pragma once

#include "SFML/Graphics.hpp"
#include "settings.h"
#include <vector>
#include <cstring>
#include <iostream> // used for debugging

class Screen
{
public:
    Screen();                     // default constructor
    Screen(const char* screenName, sf::RenderWindow* window); // constructor
    ~Screen();                    // destructor

    const char* getName() const; // public member function to get screen name
    void loadSprites();          // loads all sprites and stores them in a vector indexed by the order they should be displayed
    void handleInput();          // void public member function to handle all input from keyboard/mouse
    void update();               // void public member function to update game objects
    void render();               // void public member function to render all game objects

private:
    void TitleScreenInput();     // private member function to do title screen input if screen is title screen


    sf::RenderWindow* m_window;   // window for screen
    const char* m_screenName;     // name of screen
    std::vector<sf::Sprite> m_vecOfSprites; // vector of sprites indexed by order in which they should be displayed


};