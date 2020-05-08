#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream> // used for debugging
#include <windows.h>

#include "settings.h"

class Game
{
public:
    Game();                             // default constructor
    Game(sf::RenderWindow* window);
    ~Game();                            // destructor

    bool isDone() const;                // public member function to see if game is done
    const std::string getName() const;  // public member function to get screen name
    void load();                        // loads all sprites and stores them in a vector indexed by the order they should be displayed
    void clearScreen();                 // void public member function to clear window
    void handleInput();                 // void public member function to handle all input from keyboard/mouse
    void update();                      // void public member function to update game objects
    void render();                      // void public member function to render all game objects
    void renderBackground();
    void renderSettings();
    void loadSettings();                // void public member function to load the settings into the settings struct
    void updateSettings();              // void public member function to update settings with m_settings info
    int getFps() const;                 // gets the current fps
    void setFps(unsigned int);               // sets the game fps
    void playSoundBuffer();

private:
    sf::RenderWindow* m_window;     // window for screen
    sf::Sprite m_backgroundSprite;
    std::string m_screenName;       // name of screen
    Settings m_settings;            // settings such as display fps, etc.
    sf::Font m_font;                // generic font to be used
    sf::Music m_music;
    sf::SoundBuffer m_soundBuffer;
    unsigned int m_fps = 0;
    unsigned int m_displayedFps = 0;
    unsigned int m_frameCount = 0;
    float m_width;
    float m_height;
    

    // TITLE SCREEN RESOURCES
    void titleScreenUpdate();       // private member function to update thngs on title screen
    void titleScreenLoad();         // private member function to load the title screen assets
    void titleScreenInput();        // private member function to do title screen input if screen is title screen
    sf::Texture m_titleScreenBg;

    // PLAY SCREEN RESOURCES
    std::vector<std::string> getAllSaves();
    void playScreenUpdate();
    void playScreenLoad();
    void playScreenInput();
    sf::Texture m_playScreenBg;

    // SETTINGS SCREEN RESOURCES
    void settingsScreenUpdate();
    void settingsScreenLoad();
    void settingsScreenInput();
    sf::Texture m_settingsScreenBg;
};