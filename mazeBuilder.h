#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "section.h"
#include "settings.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <algorithm>


struct gridStruct
{
    unsigned int x;
    unsigned int y;
    unsigned int texture;
    sf::Sprite sprite;
};


class MazeBuilder: public Section
{
public:
    MazeBuilder(sf::RenderWindow* window, Settings* settings, float width, float height);
    ~MazeBuilder();                        // destructor

    virtual void load();              // overrides Screen::load()
    virtual void update();            // overrides Screen::update()
    virtual void handleInput();       // overrides Screen::handleInput()
    virtual void render();            // overrides Screen::render()
private:

    void toPreview();
    void toMain();

    void generateFile();             // private member function to generate .maze file
    void loadFromFile();             // private member function to load maze into maze creator

    void populateGrid();             // populates m_grid

    bool isMouseOnBlock(const gridStruct& block) const; // checks if mouse is on a given block
    void highlightGridSquare();
    void drawGrid();


    std::string m_mazeFileName;     // name for file open
    
    sf::Texture* m_backgroundTexture; // ptr to background texture
    sf::Sprite m_backgroundSprite;    // sprite of background

    std::vector<sf::Texture*> m_textures; // vector of textures (walls, floors, etc)
    std::vector<std::vector<gridStruct>> m_grid;
    sf::Vector2i m_highlightedGridIndex;
    unsigned int m_MAX_GRID_SIZE;      // number of squares each way (width and height)
    unsigned int m_squaresToDisplay;   // number of squares to display on screen
    float m_squareSize;

    sf::Vector2i m_upperLeftSquare; // square at origin (in coords of 2d grid vector)
    sf::Vector2f m_mazeOrigin;        // upper left pixel of grid

    int m_selectedTextureIndex;         // current texture selected
    float m_textureSize;

    sf::RectangleShape m_textureHighlightRect; // rect for highlighting textures
    sf::RectangleShape m_highlightedGridRect;

    sf::Font m_font;
    sf::Text m_gridLocation;
};