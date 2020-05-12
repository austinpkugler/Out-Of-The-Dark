#pragma once

#include <string>

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
