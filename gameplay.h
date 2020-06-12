#pragma once

// Included C++11 Libraries
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>

// Included Graphics Library Dependencies
#include "SFML/Graphics.hpp"

// Included Local Dependencies
#include "section.h"

/**
 * Struct Name: Player
 * Brief: Stores all player data
 * Description:
 *  Contains all variables related to the state of the player. This includes
 *  the player's position, health, damage status, and velocity.
 */
struct Player
{
    std::string status = "alive";
    bool burning = false;
    bool poisoned = false;
    float healthPercent = 100;
    unsigned int burnLength = 0;
    unsigned int poisonedLength = 0;
    unsigned int x = 0; // In terms of pixels
    unsigned int y = 0; // In terms of pixels
    sf::Sprite sprite;
    sf::Texture* texturePtr = new sf::Texture();
    sf::Vector2f velocity = sf::Vector2f(0, 0);
};

/**
 * Struct Name: GameObject
 * Brief: Stores all data for a single tile.
 * Description:
 *  Contains the index of the tile in the tile array, the type of tile, and
 *  the sprite texture of the tile.
 */
struct GameObject
{
    int arrIndexX = -1;
    int arrIndexY = -1;
    int textureIndex = 4;
    bool walkable = 0;
    sf::Sprite sprite;
};

/**
 * Class Name: Gameplay
 * Brief: Manages Gameplay processes
 * Description:
 *  The Gameplay class contains all general functions required for the game to
 *  actually be played. This includes allowing the player to move their
 *  character, displaying the game, and all other processes for game
 *  playthrough.
 */
class Gameplay: public Section
{
public:
    // Constructor and Destructor
    Gameplay(sf::RenderWindow* window, Settings* settings, sf::Music* music, float width, float height, std::string fileName, int saveSlot);
    ~Gameplay();

    // Public Member Functions for General Gameplay Processes
    virtual void load();            // Manages the loading of all Gameplay assets.
    virtual void update();          // Updates all gameplay variables based on events that occur.
    virtual void handleInput();     // Manages Gameplay input during game playthrough.
    virtual void render();          // Displays all Gameplay assets to the screen.

private:
    // Private Member Functions for General Gameplay Processes
    void displayHealth();           // Graphically displays the player's health bar.
    void calculateCollision();      // Calculates player related collision and applies damage if applicable
    void populateGrid();            // Creates a 2d vector of GameObjects for the maze from a given file
    void renderGrid();              // Renders the maze, including a layer of blocks the user cannot see around the screen
    bool playerWon();               // Returns a boolean indicating whether the player has won.
    void resetLevel();              // Resets the level to its original form.
    const GameObject blockMouseIsOn() const;                            // Calculates and returns the grid data of the mouse position.
    sf::Vector2f indexToCoord(unsigned int x, unsigned int y) const;    // Converts indices of the grid array to an sf::Vector2f.
    std::vector<GameObject> blocksPlayerIsOn() const;                   // Calculates collision and returns a vector of squares the player is currently on.
    void pausedScreenInput();           // Deals with input for the ingame settings (when Escape is pressed).
    void settingsScreenInput();         // Deals with input if the current screen is settings_screen.
    void renderSettingsScreen();        // Renders in game settings screen.
    void calculatePlayerVelocity();     // Calculates the player velocity based on the distance to the selected square (m_squareToMoveTo).
    void updateSettingsStruct();        // Loads the current settings to settings.csv.
    void rotatePlayerToMouse();

    // Private Member Variables
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBg;
    sf::RectangleShape m_highlightedGridRect;
    sf::RectangleShape m_squareToMoveTo;
    sf::Texture* deathScreenTexture;
    sf::Sprite deathScreenSprite;
    sf::Texture* hardModeTexture;
    sf::Sprite hardModeSprite;
    sf::Texture* pausedScreenTexture;
    sf::Sprite pausedScreenSprite;
    sf::Texture* settingsScreenTexture;
    sf::Sprite winScreenSprite;
    sf::Texture* winScreenTexture;
    sf::Sprite settingsScreenSprite;
    sf::Vector2i upperLeftSquare;
    sf::Vector2i startingBlock;
    sf::Vector2f gridOffset;
    std::vector<sf::Texture*> vectorOfTextures;
    sf::Music* m_music;

    std::vector<std::vector<GameObject>> m_maze;
    std::string fileName;
    unsigned int objectsToDisplay;
    float squareSize;
    float TEXTURE_SIZE;
    unsigned int GRID_SIZE;
    Player player;
};