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
    if (strcmp(m_screenName, "home_screen") == 0) // if screen is home_screen
    {
        TitleScreenInput(); 
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


void Screen::TitleScreenInput()
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)    // Close window button clicked.
        {
            m_window->close();
        }
        if (event.type == sf::Event::LostFocus)
        {
            // need to pause game
        }
        if (event.type == sf::Event::GainedFocus)
        {
            // need to unpause game
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                std::cout << "Mouse is pressed" << event.mouseButton.x << " " << event.mouseButton.y << '\n';
            }
        }
    }
}
