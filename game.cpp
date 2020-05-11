#include "game.h"

Game::~Game(){}

// constructor for Game class
// no return
// no parameters
Game::Game(sf::RenderWindow* window)
{
    m_window = window;
    m_width = m_window->getSize().x;
    m_height = m_window->getSize().y;
    // loadSettings();
    m_screen = new uiClass(m_window, m_settings, m_width, m_height);
    load();

}

/**
 * @brief Manages the loading of all game assets.
 * @details Loads global assets and then calls specific load functions
 * based on the current game state.
 * @throw SFML exceptions are thrown when assets fail to load. The program may
 * terminate when fatal errors occur.
 * @param None
 * @return None
 */
void Game::load()
{
    if (!m_soundBuffer.loadFromFile("assets/clicked.wav"))
    {
        std::cout << "Game: Failed to load asset clicked.wav\n";
        std::exit(1);
    }
    if (!m_font.loadFromFile("assets/rm_typerighter.ttf"))
    {
        std::cout << "Game: Failed to load asset rm_typerighter.ttf\n";
        std::exit(1);
    }

    if (m_settings->playMusic && m_music.getStatus() == sf::Music::Status::Stopped)
    {
        std::cout << "Playing music\n";
        if (!m_music.openFromFile("assets/2nd_Sonata_Malign_Chords.ogg"))
        {
            std::cout << "Game: Faled to load asset 2nd_Sonata_Malign_Chords.ogg\n";
            std::exit(1);
        }
        m_music.setVolume(20.f);
        m_music.setLoop(true);
        m_music.play();
    }

    m_screen->load();
}

/**
 * @brief Manages all game input.
 * @details When an input event occurs handleInput() calls the input handler
 * function that is relevant to the state of the game at the time input was 
 * received.
 * @throw SFML exceptions are thrown when assets fail to load. The program may
 * terminate when fatal errors occur.
 * @param None
 * @return None
 */
void Game::handleInput()
{
    m_screen->handleInput();
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::update()
{
    m_screen->update();
    if (!m_settings->playMusic)
    {
        m_music.stop();
        // std::cout << "Game: Stopped all music playback\n";
    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::render()
{
    m_screen->render();


    if (m_settings->showFps && m_frameCount % (m_settings->frameRate / 4) == 0)
    {
        m_displayedFps = m_fps;
        if (m_displayedFps > m_settings->frameRate)
        {
            m_displayedFps = m_settings->frameRate;
        }
    }
    if (m_settings->showFps)
    {
        sf::Text text;
        
        text.setFont(m_font);
        char c[10];
        sprintf(c, "%i", m_displayedFps);
        text.setString(c);
        text.setPosition(15, 0);
        m_window->draw(text);
    }
    m_frameCount++;
}



/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::clearScreen()
{
    m_window->clear(sf::Color::Black);
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
int Game::getFps() const
{
    return m_fps;
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::setFps(unsigned int fps)
{
    m_fps = fps;
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::playSoundBuffer()
{
    if (m_settings->playAudio)
    {
        sf::Sound sound;
        sound.setBuffer(m_soundBuffer);
        sound.play();
        std::cout << "Audio: Playing sound effect from buffer\n";
    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
bool Game::isDone() const
{
    return !(m_window->isOpen());
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Game::loadSettings()
{
    std::fstream file("user_data/settings.csv", std::ios::in);
    char comma = ',';
    std::string parameterName;

    file >> parameterName >> m_settings->playMusic;
    file >> parameterName >> m_settings->playAudio;
    file >> parameterName >> m_settings->difficulty;
    file >> parameterName >> m_settings->frameRate;
    file >> parameterName >> m_settings->showFps;
    file.close();

    std::cout << "loadSettings is done!\n";
}