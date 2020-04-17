// Command: g++ -std=c++11 main.cpp game.cpp snake.cpp world.cpp  -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system
#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Out of the Dark");
    Game game(window);

    while(!game.isDone())
    {
        game.handleInput();
        game.update();
        game.render();
    }

    return 0;
}