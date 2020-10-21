#pragma once

// Included C++ Libraries
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <memory>

// Included Graphics Library Dependencies
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Included Local Dependencies
#include "settings.h"
#include "section.h"
#include "menu.h"
#include "mazeBuilder.h"
#include "gameplay.h"

/**
 * Class Name: Game
 * Brief: Manages Game processes
 * Description:
 *  The Game class contains all general functions required at every stage of
 *  the game. There should only be a single instance at any given time. In this
 *  implementation, the Game object is created in main(). The Game class has no
 *  child classes and is not a child class itself. However, the constructor is
 *  passed globally required Game variables that can be viewed in the Section
 *  class.
 */
class Game
{
public:
    // Constructor and Destructor
    Game(std::shared_ptr<sf::RenderWindow> window);
    ~Game();
    Game(const Game&) = delete;            // copy constructor
    Game(Game&&) = delete;                 // move constructor
    Game& operator=(const Game&) = delete; // copy assignment
    Game& operator=(Game&&) = delete;      // move assignment

    // Public Member Functions for General Game Processes
    void load();                    // Manages the loading of all game assets.
    void update();                  // Updates the game based on the current state.
    void handleInput();             // Manages all game input.
    void render();                  // Displays all game assets to the screen.
    void clearScreen();             // Clears the game screen of all assets.
    bool isDone() const;            // Getter for the current status of the game.
    void loadSettingsStruct();      // Loads the settings from a .csv file.

private:
    // Private SFML Member Variables
    std::shared_ptr<sf::RenderWindow> m_window;     // SFML base frame for all graphics.
    sf::Font m_font;                // SFML instance of the game's generic font.
    std::shared_ptr<sf::Music> m_music;             // SFML instance of the current game music.
    sf::Clock m_clock;

    // Private Game Member Variables
    std::shared_ptr<Settings> m_settings;           // Pointer to the current settings configuration.
    std::unique_ptr<Section> m_section;             // Pointer to the current section object.
    SectionName  m_sectionName;     // The name of the current section (ex: title_screen).
    unsigned int m_fps = 0;         // The current FPS being experienced.
    unsigned int m_displayedFps = 0;// The current FPS being displayed.
    unsigned int m_frameCount = 0;  // The number of elapsed frames.
    float m_width;                  // The width of the SFML window.
    float m_height;                 // The height of the SFML window.
};