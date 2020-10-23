#pragma once


// Included C++11 Libraries
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdio>
#include <iostream>


// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


// Included Local Dependencies
#include "settings.h"
#include "section.h"


/**
 * Class Name: Menu
 * Brief: Manages Menu processes
 * Description:
 *  The Menu class contains all genral functions required to the menu that
 *  appears upon the launch of the game.
 */
class Menu: public Section
{
public:
    // Constructor and Destructor
    Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Settings> settings,
         std::shared_ptr<sf::Music> music, float width, float height);
    ~Menu();
    Menu(const Menu&) = delete;            // copy constructor
    Menu(Menu&&) = delete;                 // move constructor
    Menu& operator=(const Menu&) = delete; // copy assignment
    Menu& operator=(Menu&&) = delete;      // move assignment

    // Public Member Functions for General Menu Processes
    virtual void load();            // Manages the loading of all Menu assets.
    virtual void update();          // Dummy function for updating the Menu.
    virtual void handleInput();     // Manages Menu input and calls the relevant input handler.
    virtual void render();          // Displays all Menu assets to the screen.

private:
    // Private Member Functions for General Menu Processes
    void renderSettingsScreen();            // Displays an overlay on the Settings screen.
    void renderPlayScreen();                // Displays an overlay on the Play Game screen.
    void updateSettingsStruct();            // Updates the settings.csv file to the current settings loaded in m_settings.
    void titleScreenInput();                // Handles input related to the title screen, which is the first screen that appears upon launch.
    void playScreenInput();                 // Handles input related to the play screen.
    void settingsScreenInput();             // Handles input related to the settings screen.
    void loadFileToSaveSlot(int saveSlot);  // Loads a .maze file to one of the three save slots.

    // Private SFML Member Variables
    sf::Sprite m_backgroundSprite;
    std::unique_ptr<sf::Texture> m_backgroundTexture;
    std::shared_ptr<sf::Music> m_music;
    sf::Font m_font;
    sf::Text m_saveSlot1Text;
    sf::Text m_saveSlot2Text;
    sf::Text m_saveSlot3Text;
};

