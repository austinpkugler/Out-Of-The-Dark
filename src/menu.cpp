#include "menu.h"

/**
 * @brief Menu class constructor
 * @details Initializes the varials required for running the launch menu.
 * @throw SFML exceptions may be thrown during fatal errors, especially if
 * assets fail to load.
 * @param window - a pointer to an sf::RenderWindow instance. This is the base
 * frame of the game.
 * @param settings - a pointer to an instance of the Settings struct. It
 * contains all user preferences in relation to the game.
 * @param music - a pointer to an instance of sf::Music. It holds the music that
 * is played throughout the game.
 * @param width - a float containing the starting width of the game window.
 * @param height - a float containing the starting height of the game window.
 */
Menu::Menu(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Settings> settings,
           std::shared_ptr<sf::Music> music, float width, float height)
{
    m_window = window;
    m_settings = settings;
    m_music = music;
    m_width = width;
    m_height = height;
    m_screenName = "title_screen";
    m_sectionName = SectionName::Menu;
    m_backgroundTexture = std::make_unique<sf::Texture>();
    m_soundBuffer = std::make_unique<sf::SoundBuffer>();
    load();

}

/**
 * @brief Destructor for the Menu class.
 * @details Deletes the allocated memory for all game textures.
 */
Menu::~Menu()
{
}

/**
 * @brief Manages the loading of all Menu assets.
 * @details Loads assets required for displaying menu backgrounds, buttons, and
 * launching the game.
 * @throw SFML exceptions are thrown when assets fail to load. The program may
 * terminate when fatal errors occur.
 * @param None
 * @return None
 */
void Menu::load()
{
    if (m_screenName == "title_screen")
    {

        if (!m_backgroundTexture->loadFromFile("../assets/title_screen_background.png"))
        {
            std::exit(1);
        }

    }
    else if (m_screenName == "play_screen")
    {
        if (!m_backgroundTexture->loadFromFile("../assets/play_screen_background.png"))
        {
            std::exit(1);
        }
    }
    else if (m_screenName == "settings_screen")
    {
        if (!m_backgroundTexture->loadFromFile("../assets/settings_screen_background.png"))
        {
            std::exit(1);
        }
    }

    if (!m_font.loadFromFile("../assets/rm_typerighter.ttf"))
    {
        std::exit(1);
    }

    loadSound();

    m_backgroundSprite.setTexture(*m_backgroundTexture);
    m_backgroundSprite.setScale(m_width / m_backgroundSprite.getLocalBounds().width,
                                m_height / m_backgroundSprite.getLocalBounds().height);

    m_saveSlot1Text.setFont(m_font);
    m_saveSlot1Text.setCharacterSize(32);
    m_saveSlot1Text.setFillColor(sf::Color::White);
    m_saveSlot1Text.setPosition(0.15 * m_width, 0.5 * m_height);

    m_saveSlot2Text.setFont(m_font);
    m_saveSlot2Text.setCharacterSize(32);
    m_saveSlot2Text.setFillColor(sf::Color::White);
    m_saveSlot2Text.setPosition(0.45 * m_width, 0.5 * m_height);

    m_saveSlot3Text.setFont(m_font);
    m_saveSlot3Text.setCharacterSize(32);
    m_saveSlot3Text.setFillColor(sf::Color::White);
    m_saveSlot3Text.setPosition(0.76 * m_width, 0.5 * m_height);
}

/**
 * @brief Dummy function for updating the Menu.
 * @details No updating is needed for the Menus, but as a child of Section the
 * update function is called so must still exist.
 * @throw None
 * @param None
 * @return None
 */
void Menu::update()
{
}

/**
 * @brief Manages Menu input and calls the relevant input handler.
 * @details Input handlers are called based on the current game screen.
 * @throw None
 * @param None
 * @return None
 */
void Menu::handleInput()
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

/**
 * @brief Displays all Menu assets to the screen.
 * @details The relevant render functions are displayed based on the current
 * screen. All backgrounds, buttons, and other graphics are displayed.
 * @throw None
 * @param None
 * @return None
 */
void Menu::render()
{
    m_window->draw(m_backgroundSprite);
    if (m_screenName == "settings_screen")
    {
        renderSettingsScreen();
    }
    if (m_screenName == "play_screen")
    {
        renderPlayScreen();
    }
}

/**
 * @brief Displays an overlay on the Settings screen.
 * @details When the "Settings" button is pressed from the main menu this
 * function is used to display the overlay to indicate what settings
 * preferences are currently in use.
 * @throw None
 * @param None
 * @return None
 */
void Menu::renderSettingsScreen()
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

/**
 * @brief Displays an overlay on the Play Game screen.
 * @details Displays the text of the level that is currently loaded into each
 * of the three save slots.
 * @throw None
 * @param None
 * @return None
 */
void Menu::renderPlayScreen()
{

    std::string slot1String = m_settings->saveSlot1.substr(m_settings->saveSlot1.find_last_of("/\\") + 1);
    std::string slot2String = m_settings->saveSlot2.substr(m_settings->saveSlot2.find_last_of("/\\") + 1);
    std::string slot3String = m_settings->saveSlot3.substr(m_settings->saveSlot3.find_last_of("/\\") + 1);
    m_saveSlot1Text.setString(slot1String);
    m_saveSlot2Text.setString(slot2String);
    m_saveSlot3Text.setString(slot3String);
    m_window->draw(m_saveSlot1Text);
    m_window->draw(m_saveSlot2Text);
    m_window->draw(m_saveSlot3Text);
}

/**
 * @brief Updates the settings.csv file to the current settings loaded in m_settings.
 * @details Opens a fstream file to update settings information. Data being written to the
 * settings.csv file includes playMusic, playAudio, difficulty, frameRate, showFps, saveSlot1,
 * saveSlot2, and saveSlot3
 * @throw None
 * @param None
 * @return None
 */
void Menu::updateSettingsStruct()
{
    std::fstream file("../user_data/settings.csv", std::ios::out);
    file << "PLAY_MUSIC, " << m_settings->playMusic << '\n';
    file << "PLAY_AUDIO, " << m_settings->playAudio << '\n';
    file << "DIFFICULTY, " << m_settings->difficulty << '\n';
    file << "FRAME_RATE, " << m_settings->frameRate << '\n';
    file << "SHOW_FPS, "   << m_settings->showFps << '\n';
    file << "SAVESLOT_1, " << m_settings->saveSlot1 << '\n';
    file << "SAVESLOT_2, " << m_settings->saveSlot2 << '\n';
    file << "SAVESLOT_3, " << m_settings->saveSlot3 << '\n';
}

/**
 * @brief Handles input related to the title screen, which is the first screen
 * that appears upon launch.
 * @details Handles input for buttons such as "Play Game," "Settings," and all
 * other title screen buttons.
 * @throw None
 * @param None
 * @return None
 */
void Menu::titleScreenInput()
{
    float width = m_window->getSize().x;
    float height = m_window->getSize().y;
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)    // Close window button clicked.
        {
            m_window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (event.mouseButton.x >= width * 0.10 &&
                    event.mouseButton.x <= width * 0.28)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.3)
                    {
                        // std::cout << "Menu: 'Play Game' button pressed\n";
                        m_screenName = "play_screen";
                        playClicked();
                        load();
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.4)
                    {
                        // std::cout << "Menu: 'Settings' button pressed\n";
                        m_screenName = "settings_screen";
                        playClicked();
                        load();
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.5)
                    {
                        // std::cout << "Menu: 'Maze builder' button pressed\n";
                        playClicked();
                        m_sectionName = SectionName::MazeBuilder;
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.6)
                    {
                        // std::cout << "Menu: 'Quit' button pressed\n";
                        m_window->close();
                    }
                }
            }
        }
    }
}

/**
 * @brief Handles input related to the play screen.
 * @details Input for the play screen includes left-clicking to play a level and
 * right-clicking to load a new level.
 * @throw None
 * @param None
 * @return None
 */
void Menu::playScreenInput()
{
    float width = m_window->getSize().x;
    float height = m_window->getSize().y;
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (event.mouseButton.y >= height * 0.23 &&
                    event.mouseButton.y <= height * 0.69)
                {
                    playClicked();
                    if (event.mouseButton.x >= width * 0.09 &&
                        event.mouseButton.x <= width * 0.31)
                    {
                        // std::cout << "Menu: 'Save Slot 1' button pressed\n";
                        m_sectionName = SectionName::SaveSlot1;
                    }
                    else if (event.mouseButton.x >= width * 0.39 &&
                             event.mouseButton.x <= width * 0.61)
                    {
                        // std::cout << "Menu: 'Save Slot 2' button pressed\n";
                        m_sectionName = SectionName::SaveSlot2;
                    }
                    else if (event.mouseButton.x >= width * 0.69 &&
                             event.mouseButton.x <= width * 0.91)
                    {
                        // std::cout << "Menu: 'Save Slot 3' button pressed\n";
                        m_sectionName = SectionName::SaveSlot3;
                    }
                }
                if (event.mouseButton.y >= height * 0.75 &&
                    event.mouseButton.y <= height * 0.8)
                {
                    playClicked();
                    if (event.mouseButton.x >= width * 0.1 &&
                    event.mouseButton.x <= width * 0.165)
                    {
                        m_screenName = "title_screen";
                        load();
                    }
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                if (event.mouseButton.y >= height * 0.23 &&
                    event.mouseButton.y <= height * 0.69)
                {
                    playClicked();
                    if (event.mouseButton.x >= width * 0.09 &&
                        event.mouseButton.x <= width * 0.31)
                    {
                        // std::cout << "Menu: 'Save Slot 1' open-file button pressed\n";
                        loadFileToSaveSlot(1);
                    }
                    else if (event.mouseButton.x >= width * 0.39 &&
                             event.mouseButton.x <= width * 0.61)
                    {
                        // std::cout << "Menu: 'Save Slot 2' open-file button pressed\n";
                        loadFileToSaveSlot(2);
                    }
                    else if (event.mouseButton.x >= width * 0.69 &&
                             event.mouseButton.x <= width * 0.91)
                    {
                        // std::cout << "Menu: 'Save Slot 3' open-file button pressed\n";
                        loadFileToSaveSlot(3);
                    }
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                updateSettingsStruct();
                m_screenName = "title_screen";
                load();
            }
        }
    }
}

/**
 * @brief Handles input related to the settings screen.
 * @details Input for the settings screen includes button presses to change
 * setting preferences.
 * @throw None
 * @param None
 * @return None
 */
void Menu::settingsScreenInput()
{
    float width = m_window->getSize().x;
    float height = m_window->getSize().y;
    sf::Event event;
    while(m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (event.mouseButton.x >= width * 0.30 &&
                    event.mouseButton.x <= width * 0.37)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        m_settings->playMusic = true;
                        playClicked();

                        if (m_settings->playMusic && m_music->getStatus() == sf::Music::Status::Stopped)
                        {
                            m_music->play();
                        }
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        m_settings->playAudio = true;
                        playClicked();


                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings->difficulty = 0;
                        playClicked();

                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings->frameRate = 30;
                        m_window->setFramerateLimit(m_settings->frameRate);
                        playClicked();

                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings->showFps = true;
                        playClicked();
                    }
                }
                else if (event.mouseButton.x >= width * 0.40 &&
                         event.mouseButton.x <= width * 0.48)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        m_settings->playMusic = false;
                        playClicked();

                        if (!m_settings->playMusic && m_music->getStatus() == sf::Music::Status::Playing)
                        {
                            m_music->stop();
                        }
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        playClicked();
                        m_settings->playAudio = false;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        m_settings->difficulty = 1; // 0 is easy, 1 is hard
                        playClicked();

                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        m_settings->frameRate = 60;
                        m_window->setFramerateLimit(m_settings->frameRate);
                        playClicked();

                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        m_settings->showFps = false;
                        playClicked();

                    }
                }
                else if (event.mouseButton.x >= width * 0.50 &&
                         event.mouseButton.x <= width * 0.56)
                {
                    if (event.mouseButton.y >= height * 0.55 &&
                        event.mouseButton.y <= height * 0.6)
                    {
                        m_settings->frameRate = 120;
                        m_window->setFramerateLimit(m_settings->frameRate);
                        playClicked();

                    }
                }
                else if (event.mouseButton.x >= width * 0.10 &&
                         event.mouseButton.x <= width * 0.16)
                {
                    if (event.mouseButton.y >= height * 0.75 &&
                        event.mouseButton.y <= height * 0.80)
                    {
                        playClicked();
                        updateSettingsStruct();
                        m_screenName = "title_screen";
                        load();

                    }
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                updateSettingsStruct();
                m_screenName = "title_screen";
                load();
            }
        }
    }
}

/**
 * @brief Loads a .maze file to one of the three save slots.
 * @details Utilizes Python scripts for prompting the user with file explorer
 * so that a level can be selected.
 * @throw Both C++ and Python errors can be thrown during fatal errors.
 * @param saveSlot - Specifies which of the three save slots to link.
 * @return None
 */
void Menu::loadFileToSaveSlot(int saveSlot)
{
    std::string filePath;
    if (saveSlot == 1)
    {
        filePath = m_settings->saveSlot1;
    }
    else if (saveSlot == 2)
    {
        filePath = m_settings->saveSlot2;
    }
    else if (saveSlot == 3)
    {
        filePath = m_settings->saveSlot3;
    }

    filePath = "python ../src/getMazeName/openFile.pyw " + filePath;
    
    system(filePath.c_str());
    std::fstream file("../src/getMazeName/filename.txt", std::ios::in);
    getline(file, filePath);

    if (saveSlot == 1)
    {
        m_settings->saveSlot1 = filePath;
    }
    else if (saveSlot == 2)
    {
        m_settings->saveSlot2 = filePath;
    }
    else if (saveSlot == 3)
    {
        m_settings->saveSlot3 = filePath;
    }
    updateSettingsStruct();
}