# Out of the Dark
Find your way out. Any means necessary. Play the default levels found in /levels, or create your own with the built in maze editor. More information can be found in the Official Player Guide found in the root directory or in our youtube video: https://www.youtube.com/watch?v=YLgrfNVxZx4 

<br />

# Requirements
Please note that there is a Python 3.6+ dependency. This game requires that the tkinter library for Python is installed (it is usually installed by default), and that the location of Python is added as an environment variable. This is needed because the C++ files invocate a Python script by doing a system call similar to  `system("python3 path/to/pyFile.py arg1 arg2")`

SFML 2.5+ and a familiarity with using cmake is also required. Note that your SFML installation depends on your C++ compiler.

<br />

# Running the game
### Creating the build directory
Create a build directory in the root directory.
This will be where you will build the game.

### Running cmake
Navigate to the build directory you just made, and type `cmake ..` into the terminal. This will create the platform-dependent build files for your system. Note that additional commands may be required to set up cmake with sfml. This project assumes a familiarity with building projects via cmake.

<br />

# Suggestions?
Feel free to contact one of the creators listed below, or submit a pull request or issue on Github.

<br />

# Creators
Hayden Carroll

Austin Kugler