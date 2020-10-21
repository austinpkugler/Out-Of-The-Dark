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
#include <SFML/Graphics.hpp>

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
    enum {Alive, Dead, Won} status = Alive;
    bool burning = false;
    bool poisoned = false;
    float healthPercent = 100;
    unsigned int burnLength = 0;
    unsigned int poisonedLength = 0;
    unsigned int x = 0; // In terms of pixels
    unsigned int y = 0; // In terms of pixels
    sf::Sprite sprite;
    std::unique_ptr<sf::Texture> texturePtr = std::make_unique<sf::Texture>();
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
    bool walkable = false;
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
    Gameplay(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Settings> settings, 
             std::shared_ptr<sf::Music> music, float width, float height, std::string fileName, int saveSlot);
    ~Gameplay();
    Gameplay(const Gameplay&) = delete;            // copy constructor
    Gameplay(Gameplay&&) = delete;                 // move constructor
    Gameplay& operator=(const Gameplay&) = delete; // copy assignment
    Gameplay& operator=(Gameplay&&) = delete;      // move assignment

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
    std::optional<GameObject> blockMouseIsOn() const;                   // Calculates and returns the grid data of the mouse position.
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
    std::unique_ptr<sf::Texture> deathScreenTexture;
    sf::Sprite deathScreenSprite;
    std::unique_ptr<sf::Texture> hardModeTexture;
    sf::Sprite hardModeSprite;
    std::unique_ptr<sf::Texture> pausedScreenTexture;
    sf::Sprite pausedScreenSprite;
    std::unique_ptr<sf::Texture> settingsScreenTexture;
    sf::Sprite winScreenSprite;
    std::unique_ptr<sf::Texture> winScreenTexture;
    sf::Sprite settingsScreenSprite;
    sf::Vector2i upperLeftSquare;
    sf::Vector2i startingBlock;
    sf::Vector2f gridOffset;
    std::vector<std::unique_ptr<sf::Texture>> vectorOfTextures;
    std::shared_ptr<sf::Music> m_music;

    std::vector<std::vector<GameObject>> m_maze;
    std::string fileName;
    unsigned int objectsToDisplay;
    float squareSize;
    float TEXTURE_SIZE;
    unsigned int GRID_SIZE;
    Player player;
};