#pragma once

// I
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <windows.h>

// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// Included Local Dependencies
#include "settings.h"
#include "section.h"
#include "menu.h"
#include "mazeBuilder.h"

class Game
{
public:
    // Constructor and Destructor
    Game(sf::RenderWindow* window);
    ~Game();

    // Public Member 
    bool isDone() const;                // public member function to see if game is done
    void load();                        // loads all Game
    void clearScreen();                 // void public member function to clear window
    void handleInput();                 // void public member function to handle all input from keyboard/mouse
    void update();                      // void public member function to update game objects
    void render();                      // void public member function to render all game objects
    void loadSettingsStruct();          // void public member function to load the settings into the settings struct
    int getFps() const;                 // gets the current fps
    void setFps(unsigned int);               // sets the game fps
    void playSoundBuffer();

private:
    sf::RenderWindow* m_window;     // window for screen
    Section* m_section;
    std::string  m_sectionName;
    Settings* m_settings;            // settings such as display fps, etc.
    sf::Font m_font;                // generic font to be used
    sf::Music* m_music;
    sf::SoundBuffer m_soundBuffer;
    unsigned int m_fps = 0;
    unsigned int m_displayedFps = 0;
    unsigned int m_frameCount = 0;
    float m_width;
    float m_height;
};