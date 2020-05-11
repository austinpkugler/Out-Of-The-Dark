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
class uiClass:public Screen
{
public:
    uiClass(sf::RenderWindow* window, Settings* settings, float width, float height);
    virtual void load();              // overrides Screen::load()
    virtual void update();            // overrides Screen::update()
    virtual void handleInput();       // overrides Screen::handleInput()
    virtual void render();            // overrides Screen::render()

private:
    void titleScreenInput();
    void playScreenInput();
    void settingsScreenInput();

    void renderSettingsScreen();      // renders the settings page
    void updateSettings();            // updates the settings struct

    sf::Sprite m_backgroundSprite;
    sf::Texture m_backgroundTexture;
};