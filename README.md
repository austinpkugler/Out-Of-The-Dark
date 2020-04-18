# PA 6
## Description
 Programming Assignment 6 for CS151 at North Idaho College Spring 2020

## Game: Out of the Dark
Description: Find your way out. Any means necessary.

Rating: E for Everyone 

## How to run the game
1. Download Mingw and SFML (go find an online tutorial, its a complicated process)

2. Download this repository

3. Navigate to the SFML\bin directory, copy all .dll or .lib files, and paste them in the root directory of this repository

4. Open a terminal in the root directory, and type in `g++ -std=c++11 main.cpp screen.cpp game.cpp -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system` NOTE: replace the C:/sfml file paths with the file path where it is installed on your system
5. Type `.\main.exe` into the console, and enjoy the game