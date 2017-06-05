# README #

Spaceship can move right and left using A and D, 
shoot with machine gun bullets and laser bullets using P and reload using F;
Changing weapon is 1 for Machine Gun and 2 for Laser;

Unfortunately I had many problems with loading models, which took too much time, so enemies are just simple squares,
Collisions with spaceship and enemy bullets as well as enemies and spaceship bullets implemented.

A friend of mine had some problems with collisions with spaceship and enemies on his laptop so I decided to comment it
Implemented scoring for killing enemies, enemies have life, all nesessary information about spaceship can be seen on screen.
Water and Battlefield moving in a loop to create illusion of flying for the ship.

Implemented shaders for water reflection and moving as well as shaders for Battlefield and by pixel shading.
Two types of weapon with different damage and appearance were implemented: Laser and Machine Gun.
Collisions implemented using AABB collision detection with additional checking for Z coordinate.
SpaceShip would be removed from a scene if his life and armor equal or smaller than zero.
I use SOIL library to load textures.
Creating model of spaceship with help from Bjørn-Richard Pedersen.
I am very sorry for messy code I had not have enough time to fix all the small issues.
Here lies whole files and last compiled version and binaries of game is SpaceShooter.7z
https://www.dropbox.com/sh/tt0iyggdgufijgk/AAC_lTR-ozYOv1b3ALZ8BUEva?dl=0