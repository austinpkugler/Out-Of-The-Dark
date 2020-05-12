#pragma once

// Included C++11 Libraries
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

class Menu: public Section
{
public:
    // Constructor and Destructor
    Menu(sf::RenderWindow* window, Settings* settings, sf::Music* music, float width, float height);
    ~Menu();

    virtual void load();              // overrides Section::load()
    virtual void update();            // overrides Section::update()
    virtual void handleInput();       // overrides Section::handleInput()
    virtual void render();            // overrides Section::render()

private:
    void titleScreenInput();
    void playScreenInput();
    void settingsScreenInput();

    void renderSettingsScreen();      // renders the settings page
    void renderPlayScreen();

    void updateSettingsStruct();     // updates the settings struct
    void loadSettingsStruct();       // loads setting struct from file

    void loadFileToSaveSlot(int saveSlot);

    sf::Sprite m_backgroundSprite;
    sf::Texture* m_backgroundTexture;
    sf::Music* m_music;
    sf::Font m_font;

    sf::Text m_saveSlot1Text;
    sf::Text m_saveSlot2Text;
    sf::Text m_saveSlot3Text;
};