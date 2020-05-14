#include "gameplay.h"

/**
 * @brief Gameplay class constructor
 * @details Initializes the variables required for running ingame attributes,
 * including the player and ingame graphics.
 * @throw SFML exceptions may be thrown during fatal errors, especially if
 * assets fail to load.
 * @param window - a pointer to an instance of sf::RenderWindow. This is the
 * base frame of the game.
 * @param settings - a pointer to an instance of the Settings struct. It
 * contains all user preferences in relation to the game.
 * @param music - a pointer to an instance of sf::Music. It holds the music that
 * is played throughout the game.
 * @param width - a float containing the starting width of the game window.
 * @param height - a float containing the starting height of the game window.
 * @param fileName - a string filepath to the maze level that is currently being
 * played.
 * @param saveSlot - an integer that contains the current save slot being
 * played between 1-3.
 */
Gameplay::Gameplay(sf::RenderWindow* window, Settings* settings, sf::Music* music, float width, float height, std::string fileName, int saveSlot)
{
    m_window = window;
    m_settings = settings;
    m_music = music;
    m_width = width;
    m_height = height;
    objectsToDisplay = 25; // draw 25 squares on a screen
    TEXTURE_SIZE = 250.0f; // size of square in pixels
    gridOffset.x = 0;
    gridOffset.y = 0;
    player.velocity.x = 0;
    player.velocity.y = 0;
    m_screenName = "game_screen";

    deathScreenTexture = new sf::Texture();
    hardModeTexture = new sf::Texture();
    pausedScreenTexture = new sf::Texture();
    settingsScreenTexture = new sf::Texture();
    winScreenTexture = new sf::Texture();

    if (saveSlot == 1)
    {
        m_sectionName = "save_slot_1";
    }
    else if (saveSlot == 2)
    {
        m_sectionName = "save_slot_2";
    }
    else if (saveSlot == 3)
    {
        m_sectionName = "save_slot_3";
    }


    this->fileName = fileName;
    squareSize = static_cast<float>(std::max(m_width, m_height)) / objectsToDisplay;

    healthBarBg.setSize(sf::Vector2f(0.15 * m_width, 0.01 * height));
    healthBarBg.setFillColor(sf::Color(255, 26, 26));
    healthBarBg.setPosition(squareSize, 0.93 * m_height);

    healthBar.setSize(sf::Vector2f(0.15 * m_width, 0.01 * height));
    healthBar.setFillColor(sf::Color(0, 128, 0));
    healthBar.setPosition(squareSize, 0.93 * m_height);

    load();

    upperLeftSquare.x = startingBlock.x - (objectsToDisplay - 1) / 2.0f;
    upperLeftSquare.y = startingBlock.y - ((objectsToDisplay / m_width) * m_height-1) / 2.0f;

    sf::Vector2f playerCoords = indexToCoord(startingBlock.x, startingBlock.y);
    player.x = playerCoords.x + 0.5 * squareSize - gridOffset.x;
    player.y = playerCoords.y + 0.5 * squareSize - gridOffset.y;
    player.sprite.setPosition(player.x, player.y);

    m_highlightedGridRect.setSize(sf::Vector2f(squareSize, squareSize));
    m_highlightedGridRect.setFillColor(sf::Color(230, 230, 220, 50));

    m_squareToMoveTo.setSize(sf::Vector2f(squareSize, squareSize));
    m_squareToMoveTo.setFillColor(sf::Color(20, 20, 20, 200));
    m_squareToMoveTo.setPosition(-1, -1);
}

/**
 * @brief Destructor for the Gameplay class.
 * @details Deletes the allocated memory for all game textures.
 * @throw None
 */
Gameplay::~Gameplay()
{
    delete deathScreenTexture;
    delete hardModeTexture;
    delete pausedScreenTexture;
    delete settingsScreenTexture;
    delete winScreenTexture;
    delete player.texturePtr;
    for (int i = 0; i < 8; i++)
    {
        delete vectorOfTextures[i];
    }
}

/**
 * @brief Manages the loading of all Gameplay assets.
 * @details Loads assets required for gameplay, including player sprite and
 * grid textures.
 * @throw SFML exceptions are thrown when assets fail to load. The program may
 * terminate when fatal errors occur. This function is called from a master 
 * load() function in the Game class.
 * @param None
 * @return None
 */
void Gameplay::load()
{
    for (int i = 0; i < 8; i++)
    {
        vectorOfTextures.push_back(new sf::Texture());
    }

    if (!vectorOfTextures[0]->loadFromFile("assets/blue_floor_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'blue_floor_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[1]->loadFromFile("assets/blue_floor_trapped_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'blue_floor_trapped_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[2]->loadFromFile("assets/blue_floor_fire_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'blue_floor_fire_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[3]->loadFromFile("assets/death_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'death_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[4]->loadFromFile("assets/wall_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'wall_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[5]->loadFromFile("assets/alien_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'alien_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[6]->loadFromFile("assets/start_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'start_texture.png'\n";
        std::exit(1);
    }
    if (!vectorOfTextures[7]->loadFromFile("assets/end_texture.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'end_texture.png'\n";
        std::exit(1);
    }
    if (!player.texturePtr->loadFromFile("assets/player.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'player.png'\n";
        std::exit(1);
    }
    if (!deathScreenTexture->loadFromFile("assets/death_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'death_background.png'\n";
        std::exit(1);
    }
    if (!hardModeTexture->loadFromFile("assets/hard_mode_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'hard_mode_background.png'\n";
        std::exit(1);
    }
    if (!pausedScreenTexture->loadFromFile("assets/paused_screen_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'paused_screen_background.png'\n";
        std::exit(1);
    }
    if (!settingsScreenTexture->loadFromFile("assets/settings_screen_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'settings_screen_background.png'\n";
        std::exit(1);
    }
    if (!winScreenTexture->loadFromFile("assets/win_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'win_background.png'\n";
        std::exit(1);
    }

    player.sprite.setTexture(*player.texturePtr);
    player.sprite.setScale((squareSize / 240.0f) * 0.7, (squareSize / 240.0f) * 0.7);
    player.sprite.setOrigin(player.sprite.getLocalBounds().width / 2, player.sprite.getLocalBounds().height / 2);

    deathScreenSprite.setTexture(*deathScreenTexture);
    deathScreenSprite.setScale(m_width / deathScreenSprite.getLocalBounds().width, m_height / deathScreenSprite.getLocalBounds().height);

    hardModeSprite.setTexture(*hardModeTexture);
    hardModeSprite.setScale(m_width / hardModeSprite.getLocalBounds().width, m_height / hardModeSprite.getLocalBounds().height);

    pausedScreenSprite.setTexture(*pausedScreenTexture);
    pausedScreenSprite.setScale(m_width / pausedScreenSprite.getLocalBounds().width, m_height / pausedScreenSprite.getLocalBounds().height);

    settingsScreenSprite.setTexture(*settingsScreenTexture);
    settingsScreenSprite.setScale(m_width / settingsScreenSprite.getLocalBounds().width, m_height / settingsScreenSprite.getLocalBounds().height);

    winScreenSprite.setTexture(*winScreenTexture);
    winScreenSprite.setScale(m_width / winScreenSprite.getLocalBounds().width, m_height / winScreenSprite.getLocalBounds().height);

    populateGrid();
}

/**
 * @brief Updates all gameplay variables based on events that occur.
 * @details Handles checking for death, applying of damage, calculating new
 * player posistions, and other graphical updates. This function is called from
 * a master update() function in the Game class.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Gameplay::update()
{
    if (m_screenName == "game_screen")
    {
        calculatePlayerVelocity();
        calculateCollision();

        if (playerWon())
        {
            player.status = "won";
        }


        m_squareToMoveTo.move(player.velocity.x, player.velocity.y);

        GameObject blockMouseOn = blockMouseIsOn();
        if (blockMouseOn.arrIndexX != -1)
        {
            m_highlightedGridRect.setPosition((blockMouseOn.arrIndexX - upperLeftSquare.x)*squareSize + gridOffset.x,
                                            (blockMouseOn.arrIndexY - upperLeftSquare.y)*squareSize + gridOffset.y);
                                            
        }
        if (gridOffset.x >= squareSize)
        {
            gridOffset.x -= squareSize;
            --upperLeftSquare.x;
        }
        if (gridOffset.x <= -1*squareSize)
        {
            gridOffset.x += squareSize;
            ++upperLeftSquare.x;
        }
        if (gridOffset.y >= squareSize)
        {
            gridOffset.y -= squareSize;
            --upperLeftSquare.y;
        }
        if (gridOffset.y <= -1*squareSize)
        {
            gridOffset.y += squareSize;
            ++upperLeftSquare.y;
        }
        gridOffset.x += player.velocity.x;
        gridOffset.y += player.velocity.y;
    }
}

/**
 * @brief Manages Gameplay input during game playthrough.
 * @details All input events are checked for and the proper function calls are
 * made. This includes input related to player movement and ingame virtual
 * button presses. This function is called from a master handleInput() function
 * in the Game class.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Gameplay::handleInput()
{
    if (m_screenName == "game_screen")
    {
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
                    if (player.status == "alive")
                    {
                        GameObject blockMouseOn = blockMouseIsOn();
                        if (blockMouseOn.arrIndexX != -1)
                        {
                            m_squareToMoveTo.setPosition((blockMouseOn.arrIndexX - upperLeftSquare.x) * squareSize + gridOffset.x,
                                                        (blockMouseOn.arrIndexY - upperLeftSquare.y) * squareSize + gridOffset.y);
                        }
                    }
                    else if (player.status == "dead" || player.status == "won")
                    {
                        resetLevel();
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_screenName = "paused_screen";
                }
            }
        }
    }
    else if (m_screenName == "paused_screen")
    {
        pausedScreenInput();
    }
    else if (m_screenName == "settings_screen")
    {
        settingsScreenInput();
    }
}

/**
 * @brief Displays all Gameplay assets to the screen.
 * @details The player sprite, grid textures, and overlays are displayed. This
 * function is called from a master render() function in the Game class.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
void Gameplay::render()
{
    if (m_screenName == "game_screen")
    {
        renderGrid();
        if (player.status == "alive")
        {
            if (m_squareToMoveTo.getPosition().x != -1)
            {
                m_window->draw(m_squareToMoveTo);
            }
            if (blockMouseIsOn().arrIndexX != -1)
            {
                m_window->draw(m_highlightedGridRect);
            }
            m_window->draw(player.sprite);
            if (m_settings->difficulty == 0)
            {
                displayHealth();
            }
            else
            {
                m_window->draw(hardModeSprite);
            }
        }
        else if (player.status == "dead")
        {
            m_window->draw(deathScreenSprite);
        }
        else if (player.status == "won")
        {
            m_window->draw(winScreenSprite);
        }
    }
    else if (m_screenName == "paused_screen")
    {
        m_window->draw(pausedScreenSprite);
    }
    else if (m_screenName == "settings_screen")
    {
        m_window->draw(settingsScreenSprite);
        renderSettingsScreen();
    }
}

/**
 * @brief Graphically displays the player's health bar.
 * @details A red background health bar is always present behind a green health
 * bar. The red background health bar remains at 100% capactiy at all times,
 * while the forward green healthbar decreases in length when damage is taken.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param
 * @return
 */
void Gameplay::displayHealth()
{
    healthBar.setSize(sf::Vector2f((player.healthPercent * 0.15) / 100 * m_width, 0.01 * m_height));
    m_window->draw(healthBarBg);
    m_window->draw(healthBar);
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::calculateCollision()
{
    std::vector<GameObject> objectsStandingOn = blocksPlayerIsOn();
    // If the texture is a trap
    for (int i = 0; i < objectsStandingOn.size(); ++i)
    {
        if (objectsStandingOn[i].textureIndex == 1)
        {
            player.healthPercent -= 40;
            // The trap has been set off, so reset the square to be a path with no trap.
            m_maze[objectsStandingOn[i].arrIndexX][objectsStandingOn[i].arrIndexY].textureIndex = 0;
            m_maze[objectsStandingOn[i].arrIndexX][objectsStandingOn[i].arrIndexY].sprite.setTexture(*vectorOfTextures[0]);
        }
        // Else if the texture is fire
        else if (objectsStandingOn[i].textureIndex == 2) // player standing on fire
        {
            player.burning = true;
        }
        // Else if texture is wall
        else if (objectsStandingOn[i].textureIndex == 4)
        {
            int player_x = ((player.x - gridOffset.x) / squareSize) + upperLeftSquare.x;
            int player_y = ((player.y - gridOffset.y) / squareSize) + upperLeftSquare.y;
            if (objectsStandingOn[i].arrIndexX == player_x-1 && player.velocity.x > 0)
            {
                player.velocity.x = 0;
                player.velocity.y = 0;
            }
            else if (objectsStandingOn[i].arrIndexX == player_x + 1 && player.velocity.x < 0)
            {
                player.velocity.x = 0;
                player.velocity.y = 0;
            }
            else if (objectsStandingOn[i].arrIndexY == player_y + 1 && player.velocity.y < 0)
            {
                player.velocity.x = 0;
                player.velocity.y = 0;
            }
            else if (objectsStandingOn[i].arrIndexY == player_y - 1 && player.velocity.y > 0)
            {
                player.velocity.x = 0;
                player.velocity.y = 0;
            }
        }
        // Else if the texture is diseased path
        else if (objectsStandingOn[i].textureIndex == 5) // player standing on diseased path
        {
            player.poisoned = true;
        }
    }

    if (player.burning && player.burnLength % m_settings->frameRate == 0)
    {
        player.healthPercent -= 5;
        if (m_settings->frameRate * 5 == player.burnLength)
        {
            player.burning = false;
            player.burnLength = 0;
        }
    }
    if (player.burning)
    {
        player.burnLength++;
    }

    if (player.poisoned && player.poisonedLength % (m_settings->frameRate / 5) == 0)
    {
        player.healthPercent -= 1;
        if (m_settings->frameRate == player.poisonedLength)
        {
            player.poisoned = false;
            player.poisonedLength = 0;
        }
    }
    if (player.poisoned)
    {
        player.poisonedLength++;
    }

    if (player.healthPercent <= 0)
    {
        player.healthPercent = 0;
        player.status = "dead";
    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::populateGrid()
{
    std::fstream file(fileName, std::ios::in);
    file >> GRID_SIZE;
    for (int x = 0; x < GRID_SIZE; ++x)
    {
        m_maze.push_back(std::vector<GameObject>());
        for (int y = 0; y < GRID_SIZE; ++y)
        {
            m_maze[x].push_back(GameObject());
            m_maze[x][y].arrIndexX = x;
            m_maze[x][y].arrIndexY = y;
            m_maze[x][y].sprite.setScale(squareSize / TEXTURE_SIZE, squareSize / TEXTURE_SIZE);
            file >> m_maze[x][y].textureIndex;

            m_maze[x][y].sprite.setTexture(*vectorOfTextures[m_maze[x][y].textureIndex]);

            switch (m_maze[x][y].textureIndex)
            {
                case 1:     // If the texture is a trap
                    m_maze[x][y].walkable = 1;
                    break;
                case 2:     // If the texture is fire
                    m_maze[x][y].walkable = 1;
                    break;
                case 3:     // If the texture is a bloodied path
                    m_maze[x][y].walkable = 1;
                    break;
                case 4:     // Ff the texture ise a stone wall
                    m_maze[x][y].walkable = 0;
                    break;
                case 5:     // If the texture is diseased path
                    m_maze[x][y].walkable = 1;
                    break;
                case 6:     // If the texture is maze start
                    m_maze[x][y].walkable = 1;
                    startingBlock.x = m_maze[x][y].arrIndexX;
                    startingBlock.y = m_maze[x][y].arrIndexY;
                    break;
                case 7:     // If the texture is maze end
                    m_maze[x][y].walkable = 1;
                    break;
            };
        }
    }
    file.close();
}

/**
 * @brief 
 * @details A pixel offset is used to move the entire grid of textures based on
 * user inputs. Positioning is relative to the top left corner of the grid. If 
 * an area outside of the exisitng level occurs, then 
 * @throw
 * @param
 * @return
 */
void Gameplay::renderGrid()
{

    for (int arr_x = upperLeftSquare.x - 2; arr_x < (upperLeftSquare.x + objectsToDisplay) + 4; ++arr_x)
    {
        for (int arr_y = upperLeftSquare.y - 2; arr_y < (upperLeftSquare.y + objectsToDisplay) + 4; ++arr_y)
        {
            float x_coords = ((m_maze[arr_x][arr_y].arrIndexX - upperLeftSquare.x + 2) * squareSize) - 2*squareSize;
            float y_coords = ((m_maze[arr_x][arr_y].arrIndexY - upperLeftSquare.y + 2) * squareSize) - 2*squareSize;
            x_coords += gridOffset.x;
            y_coords += gridOffset.y;
            m_maze[arr_x][arr_y].sprite.setPosition(x_coords, y_coords);
            m_window->draw(m_maze[arr_x][arr_y].sprite);
        }
    }
}

/**
 * @brief Returns a boolean indicating whether the player has won.
 * @details Checks the texture the player is standing on to determine if it is
 * an end texture.
 * @throw None
 * @param None
 * @return bool - true if the player has won, false if not
 */
bool Gameplay::playerWon()
{
    std::vector<GameObject> objectsStandingOn = blocksPlayerIsOn();
    for (int i = 0; i < objectsStandingOn.size(); ++i)
    {
        if (objectsStandingOn[i].textureIndex == 7)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Resets the level to its original form.
 * @details Player position, all textures, and player variables are all reset
 * to their initial values when the level was first ran.
 * @throw None
 * @param None
 * @return None
 */
void Gameplay::resetLevel()
{
    gridOffset.x = 0;
    gridOffset.y = 0;
    player.velocity.x = 0;
    player.velocity.y = 0;
    player.burning = false;
    player.burnLength = 0;
    player.poisoned = false;
    player.poisonedLength = 0;
    upperLeftSquare.x = startingBlock.x - (objectsToDisplay - 1) / 2.0f;
    upperLeftSquare.y = startingBlock.y - ((objectsToDisplay / m_width) * m_height-1) / 2.0f;
    m_squareToMoveTo.setPosition(-1, -1);

    player.healthPercent = 100;
    player.status = "alive";
    populateGrid();
}

/**
 * @brief Calculates and returns the grid data of the mouse position.
 * @details Using the size of the game window and the coordinates of the mouse,
 * the grid x and y indices of the hovered over square are used to return the
 * GameObject of the grid square.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return m_maze[x][y] - an instance of the GameObject struct.
 */
const GameObject Gameplay::blockMouseIsOn() const
{
    float mouseX = sf::Mouse::getPosition(*m_window).x;
    float mouseY = sf::Mouse::getPosition(*m_window).y;
    mouseX /= m_window->getSize().x;
    mouseY /= m_window->getSize().y;
    mouseX *= m_width;
    mouseY *= m_height;
    int x = ((mouseX - gridOffset.x)/ squareSize) + upperLeftSquare.x;
    int y = ((mouseY - gridOffset.y) / squareSize) + upperLeftSquare.y;
    if (x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)
    {
        return GameObject();
    }
    return m_maze[x][y];
}

/**
 * @brief Converts indices of the grid array to an sf::Vector2f.
 * @details Passed x and y indices are used to calculate their equivalent
 * pixel positions on the game window.
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param x - the x index of the maze grid to be converted
 * @param y - the y index of the maze grid to be converted
 * @return sf::Vector2f - the pixel conversion of the passed indices.
 */
sf::Vector2f Gameplay::indexToCoord(unsigned int x, unsigned int y) const
{
    return sf::Vector2f((x - upperLeftSquare.x) * squareSize + gridOffset.x, (y - upperLeftSquare.y) * squareSize + gridOffset.y);
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
std::vector<GameObject> Gameplay::blocksPlayerIsOn() const
{
    std::vector<GameObject> blocks;
    unsigned int x = ((player.x - gridOffset.x) / squareSize) + upperLeftSquare.x; // dont calculate offset
    unsigned int y = ((player.y - gridOffset.y) / squareSize) + upperLeftSquare.y;

    if (!(x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    {
        blocks.push_back(m_maze[x][y]);
    }

    if (!(x-1 >= GRID_SIZE || x-1 < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    { 
        if (player.x - 0.5*player.sprite.getGlobalBounds().width < indexToCoord(x-1, y).x + squareSize)
        {
            blocks.push_back(m_maze[x-1][y]);
        }
    }
    if (!(x+1 >= GRID_SIZE || x+1 < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    {
        if (player.x + 0.5*player.sprite.getGlobalBounds().width > indexToCoord(x+1, y).x)
        {
            blocks.push_back(m_maze[x+1][y]);
        }
    }
    if (!(x >= GRID_SIZE || x < 0 || y-1 >= GRID_SIZE || y-1 < 0)) // if not out of bounds
    {
        if (player.y - 0.5*player.sprite.getGlobalBounds().height < indexToCoord(x, y).y)
        {
            blocks.push_back(m_maze[x][y-1]);
        }
    }
    if (!(x >= GRID_SIZE || x < 0 || y+1 >= GRID_SIZE || y+1 < 0)) // if not out of bounds
    {
        if (player.y + 0.5 * player.sprite.getGlobalBounds().height > indexToCoord(x, y+1).y)
        {
            blocks.push_back(m_maze[x][y+1]);
        }
    }
    return blocks;
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::pausedScreenInput()
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
                if (event.mouseButton.x >= width * 0.10 &&
                    event.mouseButton.x <= width * 0.28)
                {
                    if (event.mouseButton.y >= height * 0.25 &&
                        event.mouseButton.y <= height * 0.30)
                    {
                        std::cout << "Gameplay: 'Back To Game' button pressed\n";
                        m_screenName = "game_screen";
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        std::cout << "Gameplay: 'Main Menu' button pressed\n";
                        m_sectionName = "menu";
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        std::cout << "Gameplay: 'Settings' button pressed\n";
                        m_screenName = "settings_screen";
                    }
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_screenName = "game_screen";
            }
        }
    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::settingsScreenInput()
{
    sf::Event event;
    float width = m_window->getSize().x;
    float height = m_window->getSize().y;
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
                        std::cout << "Gameplay: Play Music 'Yes' button pressed\n";
                        m_settings->playMusic = true;
                        if (m_settings->playMusic && m_music->getStatus() == sf::Music::Status::Stopped)
                        {
                            m_music->play();
                        }
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        std::cout << "Gameplay: Play Audio 'Yes' button pressed\n";
                        m_settings->playAudio = true;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        std::cout << "Gameplay: Difficulty 'Easy' button pressed\n";
                        m_settings->difficulty = 0;
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        std::cout << "Gameplay: FPS '30' button pressed\n";
                        m_settings->frameRate = 30;
                        m_window->setFramerateLimit(m_settings->frameRate);
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        std::cout << "Gameplay: Show FPS 'Yes' button pressed\n";
                        m_settings->showFps = true;
                    }
                }
                else if (event.mouseButton.x >= width * 0.40 &&
                         event.mouseButton.x <= width * 0.48)
                {
                    if (event.mouseButton.y >=height * 0.25 &&
                        event.mouseButton.y <=height * 0.30)
                    {
                        std::cout << "Gameplay: Play Music 'No' button pressed\n";
                        m_settings->playMusic = false;
                        if (!m_settings->playMusic && m_music->getStatus() == sf::Music::Status::Playing)
                        {
                            m_music->stop();
                        }
                    }
                    else if (event.mouseButton.y >= height * 0.35 &&
                             event.mouseButton.y <= height * 0.40)
                    {
                        std::cout << "Gameplay: Play Audio 'No' button pressed\n";
                        m_settings->playAudio = false;
                    }
                    else if (event.mouseButton.y >= height * 0.45 &&
                             event.mouseButton.y <= height * 0.50)
                    {
                        std::cout << "Gameplay: Difficulty 'Hard' button pressed\n";
                        m_settings->difficulty = 1;
                    }
                    else if (event.mouseButton.y >= height * 0.55 &&
                             event.mouseButton.y <= height * 0.60)
                    {
                        std::cout << "Gameplay: FPS '60' button pressed\n";
                        m_settings->frameRate = 60;
                        m_window->setFramerateLimit(m_settings->frameRate);
                    }
                    else if (event.mouseButton.y >= height * 0.65 &&
                             event.mouseButton.y <= height * 0.70)
                    {
                        std::cout << "Gameplay: Show FPS 'No' button pressed\n";
                        m_settings->showFps = false;
                    }
                }
                else if (event.mouseButton.x >= width * 0.50 &&
                         event.mouseButton.x <= width * 0.56)
                {
                    if (event.mouseButton.y >= height * 0.55 &&
                        event.mouseButton.y <= height * 0.6)
                    {
                        std::cout << "Gameplay: FPS '120' button pressed\n";
                        m_settings->frameRate = 120;
                        m_window->setFramerateLimit(m_settings->frameRate);
                    }
                }
                else if (event.mouseButton.x >= width * 0.10 &&
                         event.mouseButton.x <= width * 0.16)
                {
                    if (event.mouseButton.y >= height * 0.75 &&
                        event.mouseButton.y <= height * 0.80)
                    {
                        updateSettingsStruct();
                        m_screenName = "paused_screen";
                    }
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_screenName = "paused_screen";
            }
        }
    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::renderSettingsScreen()
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
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::calculatePlayerVelocity()
{
    float x_distance = m_squareToMoveTo.getPosition().x + 0.5 * squareSize - player.x;
    float y_distance = m_squareToMoveTo.getPosition().y + 0.5 * squareSize - player.y;
    float total_distance = std::abs(x_distance) + std::abs(y_distance);
    
    if (m_squareToMoveTo.getPosition().x == -1 || total_distance < 2)
    {
        player.velocity.x = 0;
        player.velocity.y = 0;
        return;
    }

    player.velocity.x = (-75 * x_distance / total_distance) / m_settings->frameRate;
    player.velocity.y = (-75 * y_distance / total_distance) / m_settings->frameRate;
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::updateSettingsStruct()
{
    std::fstream file("user_data/settings.csv", std::ios::out);
    const char comma = ',';
    file << "PLAY_MUSIC, " << m_settings->playMusic << '\n';
    file << "PLAY_AUDIO, " << m_settings->playAudio << '\n';
    file << "DIFFICULTY, " << m_settings->difficulty << '\n';
    file << "FRAME_RATE, " << m_settings->frameRate << '\n';
    file << "SHOW_FPS, "   << m_settings->showFps << '\n';
    file << "SAVESLOT_1, " << m_settings->saveSlot1 << '\n';
    file << "SAVESLOT_2, " << m_settings->saveSlot2 << '\n';
    file << "SAVESLOT_3, " << m_settings->saveSlot3 << '\n';
    m_window->setFramerateLimit(m_settings->frameRate);
    file.close();
}