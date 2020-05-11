#include "uiClass.h"

uiClass::uiClass(sf::RenderWindow* window, Settings* settings, float width, float height)
{
    m_window = window;
    m_settings = settings;
    m_width = width;
    m_height = height;
    m_screenName = "title_screen";
}

void uiClass::load()
{
    if (m_screenName == "title_screen")
    {
        if (!m_backgroundTexture.loadFromFile("assets/title_screen_background.png"))
        {
            std::exit(1);
        }

    }
    else if (m_screenName == "play_screen")
    {
        if (!m_backgroundTexture.loadFromFile("assets/play_screen_background.png"))
        {
            std::exit(1);
        }
    }
    else if (m_screenName == "settings_screen")
    {
        if (!m_backgroundTexture.loadFromFile("assets/settings_screen_background.png"))
        {
            std::exit(1);
        }
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(m_width / m_backgroundSprite.getLocalBounds().width,
                                m_height / m_backgroundSprite.getLocalBounds().height);
}

void uiClass::handleInput()
{
    if (m_screenName == "title_screen")
    {
        titleScreenInput();
    }
    else if (m_screenName == "play_screen")
    {
        playScreenInput();
    }
    else if (m_screenName == "settings_screen")
    {
        settingsScreenInput();
    }
}

void uiClass::update()
{
    m_backgroundSprite.setTexture(m_backgroundTexture);
}

void uiClass::render()
{
        m_backgroundSprite.setTexture(m_backgroundTexture);

    m_window->draw(m_backgroundSprite); // draws background
    if (m_screenName == "settings_screen")
    {
        renderSettingsScreen(); // draws boxes for settings
    }
}

void uiClass::renderSettingsScreen()
{
    sf::RectangleShape rectangle(sf::Vector2f(m_width * 0.09, m_height * 0.05));
    rectangle.setFillColor(sf::Color(0, 0, 0, 0));
    rectangle.setOutlineColor(sf::Color(255, 255, 255));
    rectangle.setOutlineThickness(2);
    if (m_settings->playMusic)
    {
        rectangle.setPosition(m_width * 0.3, m_height * 0.25);
        m_window->draw(rectangle);
    }
    else
    {
        rectangle.setPosition(m_width * 0.4, m_height * 0.25);
        m_window->draw(rectangle);
    }

    if (m_settings->playAudio)
    {
        rectangle.setPosition(m_width * 0.3, m_height * 0.35);
        m_window->draw(rectangle);
    }
    else
    {
        rectangle.setPosition(m_width * 0.4, m_height * 0.35);
        m_window->draw(rectangle);
    }

    if (m_settings->difficulty)
    {
        rectangle.setPosition(m_width * 0.4, m_height * 0.45);
        m_window->draw(rectangle);
    }
    else
    {
        rectangle.setPosition(m_width * 0.3, m_height * 0.45);
        m_window->draw(rectangle);
    }

    if (m_settings->frameRate == 30)
    {
        rectangle.setPosition(m_width * 0.3, m_height * 0.55);
        m_window->draw(rectangle);
    }
    else if (m_settings->frameRate == 60)
    {
        rectangle.setPosition(m_width * 0.4, m_height * 0.55);
        m_window->draw(rectangle);
    }
    else if (m_settings->frameRate == 120)
    {
        rectangle.setPosition(m_width * 0.5, m_height * 0.55);
        m_window->draw(rectangle);
    }

    if (m_settings->showFps)
    {
        rectangle.setPosition(m_width * 0.3, m_height * 0.65);
        m_window->draw(rectangle);
    }
    else
    {
        rectangle.setPosition(m_width * 0.4, m_height * 0.65);
        m_window->draw(rectangle);
    }
}

void uiClass::updateSettings()
{
    std::fstream file("user_data/settings.csv", std::ios::out);
    const char comma = ',';
    file << "PLAY_MUSIC" << comma << ' ' << m_settings->playMusic << '\n';
    file << "PLAY_AUDIO" << comma << ' ' << m_settings->playAudio << '\n';
    file << "DIFFICULTY" << comma << ' ' << m_settings->difficulty << '\n';
    file << "FRAME_RATE" << comma << ' ' << m_settings->frameRate << '\n';
    file << "SHOW_FPS" << comma << ' ' << m_settings->showFps << '\n';
    m_window->setFramerateLimit(m_settings->frameRate);

    file.close();
}

void uiClass::titleScreenInput()
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
                float width = m_window->getSize().x;
                float height = m_window->getSize().y;
                if (event.mouseButton.x >= width * 0.10 &&
                    event.mouseButton.x <= width * 0.25)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.3)
                    {
                        std::cout << "Game: 'Play Game' button pressed\n";
                        m_screenName = "play_screen";
                        load();
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.4)
                    {
                        std::cout << "Game: 'Settings' button pressed\n";
                        m_screenName = "settings_screen";
                        load();
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.5)
                    {
                        std::cout << "Game: 'Quit' button pressed\n";
                        m_window->close();
                    }
                }
            }
        }
    }
}

void uiClass::playScreenInput()
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
                float width = m_window->getSize().x;
                float height = m_window->getSize().y;
                if (event.mouseButton.y >= height * 0.23 &&
                    event.mouseButton.y <= height * 0.69)
                {
                    if (event.mouseButton.x >= width * 0.09 &&
                        event.mouseButton.x <= width * 0.31)
                    {
                        std::cout << "Save Slot 1 has been pressed\n";
                    }
                    else if (event.mouseButton.x >= width * 0.39 &&
                             event.mouseButton.x <= width * 0.61)
                    {
                        std::cout << "Save slot 2 has been pressed\n";
                    }
                    else if (event.mouseButton.x >= width * 0.69 &&
                             event.mouseButton.x <= width * 0.91)
                    {
                        std::cout << "Save slot 3 has been pressed\n";
                    }
                }
                if (event.mouseButton.y >= height * 0.75 &&
                    event.mouseButton.y <= height * 0.8)
                {
                    if (event.mouseButton.x >= width * 0.1 &&
                    event.mouseButton.x <= width * 0.165)
                    {
                        m_screenName = "title_screen";
                        load();
                    }
                }
            }
        }
    }
}

void uiClass::settingsScreenInput()
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
                float width = m_window->getSize().x;
                float height = m_window->getSize().y;
                if (event.mouseButton.x >= width * 0.30 &&
                    event.mouseButton.x <= width * 0.37)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        m_settings->playMusic = true;
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        m_settings->playAudio = true;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings->difficulty = 0; // 0 difficulty includes radar, 1 does not
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings->frameRate = 30;
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings->showFps = true;
                    }
                }
                else if (event.mouseButton.x >= width * 0.40 &&
                         event.mouseButton.x <= width * 0.48)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        m_settings->playMusic = false;
                        // std::cout << m_settings->playMusic << '\n';
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        m_settings->playAudio = false;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings->difficulty = 1; // 0 is easy, 1 is hard
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings->frameRate = 60;
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings->showFps = false;
                    }
                }
                else if (event.mouseButton.x >= width * 0.50 &&
                         event.mouseButton.x <= width * 0.56)
                {
                    if (event.mouseButton.y >= height * 0.55 &&
                        event.mouseButton.y <= height * 0.6)
                    {
                        m_settings->frameRate = 120;
                    }
                }
                else if (event.mouseButton.x >= width * 0.10 &&
                         event.mouseButton.x <= width * 0.16)
                {
                    if (event.mouseButton.y >= height * 0.75 &&
                        event.mouseButton.y <= height * 0.80)
                    {
                        updateSettings();
                        m_screenName = "title_screen";
                        load();
                    }
                }
            }
        }
    }
}