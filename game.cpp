#include "game.h"


// default constructor for Game class
// no return
// no parameters
Game::Game(){}

Game::~Game(){}

// constructor for Game class
// no return
// no parameters
Game::Game(sf::RenderWindow* window)
{
    m_screenName = "title_screen";
    m_window = window;
    load();
    m_backgroundSprite.setScale(m_window->getSize().x / m_backgroundSprite.getLocalBounds().width, m_window->getSize().y / m_backgroundSprite.getLocalBounds().height);

}


void Game::handleInput()
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
        playScreenInput();
    }
}

void Game::update()
{
    if (m_screenName == "title_screen")
    {
        titleScreenUpdate();
    }
    else if (m_screenName == "play_screen")
    {
        playScreenUpdate();
    }
    else if (m_screenName == "settings_screen")
    {
        settingsScreenUpdate();
    }
}

void Game::render()
{
    // if (m_screenName == "title_screen")
    // {
    //     titleScreenRender();
    // }
    // else if (m_screenName == "play_screen")
    // {
    //     playScreenRender();
    // }
    renderBackground();

    if (m_settings.showFps == true)
    {
        sf::Text text;
        text.setFont(m_font);
        char c[10];
        sprintf(c, "%i", m_fps);
        text.setString(c);
        m_window->draw(text);
    }
}

void Game::renderBackground()
{
    m_window->draw(m_backgroundSprite);
}

void Game::clearScreen()
{
    m_window->clear(sf::Color::Black);
}

int Game::getFps() const
{
    return m_fps;
}

void Game::setFps(int fps)
{
    m_fps = fps;
}

bool Game::isDone() const
{
    return !(m_window->isOpen());
}

void Game::loadSettings()
{
    std::fstream file("settings/settings.csv", std::ios::in);
    char comma;
    std::string parameterName;
    file >> parameterName >> m_settings.playMusic;
    file >> parameterName >> m_settings.playAudio;
    file >> parameterName >> m_settings.difficulty;
    file >> parameterName >> m_settings.username;
    file >> parameterName >> m_settings.frameRate;
    file >> parameterName >> m_settings.showFps;
    file.close();
}

void Game::updateSettings()
{
    std::fstream file("settings/settings.csv", std::ios::out);
    const char comma = ',';
    std::string parameterName;
    file << "PLAY_MUSIC" << comma << m_settings.playMusic;
    file << "PLAY_AUDIO" << comma << m_settings.playAudio;
    file << "DIFFICULTY" << comma << m_settings.difficulty;
    file << "USERNAME" << comma << m_settings.username;
    file << "FRAME_RATE" << comma << m_settings.frameRate;
    file << "SHOW_FPS" << comma << m_settings.showFps;
    file.close();
}

void Game::load()
{
    std::cout << "screen Name at 60" << m_screenName;
    if (m_screenName == "title_screen")
    {
        std::cout << "Game: Loading title screen\n";
        titleScreenLoad();
    }
    else if (m_screenName == "play_screen")
    {
        std::cout << "Game: Loading play screen\n";
        playScreenLoad();
    }
    else if (m_screenName == "settings_screen")
    {
        std::cout << "Game: Loading settings screen\n";
        settingsScreenLoad();
    }
}

/*******************************************************************************
 * Functions for titleScreen change this comment to be better
 * 
 * 
 ******************************************************************************/
void Game::titleScreenUpdate()
{
    m_backgroundSprite.setTexture(m_titleScreenBg);
}

void Game::titleScreenLoad()
{
    if (!m_titleScreenBg.loadFromFile("assets/title_screen_background.png"))
    {
        std::exit(1);
    }

    m_backgroundSprite.setTexture(m_titleScreenBg);
    std::cout << "Game: Title screen loaded\n";
}

void Game::titleScreenInput()
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
                float width = m_window->getSize().x;
                float height = m_window->getSize().y;
                if (event.mouseButton.x >= width * 0.10 &&
                    event.mouseButton.x <= width * 0.25 &&
                    event.mouseButton.y >= height * 0.25 &&
                    event.mouseButton.y <= height * 0.50)
                {
                    if (event.mouseButton.y <= height * 0.3)
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

/*******************************************************************************
 * Functions for playScreen change this comment to be better
 * 
 * 
 ******************************************************************************/
void Game::playScreenUpdate()
{
    m_backgroundSprite.setTexture(m_playScreenBg);
}

void Game::playScreenLoad()
{
    if (!m_playScreenBg.loadFromFile("assets/play_screen_background.png"))
    {
        std::exit(1);
    }

    m_backgroundSprite.setTexture(m_playScreenBg);
    std::cout << "Game: Play screen loaded\n";
}

void Game::playScreenInput()
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
                    event.mouseButton.x <= width * 0.25 &&
                    event.mouseButton.y >= height * 0.25 &&
                    event.mouseButton.y <= height * 0.50)
                {
                    if (event.mouseButton.y <= height * 0.3)
                    {
                        std::cout << "Game: 'Load Game' button pressed\n";
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.4)
                    {
                        std::cout << "Game: 'New Game' button pressed\n";
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.5)
                    {
                        std::cout << "Game: 'Back' button pressed\n";
                        m_screenName = "title_screen";
                        load();
                    }
                }
            }
        }
    }
}

/*******************************************************************************
 * Functions for settingsScreen change this comment to be better
 * 
 * 
 ******************************************************************************/
void Game::settingsScreenUpdate()
{
    m_backgroundSprite.setTexture(m_settingsScreenBg);
}

void Game::settingsScreenLoad()
{
    if (!m_settingsScreenBg.loadFromFile("assets/settings_screen_background.png"))
    {
        std::exit(1);
    }

    m_backgroundSprite.setTexture(m_settingsScreenBg);
    std::cout << "Game: Settings screen loaded\n";
}

void Game::settingsScreenInput()
{
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)    // Close window button clicked.
        {
            m_window->close();
        }
    }
}
