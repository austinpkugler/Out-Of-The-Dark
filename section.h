#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "settings.h"
#include <string>



class Section
{
public:
    virtual void load() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

    std::string getSectionName() const {return m_sectionName;}

protected:
    sf::RenderWindow* m_window;
    std::string m_screenName;       // string of the current screen name
    std::string m_sectionName;      // string of the current Section name 
    Settings* m_settings;           // ptr to Settings struct (show fps, play audio, etc)
    float m_width;                  // starting width of window
    float m_height;                 // starting height of window

};