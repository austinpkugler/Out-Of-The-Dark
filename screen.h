#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include "settings.h"


class Screen
{
public:
    virtual void load() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
protected:
    sf::RenderWindow* m_window;
    std::string m_screenName;       // string of the current screen name
    Settings* m_settings;           // ptr to Settings struct (show fps, play audio, etc)
    float m_width;                  // starting width of window
    float m_height;                 // starting height of window
    sf::Font m_font;                // generic font to be used

};