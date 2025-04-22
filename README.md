# Azaroth's Kingdom

## What is this?
This is a work-in-progress game intended to be a pseudo-civilization 6 clone. 

### Proposed Ruleset
In this game, civilizations compete for minerals, food, and influence. There is one moveable character who can influence what tiles will turn into. He can move once each timestep. Each timestep, neighboring tiles will either improve or decay, creating farms, mines, or towns, or falling into disarray. Once a town is created, it can only shrink via food loss or if the bureaucrat removes it. Each variant of the tile results in different yields to the Empire, which in turn affects resource acquisition, influence, and other factors. 

### Immediate necessities (good beginner issues) 
- Create a class system with Tiles -> Tiles into CapitalCity Tile, Mineral Tile, etc. (HIGH) 
- Create textures for tiles instead of using COLORS (LOW) 
- Write logic to calculate food, minerals, population, etc from tiles surrounding a town / capital 

### Other notes
Winning conditions are a work-in-progress. I want to get a strong working prototype before other resources / complicated game logic is introduced. Trade routes / diplomacy and other factors are interesting to model and will come in the future. 

## Features (Both planned / implemented) 
- Tiling UI System in SDL2 (currently exists in debug mode with coords)
- Movement of singular character (planned)
- Randomized improvments of tiles (started in TileLogic.cpp/hpp)
- algorithmic movement of enemy civilizations (not yet implemented)
- Game logic (in-progress) 

## Instructions
- compile the program via 'make' using the makefile. This creates executable called 'game'.
- run game on linux via ./game


## Misc

### Example Map (Randomized, Apr 2025)
![image](https://github.com/user-attachments/assets/540c0799-3ae6-4e06-9d31-45e39ba3aaab)

### Example Example of Growth & Shrinking (Randomized, Apr 2025)
[Screencast from 2025-04-21 17-24-17.webm](https://github.com/user-attachments/assets/bd1a0069-386f-40b7-b32b-2c7b34baf734)


### Possible rendering issues
- firstly, make sure SDL2 is installed
- SDL2 might have rendering problem depending on Wayland / Xorg usage. See if switching between these helps.
- certain laptops resolutions might render hexagons with a blurry edge (currently investigating) 

### Reach out if you'd like to contribute / help.
- See my profile for more information 
