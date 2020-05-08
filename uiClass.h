#include "screen.h"
#include <string>
class uiClass : Screen
{
public:
    
private:
    void playSoundBuffer();

     // TITLE SCREEN RESOURCES
    void titleScreenUpdate();       // private member function to update thngs on title screen
    void titleScreenLoad();         // private member function to load the title screen assets
    void titleScreenInput();        // private member function to do title screen input if screen is title screen
    sf::Texture m_titleScreenBg;

    // PLAY SCREEN RESOURCES
    std::vector<std::string> getAllSaves();
    void playScreenUpdate();
    void playScreenLoad();
    void playScreenInput();
    sf::Texture m_playScreenBg;

    // SETTINGS SCREEN RESOURCES
    void settingsScreenUpdate();
    void settingsScreenLoad();
    void settingsScreenInput();
    sf::Texture m_settingsScreenBg;
};