#include "mazeBuilder.h"

/**
 * @brief Constructor for MazeBuilder class.
 * @details Sets member variables to corresponding parameters, and other 
 * necessary function to start the section such as load().
 * @throw None
 * @param sf::RenderWindow* window - a pointer to a window. used for rendering sprites to screen
 * @param Settings* settings - a pointer to a Settings struct, used for editing and using setting info
 * @param float width - width of starting window (used for scaling)
 * @param float height - height of starting window (used for scaling)
 */
MazeBuilder::MazeBuilder(sf::RenderWindow* window, Settings* settings, float width, float height)
{
    m_window = window;
    m_width = width;
    m_height = height;
    m_screenName = "main_screen";
    m_sectionName = "maze_builder";
    m_backgroundTexture = new sf::Texture();
    m_settings = settings;

    load();

    // member variables for grid
    m_MAX_GRID_SIZE = 512;
    m_upperLeftSquare.x = m_MAX_GRID_SIZE/2;
    m_upperLeftSquare.y = m_MAX_GRID_SIZE/2;
    m_squaresToDisplay = 25;
    m_mazeOrigin.x = 0.2 * m_width;  // left edge of grid
    m_mazeOrigin.y = 0.1 * m_height; // top edge of grid
    m_squareSize = static_cast<float>(std::max(m_width - m_mazeOrigin.x, m_height - m_mazeOrigin.y)) / m_squaresToDisplay;

    // highlighted square when mouse is on grid
    m_highlightedGridRect = sf::RectangleShape(sf::Vector2f(m_squareSize, m_squareSize));
    m_highlightedGridRect.setFillColor(sf::Color(230, 230, 220, 150));

    // sets texture to 0 (first texture)
    m_selectedTextureIndex = 0;
    m_textureSize = 250.0f; // size of texture (250x250)
    populateGrid();
    m_highlightedGridIndex.x = -1;
    m_highlightedGridIndex.y = -1;
    m_mazeFileName = "";

    // scales the background to screen size
    m_backgroundSprite.setScale(m_width / m_backgroundSprite.getLocalBounds().width,
                                m_height / m_backgroundSprite.getLocalBounds().height);
    
    // rectangle to highlight current texture
    m_textureHighlightRect = sf::RectangleShape(sf::Vector2f(0.16 * m_width, 0.08 * m_height));
    m_textureHighlightRect.setFillColor(sf::Color(230, 230, 220, 150));

}


/**
 * @brief Destructor for MazeBuilder class.
 * @details Deallocates all heap pointers.
 * @throw None
 * @param None
 */
MazeBuilder::~MazeBuilder()
{
    delete m_backgroundTexture;
    m_backgroundTexture = nullptr;

    for (int i=0; i < m_textures.size(); ++i)
    {
        delete m_textures[i];
        m_textures[i] = nullptr;
    }
}

/**
 * @brief Manages the loading of all MazeBuilder assets.
 * @details Loads all section wide assets such as backgrounds, textures, and fonts.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::load()
{
    if (!m_backgroundTexture->loadFromFile("assets/maze_builder_background.png"))
    {
        std::exit(1);   
    }
    m_backgroundSprite.setTexture(*m_backgroundTexture);

    if (!m_font.loadFromFile("assets/rm_typerighter.ttf"))
    {
        std::exit(1);
    }
    // text at bottom right for telling position of grid
    m_gridLocation.setFont(m_font);
    m_gridLocation.setCharacterSize(24);
    m_gridLocation.setFillColor(sf::Color::White);
    m_gridLocation.setPosition(0.82*m_width, 0.95*m_height);

    // populates texture vector for grid 
    for (int i = 0; i < 8; i++)
    {
        m_textures.push_back(new sf::Texture());
    }

    if (!m_textures[0]->loadFromFile("assets/blue_floor_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[1]->loadFromFile("assets/blue_floor_trapped_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[2]->loadFromFile("assets/blue_floor_fire_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[3]->loadFromFile("assets/death_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[4]->loadFromFile("assets/wall_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[5]->loadFromFile("assets/alien_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[6]->loadFromFile("assets/start_texture.png"))
    {
        std::exit(1);
    }
    if (!m_textures[7]->loadFromFile("assets/end_texture.png"))
    {
        std::exit(1);
    }
}

/**
 * @brief Updates the MazeBuilder between input handling and rendering.
 * @details resets the position to the current texture rectangle based off of m_selectedTextureIndex,
 * and resets the string to print at the bottom right screen for the current block position based
 * off of the current m_highlightedGridRect coordinates.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::update()
{

    if (m_selectedTextureIndex == 0)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.11*m_height);
    }
    else if (m_selectedTextureIndex == 1)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.21*m_height);
    }
    else if (m_selectedTextureIndex == 2)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.31*m_height);
    }
    else if (m_selectedTextureIndex == 3)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.41*m_height);
    }
    else if (m_selectedTextureIndex == 4)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.51*m_height);
    }
    else if (m_selectedTextureIndex == 5)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.61*m_height);
    }
    else if (m_selectedTextureIndex == 6)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.71*m_height);
    }
    else if (m_selectedTextureIndex == 7)
    {
        m_textureHighlightRect.setPosition(0.033*m_width, 0.81*m_height);
    }

    m_gridLocation.setString("Current position: (" + std::to_string(m_highlightedGridIndex.x)
                             + ", " + std::to_string(m_highlightedGridIndex.y) + ")");
}

/**
 * @brief Polls input and updates screen based off of it.
 * @details Polls input and updates screen based off of input. Full list of actions include
 * closing the window if the user presses the upper right red square on the window,
 * changing the selected texture if the mouse is clicked on a texture,
 * loading the file if the load button is pressed,
 * saving the file if the save button is pressed,
 * previewing the maze if the preview button is pressed,
 * changing the highlightedSquare if the mosue moves to a different square,
 * changing the texture of the highlighted square if the left mouse button is down,
 * and changing the upperLeftSquare if the user presses arrow keys or wasd keys
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::handleInput()
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
                // loop through displayable blocks and see if mouse is on them if so, set their texture to m_selectedTextureIndex
                // check all texture options and set m_selectedTextureIndex to that
                float width = m_window->getSize().x;
                float height = m_window->getSize().y;
                if (event.mouseButton.x >= 0.03 * width && event.mouseButton.x <= 0.19 * width)
                {
                    if (event.mouseButton.y >= 0.11 * height && event.mouseButton.y <= 0.19 * height)
                    {
                        // std::cout << "texture 1 pressed\n";
                        m_selectedTextureIndex = 0;
                        
                    }
                    else if (event.mouseButton.y >= 0.21 * height && event.mouseButton.y <= 0.29 * height)
                    {
                        // std::cout << "texture 2 pressed\n";
                        m_selectedTextureIndex = 1;
                    }
                    else if (event.mouseButton.y >= 0.31 * height && event.mouseButton.y <= 0.39 * height)
                    {
                        // std::cout << "texture 3 pressed\n";
                        m_selectedTextureIndex = 2;
                    }
                    else if (event.mouseButton.y >= 0.41 * height && event.mouseButton.y <= 0.49 * height)
                    {
                        // std::cout << "texture 4 pressed\n";
                        m_selectedTextureIndex = 3;
                    }
                    else if (event.mouseButton.y >= 0.51 * height && event.mouseButton.y <= 0.59 * height)
                    {
                        // std::cout << "texture 5 pressed\n";
                        m_selectedTextureIndex = 4;
                    }
                    else if (event.mouseButton.y >= 0.61 * height && event.mouseButton.y <= 0.69 * height)
                    {
                        // std::cout << "texture 6 pressed\n";
                        m_selectedTextureIndex = 5;
                    }
                    else if (event.mouseButton.y >= 0.71 * height && event.mouseButton.y <= 0.79 * height)
                    {
                        // std::cout << "texture 7 pressed\n";
                        m_selectedTextureIndex = 6;
                    }
                    else if (event.mouseButton.y >= 0.81 * height && event.mouseButton.y <= 0.89 * height)
                    {
                        // std::cout << "texture 8 pressed\n";
                        m_selectedTextureIndex = 7;
                    }
                }

                if (event.mouseButton.y >= 0.015 * height && event.mouseButton.y <= 0.085 * height)
                {
                    if (event.mouseButton.x >= 0.22 * width && event.mouseButton.x <= 0.28 * width)
                    {
                        loadFromFile();
                    }

                    if (event.mouseButton.x >= 0.32 * width && event.mouseButton.x <= 0.38 * width)
                    {
                        generateFile();
                    }
                    if (event.mouseButton.x >= 0.4 * width && event.mouseButton.x <= 0.49 * width)
                    {
                        if (m_screenName == "main_screen")
                        {
                            toPreview();
                        }
                        else if (m_screenName == "preview_screen")
                        {
                            toMain();
                        }
                    }

                    if (event.mouseButton.x >= 0.91 * width && event.mouseButton.x <= 0.98 * width)
                    {
                        m_sectionName = "menu"; // back button pressed
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // if mouse left is down (not an event)
        {
            for (int arr_x = m_upperLeftSquare.x; arr_x < (m_upperLeftSquare.x + m_squaresToDisplay); ++arr_x)
            {
                for (int arr_y = m_upperLeftSquare.y; arr_y < (m_upperLeftSquare.y + m_squaresToDisplay); ++arr_y)
                {
                    if (isMouseOnBlock(m_grid[arr_x][arr_y]))
                    {
                        m_grid[arr_x][arr_y].texture = m_selectedTextureIndex;
                        m_grid[arr_x][arr_y].sprite.setScale(m_squareSize/m_textureSize,
                                                             m_squareSize/m_textureSize);
                    }
                }
            }
        }

        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // if mouse right is down (not an event)
        {
            for (int arr_x = m_upperLeftSquare.x; arr_x < (m_upperLeftSquare.x + m_squaresToDisplay); ++arr_x)
            {
                for (int arr_y = m_upperLeftSquare.y; arr_y < (m_upperLeftSquare.y + m_squaresToDisplay); ++arr_y)
                {
                    if (isMouseOnBlock(m_grid[arr_x][arr_y]))
                    {
                        m_grid[arr_x][arr_y].texture = 4;
                        m_grid[arr_x][arr_y].sprite.setScale(m_squareSize/m_textureSize,
                                                             m_squareSize/m_textureSize);
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            m_highlightedGridIndex.x = m_highlightedGridIndex.y = -1; // make no highlighted square
            for (int x = 0; x < m_squaresToDisplay; ++x)
                {
                    for (int y = 0; y < m_squaresToDisplay; ++y)
                    {
                        int xIndex = x + m_upperLeftSquare.x;
                        int yIndex = y + m_upperLeftSquare.y;
                        if (isMouseOnBlock(m_grid[xIndex][yIndex]) == true)
                        {
                            m_highlightedGridIndex.x = xIndex;
                            m_highlightedGridIndex.y = yIndex;
                            return;
                        }
                    }
                }
            

            // loop through displayable blocks and see if mouse is on them if so, set m_highlighted to that
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                if (m_upperLeftSquare.y - 1 >= 0) // move up if possible
                {
                    m_upperLeftSquare.y--;
                }
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                if (m_upperLeftSquare.x - 1 >= 0) // move up if possible
                {
                    m_upperLeftSquare.x--;
                }
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                if (m_upperLeftSquare.y + m_squaresToDisplay < m_MAX_GRID_SIZE) // move up if possible
                {
                    m_upperLeftSquare.y++;
                }
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                if (m_upperLeftSquare.x + m_squaresToDisplay < m_MAX_GRID_SIZE) // move up if possible
                {
                    m_upperLeftSquare.x++;
                }
            }
        }
    }
}

/**
 * @brief Renders the MazeBuilder screen.
 * @details Renders the background, highlighted texture, highlighted grid square (if there is one), and
 * the grid location
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::render()
{
    m_window->draw(m_backgroundSprite);
    m_window->draw(m_textureHighlightRect);
    drawGrid();

    if (m_highlightedGridIndex.x != -1) // if there is a highlighted grid square
    {
        highlightGridSquare();
    }

    m_window->draw(m_gridLocation);
}

/**
 * @brief Saves current maze data to a file.
 * @details Invokes a python script to open file explorer for user to save file. If a filename exists, it 
 * has that as the default save name
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::generateFile()
{
    if (m_mazeFileName == "") // if there isnt a fileName, dont have recommended name
    {
        m_mazeFileName = "python getMazeName/saveAs.py";
    }
    else // otherwise do have recommended name
    {
        m_mazeFileName = "python getMazeName/saveAs.py \"" + m_mazeFileName + "\"";
    }
    system(m_mazeFileName.c_str()); // get filename to save as
    std::fstream file("getMazeName/filename.txt");
    std::getline(file, m_mazeFileName);
    file.close();

    file.open(m_mazeFileName, std::ios::out);
    file << m_MAX_GRID_SIZE << '\n';
    for (int x = 0; x < m_MAX_GRID_SIZE; ++x)
    {
        for (int y = 0; y < m_MAX_GRID_SIZE; ++y)
        {
            file << m_grid[x][y].texture << '\n';
        }
    }

    file.close();
}

/**
 * @brief Loads .maze file into maze builder.
 * @details invokes a python script to open file explorer for user to load file. If a filename already exists, it 
 * has that as the default load name
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::loadFromFile()
{
    // opens file using python tkinter
    system("python getMazeName/openFile.py");

    std::fstream file("getMazeName/filename.txt", std::ios::in);
    getline(file, m_mazeFileName);
    file.close();

    file.open(m_mazeFileName, std::ios::in);
    file >> m_MAX_GRID_SIZE;
    for (int x = 0; x < m_MAX_GRID_SIZE; ++x)
    {
        for (int y = 0; y < m_MAX_GRID_SIZE; ++y)
        {
            file >> m_grid[x][y].texture;
        }
    }

    file.close();
}

/**
 * @brief Populates the grid with default textures (wall).
 * @details Loops through the grid and creates a 2d array with proper textures and scales for walls
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::populateGrid()
{
    for (int x = 0; x < m_MAX_GRID_SIZE; ++x)
    {
        m_grid.push_back(std::vector<gridStruct>());
        for (int y = 0; y < m_MAX_GRID_SIZE; ++y)
        {
            gridStruct currentStruct;
            currentStruct.x = x;
            currentStruct.y = y;
            currentStruct.texture = 4;
            currentStruct.sprite.setScale(m_squareSize/250.0f,
                                           m_squareSize/250.0f);
            m_grid[x].push_back(currentStruct);
        }
    }
}

/**
 * @brief Draws the 2D grid of tiles.
 * @details Has a 2D nested for loop looping through all squares to display. It then sets the correct position and texture, and 
 * draws the sprite to the screen.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::drawGrid()
{
    for (int arr_x = m_upperLeftSquare.x; arr_x < (m_upperLeftSquare.x + m_squaresToDisplay); ++arr_x)
    {
        for (int arr_y = m_upperLeftSquare.y; arr_y < (m_upperLeftSquare.y + m_squaresToDisplay); ++arr_y)
        {
            float x_coords = (m_grid[arr_x][arr_y].x - m_upperLeftSquare.x) * m_squareSize + m_mazeOrigin.x;
            float y_coords = (m_grid[arr_x][arr_y].y - m_upperLeftSquare.y) * m_squareSize + m_mazeOrigin.y;
            m_grid[arr_x][arr_y].sprite.setPosition(x_coords, y_coords);
            m_grid[arr_x][arr_y].sprite.setTexture(*m_textures[m_grid[arr_x][arr_y].texture]);
            m_window->draw(m_grid[arr_x][arr_y].sprite);

        }
    }
}

/**
 * @brief Checks whether the mouse is currently on a passed tile.
 * @details First, the coordinates of the block's x and y are converted from array indexes to coordinates on the screen.
 * The Mouse coordinates are then scaled to fit the original screen size. The function then returns True if 
 * the mouse is in the boundaries of the block, False if not.
 * @throw None
 * @param const gridStruct& block - a gridStruct object to check if the mouse is on
 * @return bool - True if the mouse is in the block parameter, False otherwise
 */
bool MazeBuilder::isMouseOnBlock(const gridStruct& block) const
{
    float x_coords, y_coords;
    x_coords = (block.x - m_upperLeftSquare.x) * m_squareSize + m_mazeOrigin.x;
    y_coords = (block.y - m_upperLeftSquare.y) * m_squareSize + m_mazeOrigin.y;

    float mouseX = sf::Mouse::getPosition(*m_window).x;
    float mouseY = sf::Mouse::getPosition(*m_window).y;

    // scales mouse coords
    mouseX /= m_window->getSize().x;
    mouseY /= m_window->getSize().y;
    mouseX *= m_width;
    mouseY *= m_height;
    
    // if mouse in block
    if (x_coords <= mouseX && mouseX <= x_coords + m_squareSize &&
        y_coords <= mouseY && mouseY <= y_coords + m_squareSize)
    {
        return true;
    }
    return false;

}

/**
 * @brief Draws the highlighted grid square to the screen.
 * @details First, coordinates of the highlightedGrid square are converted from indexes to pixels.
 * The coordinates are then set to the m_highlightedGridRect object, and drawn to the
 * screen.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::highlightGridSquare()
{
    // gets location to be drawn on screen
    float pixelX = (m_highlightedGridIndex.x - m_upperLeftSquare.x)*m_squareSize + m_mazeOrigin.x;
    float pixelY = (m_highlightedGridIndex.y - m_upperLeftSquare.y)*m_squareSize + m_mazeOrigin.y;

    m_highlightedGridRect.setPosition(pixelX, pixelY);
    m_window->draw(m_highlightedGridRect);
}

/**
 * @brief Resizes the square size and grid to preview most of the maze on one screen (either zooms in or out).
 * @details First, the m_screenName is set to "preview_screen". Then, the maze is iterated through using 2D
 * nested for loops, and the bottom, top, left, and right sides of the maze are found.
 * If not all of them are found, then the preview_screen cannot work and the function is exited.
 * the m_squaresToDisplay is updated based on the bottom, top, left, and right values, and the grid is resized.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::toPreview()
{
    m_screenName = "preview_screen";

    int bottom = -1, top = -1, left = -1, right = -1;
    
    for (int i=0; i < m_MAX_GRID_SIZE; ++i)
    {
        for (int z=0; z < m_MAX_GRID_SIZE; ++z)
        {
            if (m_grid[i][z].texture != 4)
            {
                right = m_grid[i][z].x;
                if (left == -1)
                {
                    left = m_grid[i][z].x;
                }
            }
            if (m_grid[z][i].texture != 4)
            {
                bottom = m_grid[z][i].y;
                if (top == -1)
                {
                    top = m_grid[z][i].y;
                }
            }
        }
    }
    if (left == -1 || right == -1 || top == -1 || bottom == -1)
    {
        return;
    }
    m_squaresToDisplay = std::max(right-left, bottom-top)+2;
    m_squareSize = static_cast<float>(std::max(m_width - m_mazeOrigin.x, m_height - m_mazeOrigin.y)) / m_squaresToDisplay;
    m_upperLeftSquare.x = left;
    m_upperLeftSquare.y = top;
    for (int i=0; i < m_MAX_GRID_SIZE; ++i)
    {
        for (int z = 0; z < m_MAX_GRID_SIZE; ++z)
        {
            m_grid[i][z].sprite.setScale(m_squareSize/250.0f,
                                           m_squareSize/250.0f);
        }
    }
    m_highlightedGridRect.setSize(sf::Vector2f(m_squareSize, m_squareSize));
}


/**
 * @brief Puts the maze builder back in main mode, from preview mode.
 * @details First, the m_screenName is set to "main_screen". The squaresToDisplay is set
 * back to its normal value, instead of being based on the number of blocks created as with
 * the preview mode. the squareSize, upperLeftSquare coordinates and sprite scales are
 * all calculated again to completely return back from preview_screen mode.
 * @throw None
 * @param None
 * @return None
 */
void MazeBuilder::toMain() // called after state machine is changed to main
{
    m_screenName = "main_screen";
    m_squaresToDisplay = 25;
    m_squareSize = static_cast<float>(std::max(m_width - m_mazeOrigin.x, m_height - m_mazeOrigin.y)) / m_squaresToDisplay;
    m_upperLeftSquare.x = m_MAX_GRID_SIZE/2;
    m_upperLeftSquare.y = m_MAX_GRID_SIZE/2;
    for (int i=0; i < m_MAX_GRID_SIZE; ++i)
    {
        for (int z = 0; z < m_MAX_GRID_SIZE; ++z)
        {
            m_grid[i][z].sprite.setScale(m_squareSize/250.0f,
                                           m_squareSize/250.0f);
        }
    }
    m_highlightedGridRect.setSize(sf::Vector2f(m_squareSize, m_squareSize));

}