Scotland Yard Game
==================

This is a C++ and OpenGL implementation of the famous board game.

Dependencies
------------

To compile the game you have to use Visual Studio Express 2013 or later. 
You also have to have the following libraries installed: opengl32.lib, glu32.lib, glaux.lib.
You might have to change to path of some OpenGL headers.

Controls
--------

Esc -- Open/Close the games menu  
C/V -- Zoom in and out  
O/P -- Adjust scaling  
Note that the game runs in debug mode by default where you can freely go
around with all characters. To switch between them use the corresponding
buttons in the menu. You can also switch to multiplayer mode to play the
game with one of your friends.

Short documentation
-------------------

### main.cpp
This file contains the skeleton of the game as it handles switching between
gamemodes opening the menu and stopping/starting various cycles.

### WINAPI.cpp
This file contains all Windows related code. It handles input, messages
and a few OpenGL commands.

### openGL.h
This file contians all OpenGL code. It also includes my really basic rendering engine.
You might have to change the path to some OpenGL headers here.

### input.cpp
This file is responsible for keeping track of mouse movements and
recognizing keystrokes.

### render.cpp
This file interacts with my rendering engine. Most of it are just polygon coordinates.