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


class Screen
{
public:
    Screen(sf::RenderWindow* window, Settings* settings, float width, float height);
    void load(); // loads everything
    void handleInput();
    void update();
    void render();
protected:
    std::string m_screenName;
    sf::RenderWindow* m_window;
    Settings* m_settings;
    float m_width;
    float m_height;

};