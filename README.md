# Out of the Dark
## Description
Find your way out. Any means necessary. Play the default levels found in /levels, or create your own with the built in maze editor. More information can be found in the Official Player Guide found in the root directory. 

## Before you run the game
Please note that there is a Python 3.6+ dependency. This game requires that the tkinter library for Python is installed (it is installed by default), and that the location of Python is added as an environment variable. This is needed because the C++ files invocate a Python script by doing a system call similar to  `system("python3 path/to/pyFile.py arg1 arg2")`

SFML 2.5+ is also needed. 

## Running the game
### Creating the build directory
Create a build directory in the root directory.
This will be where you will build the game.
### Running cmake
Navigate to the build directory you just made, and type `cmake ..` into the
terminal. This will create the proper build files necessary to actually compile the game.

### For Linux/Mac Users:
There should be a Makefile created in the build directory once you complete the previous step.
You can compile the game by typing `make`
in that directory. You should see a new file called `OutOfTheDark`. This is the game! Run it by typing
`./OutOfTheDark` in the terminal.

### For Windows Users:
???

## Suggestions?
Feel free to contact one of the creators listed below, or submit a pull request or issue on Github.

## Creators
Hayden Carroll

Austin Kugler
