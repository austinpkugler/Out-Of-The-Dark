#include "gameplay.h"

Gameplay::Gameplay(sf::RenderWindow* window, Settings* settings, float width, float height, std::string fileName, int saveSlot)
{
    m_window = window;
    m_settings = settings;
    m_width = width;
    m_height = height;
    objectsToDisplay = 25; // draw 25 squares on a screen
    TEXTURE_SIZE = 250.0f; // size of square in pixels
    
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

    player.x = 500;
    player.y = 500;

    this->fileName = fileName;
    squareSize = static_cast<float>(std::max(m_width, m_height)) / objectsToDisplay;

    healthBarBg = sf::RectangleShape(sf::Vector2f(0.15 * m_width, 0.01 * height));
    healthBarBg.setFillColor(sf::Color(255, 26, 26));
    healthBarBg.setPosition(squareSize, 0.93 * m_height);

    healthBar = sf::RectangleShape(sf::Vector2f(0.15 * m_width, 0.01 * height));
    healthBar.setFillColor(sf::Color(0, 128, 0));
    healthBar.setPosition(squareSize, 0.93 * m_height);

    load();

    upperLeftSquare.x = startingBlock.x - (objectsToDisplay - 1) / 2.0f;
    upperLeftSquare.y = startingBlock.y - ((objectsToDisplay / m_width) * m_height-1) / 2.0f;

    std::cout << upperLeftSquare.x << " " << upperLeftSquare.y << '\n';
    std::cout << startingBlock.x << " " << startingBlock.y << '\n';

    std::cout << "constructor is finished\n";
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

    populateGrid();
    // std::cout << "load() is finished\n";
}

void Gameplay::update()
{
    // std::cout << "update is called\n";
    applyDamage();
    if (playerWon())
    {
        std::cout << "player won!\n";
        std::exit(1);
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
    }
}

void Gameplay::render()
{
    // std::cout << "render() is called\n";
    renderGrid();
    displayHealth();
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
    GameObject standingOn = blockPlayerIsOn();
    if (standingOn.textureIndex == 1)
    {
        player.healthPercent -= 45;
        // The trap has been set off, so reset the square to be a path with no trap.
        m_maze[standingOn.arrIndexX][standingOn.arrIndexY].textureIndex = 0;
        m_maze[standingOn.arrIndexX][standingOn.arrIndexY].sprite.setTexture(*vectorOfTextures[0]);
    }
    else if (standingOn.textureIndex == 2) // player standing on fire
    {
        player.burning == true;
    }
    else if (standingOn.textureIndex == 5) // player standing on diseased path
    {
        player.healthPercent -= 0.1;
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

    if (player.healthPercent < 0)
    {
        player.healthPercent == 0;
        std::cout << "YOU DIED!\n";
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

const GameObject Gameplay::blockPlayerIsOn() const
{
    int x = (player.x / squareSize) + upperLeftSquare.x;
    int y = (player.y / squareSize) + upperLeftSquare.y;

    if (x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)
    {
        return GameObject();
    }
    return m_maze[x][y];
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
    if (blockPlayerIsOn().textureIndex == 7)
    {
        return true;
    }
    return false;
}

const GameObject Gameplay::blockMouseIsOn() const
{
    int x = (player.x / squareSize) + upperLeftSquare.x;
    int y = (player.y / squareSize) + upperLeftSquare.y;

    if (x >= GRID_SIZE || x < 0 || y >= GRID_SIZE || y < 0)
    {
        return GameObject();
    }
    return m_maze[x][y];
}