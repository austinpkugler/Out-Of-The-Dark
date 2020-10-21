// Included Graphics Library Dependencies
#include <SFML/Graphics.hpp>
#include <memory>
#include "game.h"
#include <iostream>


/**
 * @brief Creates the game and contains the game loop.
 * @details The main function setups the initial state of the game and then
 * continuously calls the required functions to continue to accurately display
 * the game, until the game loop has ended. The entire game and all of the main
 * function's dependencies can be compiled by entering:
 * g++ -std=c++14 main.cpp game.cpp menu.cpp mazeBuilder.cpp gameplay.cpp -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
 * @throw SFML exceptions may be thrown during fatal errors.
 * @param None
 * @return None
 */
int main()
{
    std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "Out of the Dark");
    Game game(window);
    

    while(!game.isDone())
    {
        game.clearScreen();
        game.handleInput();
        game.update();
        game.render();
        window->display();
    }

    return 0;
}