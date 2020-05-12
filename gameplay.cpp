#include "gameplay.h"

/**
 * @brief
 * @details
 * @throw
 * @param
 */
Gameplay::Gameplay(sf::RenderWindow* window, Settings* settings, float width, float height, std::string fileName, int saveSlot)
{
    m_window = window;
    m_settings = settings;
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

    std::cout << upperLeftSquare.x << " " << upperLeftSquare.y << '\n';
    std::cout << startingBlock.x << " " << startingBlock.y << '\n';
    
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
 * @brief
 * @details
 * @throw
 * @param
 */
Gameplay::~Gameplay()
{
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
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
    if (!pausedScreenTexture->loadFromFile("assets/settings_screen_overlay_background.png"))
    {
        std::cout << "Gameplay: Failed to load asset 'settings_screen_overlay_background.png'\n";
        std::exit(1);
    }
    player.sprite.setTexture(*player.texturePtr);
    player.sprite.setScale((squareSize / 240.0f) * 0.5, (squareSize / 240.0f) * 0.5);
    player.sprite.setOrigin(player.sprite.getLocalBounds().width/2, 
                            player.sprite.getLocalBounds().height/2);

    deathScreenSprite.setTexture(*deathScreenTexture);
    deathScreenSprite.setScale(m_width / deathScreenSprite.getLocalBounds().width,
                                m_height / deathScreenSprite.getLocalBounds().height);

    hardModeSprite.setTexture(*hardModeTexture);
    hardModeSprite.setScale(m_width / hardModeSprite.getLocalBounds().width,
                                m_height / hardModeSprite.getLocalBounds().height);

    pausedScreenSprite.setTexture(*pausedScreenTexture);
    pausedScreenSprite.setScale(m_width / pausedScreenSprite.getLocalBounds().width,
                                m_height / pausedScreenSprite.getLocalBounds().height);

    populateGrid();
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::update()
{
    if (m_screenName == "game_screen")
    {
        calculatePlayerVelocity();
        GameObject blockMouseOn = blockMouseIsOn();
        applyDamage();
        if (playerWon())
        {
            std::cout << "player won!\n";
        }

        m_squareToMoveTo.move(player.velocity.x, player.velocity.y);
        // std::cout << (blockMouseOn.arrIndexX - upperLeftSquare.x) * squareSize + gridOffset.x << '\n';
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
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::handleInput()
{
    if (m_screenName == "game_screen")
    {
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
                    if (player.alive)
                    {
                        GameObject blockMouseOn = blockMouseIsOn();
                        if (blockMouseOn.arrIndexX != -1)
                        {
                            m_squareToMoveTo.setPosition((blockMouseOn.arrIndexX - upperLeftSquare.x) * squareSize + gridOffset.x,
                                                        (blockMouseOn.arrIndexY - upperLeftSquare.y) * squareSize + gridOffset.y);
                        }
                    }
                    else
                    {
                        player.alive = true;
                        player.healthPercent = 100;
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

    }
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::render()
{
    if (m_screenName == "game_screen")
    {
        renderGrid();
        if (player.alive)
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
        else
        {
            m_window->draw(deathScreenSprite);
        }
    }
    else if (m_screenName == "paused_screen")
    {
        m_window->draw(pausedScreenSprite);
    }
    else if (m_screenName == "settings_screen")
    {

    }
}

/**
 * @brief
 * @details
 * @throw
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
void Gameplay::applyDamage()
{
    // std::cout << "applyDamage is called\n";
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
            player.burning == true;
        }
        // Else if the texture is diseased path
        else if (objectsStandingOn[i].textureIndex == 5) // player standing on diseased path
        {
            player.healthPercent -= 0.1;
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
    if (player.healthPercent <= 0)
    {
        player.healthPercent = 0;
        player.alive = false;
        load();
        // reset the player position
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
 * @details
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
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
void Gameplay::renderSettings()
{

}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
 */
bool Gameplay::playerWon()
{
    std::vector<GameObject> objectsStandingOn = blocksPlayerIsOn();
    for (int i=0; i < objectsStandingOn.size(); ++i)
    {
        if (objectsStandingOn[i].textureIndex == 7)
            {
                return true;
            }
    }
    return false;
}

/**
 * @brief
 * @details
 * @throw
 * @param
 * @return
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
 * @brief
 * @details
 * @throw
 * @param
 * @return
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
    unsigned int x = (player.x / squareSize) + upperLeftSquare.x;
    unsigned int y = (player.y / squareSize) + upperLeftSquare.y;

    if (!(x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    {
        blocks.push_back(m_maze[x][y]);
    }

    if (!(x-1 >= GRID_SIZE || x-1 < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    { 
        if (player.x - 0.5*player.sprite.getLocalBounds().width < indexToCoord(x, y).x + squareSize)
        {
            blocks.push_back(m_maze[x-1][y]);
        }
    }
    if (!(x+1 >= GRID_SIZE || x+1 < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    {
        if (player.x + 0.5*player.sprite.getLocalBounds().width > indexToCoord(x+1, y).x)
        {
            blocks.push_back(m_maze[x+1][y]);
        }
    }
    if (!(x >= GRID_SIZE || x < 0 || y-1 >= GRID_SIZE || y-1 < 0)) // if not out of bounds
    {
        if (player.y - 0.5*player.sprite.getLocalBounds().height < indexToCoord(x, y).y)
        {
            blocks.push_back(m_maze[x][y-1]);
        }
    }
    if (!(x >= GRID_SIZE || x < 0 || y+1 >= GRID_SIZE || y+1 < 0)) // if not out of bounds
    {
        if (player.y + 0.5*player.sprite.getLocalBounds().height > indexToCoord(x, y+1).y)
        {
            blocks.push_back(m_maze[x-1][y+1]);
        }
    }
    for (int i=0; i < blocks.size(); ++i)
    {
        std::cout << blocks[i].textureIndex << ' ';
    }
    std::cout << "\n";
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
                    // else if (event.mouseButton.y >= height * 0.55 &&
                    //          event.mouseButton.y <= height * 0.60)
                    // {
                    //     std::cout << "Menu: 'Quit' button pressed\n";
                    //     m_window->close();
                    // }
                }
            }
        }
    }
}

void Gameplay::calculatePlayerVelocity()
{
    float x_distance = m_squareToMoveTo.getPosition().x + 0.5*squareSize - player.x;
    float y_distance = m_squareToMoveTo.getPosition().y + 0.5*squareSize - player.y;
    float total_distance = std::abs(x_distance) + std::abs(y_distance);
    
    if (m_squareToMoveTo.getPosition().x == -1 || total_distance < 1)
    {
        player.velocity.x = 0;
        player.velocity.y = 0;
        return;
    }

    player.velocity.x = (-50 * x_distance / total_distance)/m_settings->frameRate;
    player.velocity.y = (-50 * y_distance / total_distance)/m_settings->frameRate;
}

