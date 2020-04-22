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
    loadSettings();
    load();
    m_backgroundSprite.setScale(m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
                                m_window->getSize().y / m_backgroundSprite.getLocalBounds().height);
    getAllSaves();
}

void Game::load()
{
    if (!m_font.loadFromFile("assets/rm_typerighter.ttf"))
    {
        std::exit(1);
    }

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
    else if (m_screenName == "settings_screen")
    {
        std::cout << "Game: Loading settings screen\n";
        settingsScreenLoad();
    }
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
        settingsScreenInput();
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

void Game::setFps(unsigned int fps)
{
    m_fps = fps;
}

bool Game::isDone() const
{
    return !(m_window->isOpen());
}

void Game::loadSettings()
{
    std::fstream file("user_data/settings.csv", std::ios::in);
    char comma = ',';
    std::string parameterName;

    file >> parameterName >> m_settings.playMusic;
    file >> parameterName >> m_settings.playAudio;
    file >> parameterName >> m_settings.difficulty;
    file >> parameterName >> m_settings.frameRate;
    file >> parameterName >> m_settings.showFps;
    file.close();
}

void Game::updateSettings()
{
    std::fstream file("user_data/settings.csv", std::ios::out);
    const char comma = ',';
    file << "PLAY_MUSIC" << comma << ' ' << m_settings.playMusic << '\n';
    file << "PLAY_AUDIO" << comma << ' ' << m_settings.playAudio << '\n';
    file << "DIFFICULTY" << comma << ' ' << m_settings.difficulty << '\n';
    file << "FRAME_RATE" << comma << ' ' << m_settings.frameRate << '\n';
    file << "SHOW_FPS" << comma << ' ' << m_settings.showFps << '\n';

    if (!m_settings.playMusic)
    {
        m_music.stop();
        std::cout << "Game: Stopped all music playback\n";
    }
    file.close();
}

std::vector<std::string> Game::getAllSaves()
{
    std::vector<std::string> saveFiles;
    std::fstream file("user_data/one.save", std::ios::in);
    if (!file.fail())
    {
        saveFiles.push_back("one.save");
    }
    file.close();

    file.open("user_data/two.save", std::ios::in);
    if (!file.fail())
    {
        saveFiles.push_back("two.save");
    }
    file.close();

    file.open("user_data/three.save", std::ios::in);
    if (!file.fail())
    {
        saveFiles.push_back("three.save");
    }
    file.close();

    return saveFiles;
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

    std::cout << "m_settings.playMusic : " << m_settings.playMusic << '\n';
    if (m_settings.playMusic)
    {
        std::cout << "Title Screen: Playing music\n";
        if (!m_music.openFromFile("assets/2nd_Sonata_Malign_Chords.ogg"))
        {
            std::exit(1);
        }
        m_music.setVolume(20.f);
        m_music.setLoop(true);
        m_music.play();
    }
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

/*******************************************************************************
 * Functions for playScreen change this comment to be better
 * 
 * 
 ******************************************************************************/

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

void Game::playScreenLoad()
{
    if (!m_titleScreenBg.loadFromFile("assets/play_screen_background.png"))
    {
        std::exit(1);
    }
    m_backgroundSprite.setTexture(m_titleScreenBg);
}

void Game::playScreenUpdate()
{
    m_backgroundSprite.setTexture(m_titleScreenBg);
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
                        m_settings.playMusic = true;
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        m_settings.playAudio = true;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings.difficulty = 0; // 0 difficulty includes radar, 1 does not
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings.frameRate = 30;
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings.showFps = true;
                    }
                }
                else if (event.mouseButton.x >= width * 0.4 &&
                         event.mouseButton.x <= width * 0.48)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        m_settings.playMusic = false;
                        std::cout << m_settings.playMusic << '\n';
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        m_settings.playAudio = false;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings.difficulty = 1; // 0 is easy, 1 is hard
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings.frameRate = 60;
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings.showFps = false;
                    }
                }
                else if (event.mouseButton.x >= width * 0.50 &&
                         event.mouseButton.x <= width * 0.56)
                {
                    if (event.mouseButton.y >= height * 0.55 &&
                        event.mouseButton.y <= height * 0.6)
                    {
                        m_settings.frameRate = 120;
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
