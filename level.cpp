#include "level.h"

// default constructor for Level class
// no return
// no parameters
Level::Level()
{
}

// constructor for Level class
// no return
// no parameters
Level::Level(char* levelName)
{
    m_levelName = levelName;
    // m_window = sf::RenderWindow(sf::VideoMode(800, 600), "Out of the Dark");
}

// destructor for Level class
// no return
// no parameters
Level::~Level()
{
}

void Level::handleInput()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            m_window.close();
        }
    }
}

void Level::update()
{
    
}

void Level::render()
{
    
}