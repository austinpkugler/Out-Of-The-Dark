#include "screen.h"


// default constructor for Screen class
// no return
// no parameters
Screen::Screen(){}

Screen::~Screen(){}

// constructor for Screen class
// no return
// no parameters
Screen::Screen(const char* screenName, sf::RenderWindow* window)
{
    m_screenName = screenName;
    m_window = window;
    sf::Texture texture;
    loadSprites();
}


void Screen::handleInput()
{
    if (strcmp(m_screenName, "home_screen") == 0) // if screen is home_screen
    {
        titleScreenInput();
    }
}

void Screen::update()
{
}

void Screen::render()
{
    if (strcmp(m_screenName, "home_screen") == 0) // if screen is home_screen
    {
        titleScreenRender();
    }
}

void Screen::loadSprites()
{
    if (strcmp(m_screenName, "home_screen") == 0) // if screen is home_screen
    {
        titleScreenLoad();
    }
}


void Screen::titleScreenLoad()
{
    m_vecOfTextures.push_back(sf::Texture()); // FIGURE OUT HOW TO KEEP TEXTURE GLOBAL

    if (!m_vecOfTextures[0].loadFromFile("assets/home_screen_background.png"))
    {
        std::exit(1);
    }

    sf::Sprite sprite;
    sprite.setTexture(m_vecOfTextures[0]);
    m_vecOfSprites.push_back(sprite);
    update();

}

void Screen::titleScreenInput() const
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)    // Close window button clicked.
        {
            m_window->close();
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

void Screen::titleScreenRender() const
{
    for (int i = 0; i < m_vecOfSprites.size(); ++i) // loops through all sprites and displays
    {
        m_window->draw(m_vecOfSprites[i]);
    }
    m_window->display();
}
