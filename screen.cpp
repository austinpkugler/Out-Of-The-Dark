#include "screen.h"

// default constructor for Screen class
// no return
// no parameters
Screen::Screen()
{
}

// default constructor for Screen class
// no return
// no parameters
Screen::~Screen()
{
}

// constructor for Screen class
// no return
// no parameters
Screen::Screen(const char* screenName, sf::RenderWindow* window)
{
    m_screenName = screenName;
    m_window = window;
}


void Screen::handleInput()
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            m_window->close();
        }
    }
}

void Screen::update()
{
}

void Screen::render()
{
}

void Screen::loadSprites()
{
    // load sprites here
}
