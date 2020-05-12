#pragma once
#include "SFML/Graphics.hpp"
#include "section.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>

struct Player
{
    bool alive = true;
    bool burning = false;
    float healthPercent = 100;
    unsigned int burnLength = 0;
    unsigned int x = 0; // in terms of pixels
    unsigned int y = 0; // in terms of pixels
    sf::Sprite sprite;
    sf::Texture* texturePtr = new sf::Texture();
    sf::Vector2f velocity = sf::Vector2f(0, 0);

};

struct GameObject
{
    int arrIndexX = -1;
    int arrIndexY = -1;
    int textureIndex = 4;
    bool walkable = 0;
    sf::Sprite sprite;
};

class Gameplay: public Section
{
public:
    Gameplay(sf::RenderWindow* window, Settings* settings, float width, float height, std::string fileName, int saveSlot);
    ~Gameplay();

    virtual void load();
    virtual void update();
    virtual void handleInput();
    virtual void render();

private:
    void displayHealth();
    void applyDamage();
    void populateGrid();
    void renderGrid();
    void pausedScreenInput();
    void calculatePlayerVelocity();
    bool playerWon();
    void resetLevel();
    const GameObject blockMouseIsOn() const;
    std::vector<GameObject> blocksPlayerIsOn() const;


    sf::Vector2f indexToCoord(unsigned int x, unsigned int y) const;



    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBg;
    sf::RectangleShape m_highlightedGridRect; // square where mouse is highlighted
    sf::RectangleShape m_squareToMoveTo;      // square to move to 

    sf::Texture* deathScreenTexture;
    sf::Sprite deathScreenSprite;
    sf::Texture* hardModeTexture;
    sf::Sprite hardModeSprite;
    sf::Texture* pausedScreenTexture;
    sf::Sprite pausedScreenSprite;

    std::vector<sf::Texture*> vectorOfTextures;
    std::vector<std::vector<GameObject>> m_maze;
    sf::Vector2i upperLeftSquare;
    sf::Vector2i startingBlock;
    unsigned int objectsToDisplay;
    float squareSize;
    float TEXTURE_SIZE;
    unsigned int GRID_SIZE;
    sf::Vector2f gridOffset;

    std::string fileName;

    Player player;
};