#pragma once

// Included C++ Libraries
#include <string>
#include <memory>
#include <iostream>

// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// Included Local Dependencies
#include "settings.h"

enum class SectionName
{
    Menu, MazeBuilder, SaveSlot1, SaveSlot2, SaveSlot3
};

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
    Section() {}
    SectionName getSectionName() const {return m_sectionName;}
    sf::Sound::Status soundStatus() const {return m_sound.getStatus();}


protected:
    std::shared_ptr<sf::RenderWindow> m_window;
    sf::Sound m_sound;
    std::unique_ptr<sf::SoundBuffer> m_soundBuffer;
    std::string m_screenName;       // string of the current screen name
    SectionName m_sectionName;      // string of the current Section name 
    std::shared_ptr<Settings> m_settings;           // ptr to Settings struct (show fps, play audio, etc)
    float m_width;                  // starting width of window
    float m_height;                 // starting height of window


    void loadSound()
    {
        m_soundBuffer = std::make_unique<sf::SoundBuffer>();
        if (!m_soundBuffer->loadFromFile("../assets/clicked.wav"))
        {
            std::cout << "Section: Failed to load asset 'clicked.wav'\n";
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
};

