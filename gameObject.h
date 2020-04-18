#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

class gameObject
{
public:
    bool isCollision(const gameObject& gameObject); // boolean function to check collision of two game objects
    gameObject* isCollision(const std::vector<gameObject>& gameVect); // returns a pointer to a game object if there is a collision, nullptr otherwise


    sf::Sprite sprite;

};