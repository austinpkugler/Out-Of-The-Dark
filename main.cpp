// Command: g++ -std=c++11 main.cpp game.cpp uiClass.cpp -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include "SFML/Graphics.hpp"
#include "game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Out of the Dark");
    sf::Clock clock;
    Game game(&window);
    sf::Time time;
    int fps = 0;

    while(!game.isDone())
    {
        game.clearScreen();
        game.handleInput();
        game.update();
        game.render();
        window.display();

        // Calculate and store fps
        time = clock.getElapsedTime();
        fps = 1.0f / time.asSeconds();
        game.setFps(fps);
        clock.restart().asSeconds();
    }

    return 0;
}