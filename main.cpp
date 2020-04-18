// Command: g++ -std=c++11 main.cpp game.cpp snake.cpp world.cpp  -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system
#include "game.h"
#include "screen.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Out of the Dark");
    Game game(&window);

    // sf::Texture texture;
    // if (!texture.loadFromFile("assets/home_screen_background.png"))
    // {
    //     std::exit(1);
    // }
    // sf::Sprite sprite(texture);

    while(!game.isDone())
    {
        game.clearScreen();
        game.handleInput();
        game.update();
        game.render();
    }

    return 0;
}