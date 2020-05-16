# Out of the Dark
## Description
Find your way out. Any means necessary. Play the default levels found in /levels, or create your own with the built in maze editor. 

## How to run the game
1. Download Mingw and SFML (go find an online tutorial, its a complicated process)

2. Download Python 3.6 or greater and add it to PATH if you have not already

3. Download this repository

4. Navigate to the SFML\bin directory, copy all .dll or .lib files, and paste them in the root directory of this repository

5. Open a terminal in the root directory, and type in `g++ -std=c++11 main.cpp game.cpp gameplay.cpp mazeBuilder.cpp menu.cpp -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio` NOTE: replace the C:/sfml file paths with the file path where it is installed on your system
6. Type `.\main.exe` into the console, and enjoy the game

We realize this is troublesome for people who are just looking to play the game, and are working on a simple installer to help with this process.

## Creators
Hayden Carroll

- Preferred Contact Info: haydencarroll77@gmail.com

Austin Kugler

- Preferred Contact Info: austinpkugler@gmail.com

