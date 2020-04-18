#include "game.h"
// default constructor for Game class
// no return
// no parameters
Game::Game()
{
    m_resolution.x = sf::VideoMode::getDesktopMode().width;
    m_resolution.y = sf::VideoMode::getDesktopMode().height;
    m_isDone = false;
    m_window = new sf::RenderWindow(sf::VideoMode(m_resolution.x, m_resolution.y), "Out of the Dark");
    m_screen = Screen("home_screen", m_window);
}


// destructor for game class
// no return
// no parameters
Game::~Game()
{
}


void Game::handleInput()
{
    m_screen.handleInput(); // have input handling level specific
}


void Game::update()
{
    m_screen.update(); // have update be level specific
}


void Game::render()
{
    m_screen.render(); // have render be level specific
}


bool Game::isDone() const
{
    return m_isDone;
}


void Game::loadSettings()
{
    std::fstream file("settings/settings.csv", std::ios::in);
    char comma;
    char* parameterName;
    file >> parameterName >> comma >> m_settings.playMusic;
    file >> parameterName >> comma >> m_settings.playAudio;
    file >> parameterName >> comma >> m_settings.difficulty;
    file >> parameterName >> comma >> m_settings.username;
    file >> parameterName >> comma >> m_settings.frameRate;
    file >> parameterName >> comma >> m_settings.showFps;
    file.close();
}


void Game::updateSettings()
{
    std::fstream file("settings/settings.csv", std::ios::out);
    const char comma = ',';
    char* parameterName;
    file << "PLAY_MUSIC" << comma << m_settings.playMusic;
    file << "PLAY_AUDIO" << comma << m_settings.playAudio;
    file << "DIFFICULTY" << comma << m_settings.difficulty;
    file << "USERNAME" << comma << m_settings.username;
    file << "FRAME_RATE" << comma << m_settings.frameRate;
    file << "SHOW_FPS" << comma << m_settings.showFps;
    file.close();
}