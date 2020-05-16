#include "game.h"

/**
 * @brief Game class constructor
 * @details Initializes the variables required for running the game.
 * @throw SFML exceptions may be thrown during fatal errors, especially if
 * assets fail to load.
 * @param window - a pointer to an sf::RenderWindow instance. This is the base
 * frame of the game.
 */
Game::Game(sf::RenderWindow* window)
{
    m_window = window;
    m_width = m_window->getSize().x;
    m_height = m_window->getSize().y;
    m_settings = new Settings();
    m_music = new sf::Music();
    load();
    m_section = new Menu(m_window, m_settings, m_music, m_width, m_height);
    m_sectionName = "maze_builder";
    m_window->setFramerateLimit(m_settings->frameRate);
}

/**
 * @brief Destructor for the Game class.
 * @details Deletes the allocated memory for the m_settings and m_section
 * instances.
 * @throw None
 */
Game::~Game()
{
    delete m_settings;
    delete m_section;
    delete m_music;
}

/**
 * @brief Manages the loading of all Game assets.
 * @details Loads global assets and then calls specific load functions
 * based on the current game state.
 * @throw SFML exceptions are thrown when assets fail to load. The program may
 * terminate when fatal errors occur.
 * @param None
 * @return None
 */
void Game::load()
{
    loadSettingsStruct();
    if (!m_soundBuffer.loadFromFile("assets/clicked.wav"))
    {
        std::cout << "Game: Failed to load asset 'clicked.wav'\n";
        std::exit(1);
    }
    if (!m_font.loadFromFile("assets/rm_typerighter.ttf"))
    {
        std::cout << "Game: Failed to load asset 'rm_typerighter.ttf'\n";
        std::exit(1);
    }
    if (!m_music->openFromFile("assets/2nd_Sonata_Malign_Chords.ogg"))
    {
        std::cout << "Game: Failed to load asset '2nd_Sonata_Malign_Chords.ogg'\n";
        std::exit(1);
    }
    m_music->setVolume(20.f);
    m_music->setLoop(true);

    if (m_settings->playMusic && m_music->getStatus() == sf::Music::Status::Stopped)
    {
        m_music->play();
    }
}

/**
 * @brief Updates the game based on the current state.
 * @details The update function of the current section is called. If the
 * section name does not match the child's section name, then update the parent
 * section name. The previous section is deleted and replaced with the new
 * section.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Game::update()
{
    m_section->update();
    if (m_sectionName != m_section->getSectionName())
    {
        m_sectionName = m_section->getSectionName();
        delete m_section;
        if (m_sectionName == "menu")
        {
            m_section = new Menu(m_window, m_settings, m_music, m_width, m_height);
        }
        else if (m_sectionName == "maze_builder")
        {
            m_section = new MazeBuilder(m_window, m_settings, m_width, m_height);
        }
        else if (m_sectionName == "save_slot_1")
        {
            m_section = new Gameplay(m_window, m_settings, m_music, m_width, m_height, m_settings->saveSlot1, 1);
        }
        else if (m_sectionName == "save_slot_2")
        {
            m_section = new Gameplay(m_window, m_settings, m_music, m_width, m_height, m_settings->saveSlot2, 2);
        }
        else if (m_sectionName == "save_slot_3")
        {
            m_section = new Gameplay(m_window, m_settings, m_music, m_width, m_height, m_settings->saveSlot3, 3);
        }
    }
}

/**
 * @brief Manages all Game input.
 * @details When an input event occurs handleInput() calls the input handler
 * function of the child section class that is relevant to the state of the game
 * at the time input was received.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Game::handleInput()
{
    m_section->handleInput();
}

/**
 * @brief Displays all Game assets to the screen.
 * @details The render function of the current section is called to display all
 * game assets (backgrounds, sprites, etc.). FPS is then displayed if display
 * FPS is true.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Game::render()
{
    m_section->render();
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
        text.setPosition(15, -15);
        m_window->draw(text);
    }
    m_frameCount++;
}

/**
 * @brief Clears the game screen of all assets.
 * @details Calls the SFML clear function to replace the screen with solid
 * black.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Game::clearScreen()
{
    m_window->clear(sf::Color::Black);
}

/**
 * @brief Getter function for the current FPS being displayed.
 * @details The value of m_fps is not the maximum FPS, but rather the FPS
 * currently being displayed. For example, the max FPS may be 120, but the
 * value returned by getFps() is 113.
 * @throw None
 * @param None
 * @return m_fps - the FPS being displayed at the time of function call.
 */
int Game::getFps() const
{
    return m_fps;
}

/**
 * @brief Updates the current FPS with the newest value, calculated in main().
 * @details The current FPS is re-calculated each frame in main() and this
 * setter function is used to update the m_fps Game member variable with the
 * new value.
 * @throw None
 * @param None
 * @return None
 */
void Game::setFps(unsigned int fps)
{
    m_fps = fps;
}

/**
 * @brief Plays the contents of the current sound buffer member variable.
 * @details The current audio in sf::SoundBuffer member variable m_soundBuffer
 * is played during function call.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Game::playSoundBuffer()
{
    if (m_settings->playAudio)
    {
        sf::Sound sound;
        sound.setBuffer(m_soundBuffer);
        sound.play();
    }
}

/**
 * @brief Getter for the current status of the game.
 * @details A boolean is returned indicating whether the game is running.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return bool - true if the game is running, false if it is not
 */
bool Game::isDone() const
{
    return !(m_window->isOpen());
}

/**
 * @brief Loads the settings from a .csv file.
 * @details Setting preferences are loaded from an external .csv file into the
 * m_settings struct.
 * @throw None
 * @param None
 * @return None
 */
void Game::loadSettingsStruct()
{
    std::fstream file("user_data/settings.csv", std::ios::in);
    char space;
    std::string parameterName;

    file >> parameterName >> m_settings->playMusic;
    file >> parameterName >> m_settings->playAudio;
    file >> parameterName >> m_settings->difficulty;
    file >> parameterName >> m_settings->frameRate;
    file >> parameterName >> m_settings->showFps;
    file >> parameterName;
    file.get(space);
    getline(file, m_settings->saveSlot1);
    file >> parameterName;
    file.get(space);
    getline(file, m_settings->saveSlot2);
    file >> parameterName;
    file.get(space);
    getline(file, m_settings->saveSlot3);

    file.close();
}