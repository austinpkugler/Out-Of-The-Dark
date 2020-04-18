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
    // updates nothing
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
    sf::Texture texture;

    if (!texture.loadFromFile("assets/home_screen_background.png"))
    {
        std::exit(1);
    }
    sf::Sprite* sprite = new sf::Sprite(texture);

    m_vecOfSprites.push_back(sprite);
}

void Screen::titleScreenInput()
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
                // std::cout << "Mouse is pressed" << event.mouseButton.x << " " << event.mouseButton.y << '\n';
            }
        }
    }
}

void Screen::titleScreenRender()
{
    for (int i = 0; i < m_vecOfSprites.size(); ++i) // loops through all sprites and displays
    {
        m_vecOfSprites[i]->setPosition(0.f, 0.f);
        m_window->draw(*m_vecOfSprites[i]);
    }
    m_window->display();
    std::cout << "RENDER IS HAPPENING\n";
}
