How to play the game:
- Start the game with X
- Get as high of a score as you can by shooting and destroy asteroids and collecting the gems/debris they drop. 
- Shoot with Z. You need to hold down Z to charge your shot so you can fire a projectile.
- If you get hit by an asteroid you lose

Understanding the code base:

classes.h:
- This script contains all classes used by all other scripts and the project in general. 
- All classes contain update and render functionality which get called from level.cpp and the function exsist 
  in the classes corresponding scripts.
- This script also contains an enum gamestate class for handling game states

main.cpp:
- This script initiliazes the game.
- It also loads and unloads all textures and sounds.
- It contains the main menu and game state logic.
- It handles the background particles.
- It handles screen shake for the main menu.
- It passes update and render functionality onto level.cpp if in game.

level.cpp:
- Level.cpp passes update and render functionality onto all entities.
- All entities except the player are stored in vectors.
- It handles rendering the combo score popups and the total score
- Its also handles all collisions.
- It handles the spawning of the rocks
- It handles reseting all values and passing down reset logic to other scripts
- It handles camera shake by creating an x and y value from two sin waves that other 
  scripts rendering functionality can use to displace sprites 

player.cpp:
- Handles input and controls movement
- Controls shooting logic and holding down to shoot
- Has reset logic for reseting player varibles at the beginning of new games
- Handles rendering player ship and charge effect

bullet.cpp:
- Contains update, rendering, and initializing functionality

rock.cpp:
- Contains update, rendering, and initializing functionality

debris.cpp:
- Contains update, rendering, and initializing functionality

particle.cpp:
- Contains update, rendering, and initializing functionality for general particles
- Contains update, rendering, and initializing functionality for background particles
  which controls a vector of the general particles type
- Contains update, rendering, and initializing functionality for explosion particles
  which controls a vector of the general particles type