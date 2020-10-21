#pragma once

// Included C++11 Libraries
#include <string>

/**
 * Struct Name: Settings
 * Brief: Stores all of the user's settings preferences.
 * Description:
 *  Contains all variables related to user-controllable game settings.
 */
struct Settings
{
    bool playMusic;
    bool playAudio;
    unsigned int difficulty;
    unsigned int frameRate;
    bool showFps;
    std::string saveSlot1;
    std::string saveSlot2;
    std::string saveSlot3;
};
