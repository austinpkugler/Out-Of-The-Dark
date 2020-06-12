#pragma once

// Included C++11 Libraries
#include <string>

// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// Included Local Dependencies
#include "settings.h"

/**
 * Class Name: Section
 * Brief: The parent of all child classes used for running the game.
 * Description:
 *  Contains functions for running vital game processes that occur every frame
 *  of the game. The functions present in this class can be overwritten by child
 *  classes
 */
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
    sf::Sound m_sound;
    sf::SoundBuffer* m_soundBuffer = new sf::SoundBuffer;

    void loadSound()
    {
        if (!m_soundBuffer->loadFromFile("assets/clicked.wav"))
        {
            std::cout << "Game: Failed to load asset 'clicked.wav'\n";
            std::exit(1);
        }
        m_sound.setBuffer(*m_soundBuffer);
    }

    void playClicked()
    {
        if (m_settings->playAudio)
        {
            m_sound.play();
        }
    }
    std::string m_screenName;       // string of the current screen name
    std::string m_sectionName;      // string of the current Section name 
    Settings* m_settings;           // ptr to Settings struct (show fps, play audio, etc)
    float m_width;                  // starting width of window
    float m_height;                 // starting height of window

};