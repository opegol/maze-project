# maze-project

## Introduction
The Maze is a pseudo3D game built a 2D map using SDL2  and Raycasting.  Players can move in all four directions using keys up, down, left and right arrow keys
The maps are defined in 2D arrays in text files, which are parsed with 0 representing an open space, and all other integers are drawn as walls with mapped textures.
- [LinkedIn](https://www.linkedin.com/in/ope-olubodun )
- [Landing page](https://qkpage2.co/p/mazeproject )
-[blogpost](https://docs.google.com/document/d/1Qg3FPAOSruBEnTwkBTubax8RCMwk-y9aLtTiTCC9KXk/edit?usp=sharing)
  
Building a maze game using raycasting and SDL2 as a portfolio project. 
Development features include:
- Creating a window with SDL2
- Using raycasting to draw walls on your window
- Making the color of walls different from the color of the - ground/ceil
- Drawing walls facing NORTH and SOUTH in a different color from walls facing EAST and WEST.
- Providing means to rotate the camera during the execution for by using the left,right arrows keyboard presses or mouse movements
- Providing a way to move the camera during execution for example by using w,a,s,d keyboard presses.
- Implementing collisions and maps

- Handling the collisions of the player with the walls. The player must not be able to enter a wall but can slide on the walls instead of being just stopped by it.
- implementing a parser to get the map from a file and define characters for different components (walls, enemies, space etc)
- Drawing the map and including the player’s line of sight in it.

  ![Game screenshot](https://github.com/opegol/maze-project/blob/main/pics/mazeImg.jpg?raw=true)


## Installation

To Compile and Run and the, SDL2 and SDL2_image are required to be installed.
Compile with gcc 4.8.4 with the following flags: gcc -O2 -g -Wall -Werror -Wextra -pedantic -Isrc/headers *.c -lSDL2 -lSDL2_image -lm -o maze `sdl2-config --cflags --libs`

## Usage

Up Arrow Key - Moving forward
Down Arrow Key - Moving backward
Right Arrow Key - Look left
Right Arrow Key - Look right

## Related projects

ALX SE Maze Project 

## Contributing

- Read the source files in src folder and the header files in header folder.
- Clone the repo and make a new branch: $ git checkout https://github.com/opegol/maze-project -b [name_of_new_branch].
- Add a feature, fix a bug, or refactor some code 
- Update README.md as needed.
- Open a Pull Request with a detailed description of changes.

## Licensing
- BSD

## Resources: 
- SDL2 API
- LazyFoo Beginning Game Programming
- LodeV Raycasting Tutorial

# My inspiration
The primary inspiration for the would be ALX. For making it an option for a portfolio project and also providing good resources to start with! Really, it was supposed to be the default for uninspired folks! But going through the concept page and getting acquainted with the underlying technologies of the project,such as raycasting/raytracing and the SDL libraries, I realized it was an opportunity to satisfy my curiousity about the inner mechanisms of game engines, audio visuals, CAD softwares etc since we would be making use of the C language.
With this project, I am able to deepen my understanding of game development principles and practical application of computer graphics algorithms, at close to a fundamental level.


