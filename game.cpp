#include "game.h"
// default constructor for Game class
// no return
// no parameters
Game::Game(sf::RenderWindow& window, char* levelName)
{
    // m_level = home level
    m_isDone = false;
    m_window = window;
    m_level = Level(levelName);
}

// destructor for game class
// no return
// no parameters
Game::~Game()
{
}

void Game::handleInput()
{
    m_level.handleInput(); // have input handling level specific
}

void Game::update()
{
    m_level.update(); // have update be level specific
}

void Game::render()
{
    m_level.render(); // have render be level specific
}