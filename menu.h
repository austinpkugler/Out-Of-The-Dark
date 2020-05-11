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
#include "section.h"
class Menu:public Section
{
public:
    Menu(sf::RenderWindow* window, Settings* settings, sf::Music* music, float width, float height);
    ~Menu();                          // destructor
    virtual void load();              // overrides Screen::load()
    virtual void update();            // overrides Screen::update()
    virtual void handleInput();       // overrides Screen::handleInput()
    virtual void render();            // overrides Screen::render()

private:
    void titleScreenInput();
    void playScreenInput();
    void settingsScreenInput();

    void renderSettingsScreen();      // renders the settings page

    void updateSettingsStruct();     // updates the settings struct
    void loadSettingsStruct();       // loads setting struct from file

    sf::Sprite m_backgroundSprite;
    sf::Texture* m_backgroundTexture;
    sf::Music* m_music;
};