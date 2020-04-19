// Command: g++ -std=c++11 main.cpp game.cpp snake.cpp world.cpp  -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system
#include "game.h"
#include "screen.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Out of the Dark");
    sf::Clock clock;
    float lastTime = 0;
    float currentTime = 0;
    float fps = 0;
    Game game(&window);


    while(!game.isDone())
    {
        game.clearScreen();
        game.handleInput();
        game.update();
        game.render();
        window.display();

        // calculate and store fps
        currentTime = clock.restart().asSeconds();
        fps = 1 / (currentTime - lastTime);
        lastTime = currentTime;
        game.setFps(fps);
    }

    return 0;
}