#pragma once

// Included C++11 Libraries
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>

// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

// Included Local Dependencies
#include "section.h"
#include "settings.h"

/**
 * Struct Name: gridStruct
 * Brief: Stores all data for a single square.
 * Description:
 *  Contains the index of the tile in the tile array, the type of tile, and
 *  the sprite texture of the tile.
 */
struct gridStruct
{
    unsigned int x;
    unsigned int y;
    unsigned int texture;
    sf::Sprite sprite;
};

/**
 * Class Name: MazeBuilder
 * Brief: Manages all Maze Builder processes
 * Description:
 *  The Game class contains all general functions for running the Maze builder.
 *  This includes displaying, updating, handling input, allowing usability and
 *  all other Maze Builder processes.
 */
class MazeBuilder: public Section
{
public:
    // Constructor and Destructor
    MazeBuilder(sf::RenderWindow* window, Settings* settings, float width, float height);
    ~MazeBuilder();

    // Public Member Functions for General MazeBuidler Processes
    virtual void load();            // Manages the loading of all MazeBuilder assets.
    virtual void update();          // Updates the MazeBuilder between input handling and rendering.
    virtual void handleInput();     // Polls input and updates screen based off of it.
    virtual void render();          // Renders the MazeBuilder screen.

private:
    // Private Member Functions for General MazeBuilder Processes
    void generateFile();            // Saves current maze data to a file.
    void loadFromFile();            // Loads .maze file into maze builder.
    void populateGrid();            // Populates the grid with default textures (wall).
    void drawGrid();                // Draws the 2D grid of tiles.
    bool isMouseOnBlock(const gridStruct& block) const;     // Checks whether the mouse is currently on a passed tile.
    void highlightGridSquare();     // Draws the highlighted grid square to the screen.
    void toPreview();               // Resizes the square size and grid to preview most of the maze on one screen (either zooms in or out).
    void toMain();                  // Puts the maze builder back in main mode, from preview mode.

    // Private SFML Member Variables
    sf::Texture* m_backgroundTexture;
    sf::Sprite m_backgroundSprite;
    sf::Vector2i m_upperLeftSquare;
    sf::Vector2f m_mazeOrigin;
    sf::RectangleShape m_textureHighlightRect;
    sf::RectangleShape m_highlightedGridRect;
    sf::Font m_font;
    sf::Text m_gridLocation;
    sf::Vector2i m_highlightedGridIndex;

    // Private Gameplay Member Variables
    std::string m_mazeFileName;
    std::vector<sf::Texture*> m_textures;
    std::vector<std::vector<gridStruct>> m_grid;
    unsigned int m_MAX_GRID_SIZE;
    unsigned int m_squaresToDisplay;
    float m_squareSize;
    int m_selectedTextureIndex;
    float m_textureSize;
};