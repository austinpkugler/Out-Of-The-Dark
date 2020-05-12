#include "gameplay.h"

Gameplay::Gameplay(sf::RenderWindow* window, Settings* settings, float width, float height, std::string fileName, int saveSlot)
{
    m_window = window;
    m_settings = settings;
    m_width = width;
    m_height = height;
    objectsToDisplay = 25; // draw 25 squares on a screen
    TEXTURE_SIZE = 250.0f; // size of square in pixels

    deathScreenTexture = new sf::Texture();
    hardModeTexture = new sf::Texture();
    
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
    player.x = playerCoords.x + 0.5*squareSize;
    player.y = playerCoords.y + 0.5*squareSize;
    player.sprite.setPosition(player.x, player.y);

    m_highlightedGridRect.setSize(sf::Vector2f(squareSize, squareSize));
    m_highlightedGridRect.setFillColor(sf::Color(230, 230, 220, 50));

    m_squareToMoveTo.setSize(sf::Vector2f(squareSize, squareSize));
    m_squareToMoveTo.setFillColor(sf::Color(20, 20, 20, 200));
    m_squareToMoveTo.setPosition(-1, -1);

}

Gameplay::~Gameplay()
{
}

void Gameplay::load()
{
    for (int i = 0; i < 8; i++)
    {
        vectorOfTextures.push_back(new sf::Texture());
    }

    if (!vectorOfTextures[0]->loadFromFile("assets/blue_floor_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[1]->loadFromFile("assets/blue_floor_trapped_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[2]->loadFromFile("assets/blue_floor_fire_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[3]->loadFromFile("assets/death_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[4]->loadFromFile("assets/wall_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[5]->loadFromFile("assets/alien_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[6]->loadFromFile("assets/start_texture.png"))
    {
        std::exit(1);
    }
    if (!vectorOfTextures[7]->loadFromFile("assets/end_texture.png"))
    {
        std::exit(1);
    }
    if (!player.texturePtr->loadFromFile("assets/player.png"))
    {
        std::exit(1);
    }
    if (!deathScreenTexture->loadFromFile("assets/death_background.png"))
    {
        std::exit(1);
    }
    if (!hardModeTexture->loadFromFile("assets/hard_mode_background.png"))
    {
        std::exit(1);
    }
    player.sprite.setTexture(*player.texturePtr);
    player.sprite.setScale((squareSize / 240.0f) * 0.7, (squareSize / 240.0f) * 0.7);
    player.sprite.setOrigin(player.sprite.getLocalBounds().width/2, 
                            player.sprite.getLocalBounds().height/2);

    deathScreenSprite.setTexture(*deathScreenTexture);
    deathScreenSprite.setScale(m_width / deathScreenSprite.getLocalBounds().width,
                                m_height / deathScreenSprite.getLocalBounds().height);

    hardModeSprite.setTexture(*hardModeTexture);
    hardModeSprite.setScale(m_width / hardModeSprite.getLocalBounds().width,
                                m_height / hardModeSprite.getLocalBounds().height);

    populateGrid();
    // std::cout << "load() is finished\n";
}

void Gameplay::update()
{
    GameObject blockMouseOn = blockMouseIsOn();
    // std::cout << "update is called\n";
    applyDamage();
    if (playerWon())
    {
        std::cout << "player won!\n";
        std::exit(1);
    }

    if (blockMouseOn.arrIndexX != -1)
    {
        m_highlightedGridRect.setPosition((blockMouseOn.arrIndexX - upperLeftSquare.x)*squareSize,
                                          (blockMouseOn.arrIndexY - upperLeftSquare.y)*squareSize);
    }
    // std::cout << "update is finished\n";
}

void Gameplay::handleInput()
{
    // std::cout << "handleInput is called\n";
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
                if (player.alive)
                {
                    GameObject blockMouseOn = blockMouseIsOn();
                    if (blockMouseOn.arrIndexX != -1)
                    {
                        m_squareToMoveTo.setPosition((blockMouseOn.arrIndexX - upperLeftSquare.x) * squareSize,
                                                     (blockMouseOn.arrIndexY - upperLeftSquare.y) * squareSize);
                    }
                }
                else
                {
                    player.alive = true;
                    player.healthPercent = 100;
                }
            }
        }
    }
}

void Gameplay::render()
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
        if (m_settings->difficulty = 0)
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

void Gameplay::displayHealth()
{
    healthBar.setSize(sf::Vector2f((player.healthPercent * 0.15) / 100 * m_width, 0.01 * m_height));

    // std::cout << (m_height* 0.05) << " playery health\n";
    
    m_window->draw(healthBarBg);
    m_window->draw(healthBar);
}

void Gameplay::applyDamage()
{
    // std::cout << "applyDamage is called\n";
    std::vector<GameObject> objectsStandingOn = blocksPlayerIsOn();
    // If the texture is a trap
    for (int i=0; i < objectsStandingOn.size(); ++i)
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

void Gameplay::populateGrid()
{
    // std::cout << "populateGrid() is called\n";
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
            m_maze[x][y].sprite.setScale(squareSize/TEXTURE_SIZE, squareSize/TEXTURE_SIZE);
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
                case 4:     // if the texture ise a stone wall
                    m_maze[x][y].walkable = 0;
                    break;
                case 5:    // if the texture is diseased path
                    m_maze[x][y].walkable = 1;
                    break;
                case 6:    // if the texture is maze start
                    m_maze[x][y].walkable = 1;
                    startingBlock.x = m_maze[x][y].arrIndexX;
                    startingBlock.y = m_maze[x][y].arrIndexY;
                    break;
                case 7:   // if the texture is maze end
                    m_maze[x][y].walkable = 1;
                    break;
            };
        }
    }
    file.close();
}


void Gameplay::renderGrid()
{
    // std::cout << "rendergrid called\n";

    for (int arr_x = upperLeftSquare.x; arr_x < (upperLeftSquare.x + objectsToDisplay); ++arr_x)
    {
        for (int arr_y = upperLeftSquare.y; arr_y < (upperLeftSquare.y + objectsToDisplay); ++arr_y)
        {
            float x_coords = (m_maze[arr_x][arr_y].arrIndexX - upperLeftSquare.x) * squareSize;
            float y_coords = (m_maze[arr_x][arr_y].arrIndexY - upperLeftSquare.y) * squareSize;
            m_maze[arr_x][arr_y].sprite.setPosition(x_coords, y_coords);
            m_window->draw(m_maze[arr_x][arr_y].sprite);
        }
    }
}

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

const GameObject Gameplay::blockMouseIsOn() const
{
    float mouseX = sf::Mouse::getPosition(*m_window).x;
    float mouseY = sf::Mouse::getPosition(*m_window).y;
    mouseX /= m_window->getSize().x;
    mouseY /= m_window->getSize().y;
    mouseX *= m_width;
    mouseY *= m_height;
    int x = (mouseX / squareSize) + upperLeftSquare.x;
    int y = (mouseY / squareSize) + upperLeftSquare.y;

    if (x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)
    {
        return GameObject();
    }
    return m_maze[x][y];
}

sf::Vector2f Gameplay::indexToCoord(unsigned int x, unsigned int y) const
{
    return sf::Vector2f((x - upperLeftSquare.x) * squareSize, (y - upperLeftSquare.y) * squareSize);
}


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
        if (player.x - 0.5*player.sprite.getLocalBounds().width < indexToCoord(x, y).x)
        {
            blocks.push_back(m_maze[x-1][y]);
        }
    }
    if (!(x+1 >= GRID_SIZE || x+1 < 0 || y >= GRID_SIZE || y < 0)) // if not out of bounds
    {
        if (player.x - 0.5*player.sprite.getLocalBounds().width > indexToCoord(x+1, y).x)
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
        if (player.y - 0.5*player.sprite.getLocalBounds().height > indexToCoord(x, y+1).y)
        {
            blocks.push_back(m_maze[x-1][y+1]);
        }
    }
    
    return blocks;
}
