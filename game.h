#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <windows.h>

#include "settings.h"
#include "screen.h"
#include "uiClass.h"

class Game
{
public:
    Game(sf::RenderWindow* window);
    ~Game();                            // destructor

    bool isDone() const;                // public member function to see if game is done
    void load();                        // loads all sprites and stores them in a vector indexed by the order they should be displayed
    void clearScreen();                 // void public member function to clear window
    void handleInput();                 // void public member function to handle all input from keyboard/mouse
    void update();                      // void public member function to update game objects
    void render();                      // void public member function to render all game objects
    void loadSettings();                // void public member function to load the settings into the settings struct
    int getFps() const;                 // gets the current fps
    void setFps(unsigned int);               // sets the game fps
    void playSoundBuffer();

private:
    sf::RenderWindow* m_window;     // window for screen
    Screen* m_screen;
    Settings* m_settings;            // settings such as display fps, etc.
    sf::Font m_font;                // generic font to be used
    sf::Music m_music;
    sf::SoundBuffer m_soundBuffer;
    unsigned int m_fps = 0;
    unsigned int m_displayedFps = 0;
    unsigned int m_frameCount = 0;
    float m_width;
    float m_height;
};