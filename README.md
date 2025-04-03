# This is a work-in-progress civilization Clone

## Features (Both planned / implemented) 
- Tiling UI System in SDL2 (currently exists in debug mode with coords)
- Movement of singular character
- Randomized improvments of tiles (started in TileLogic.cpp/hpp)
- algorithmic movement of enemy civilizations (not yet implemented)

## Instructions
- compile the program via 'make' using the makefile. This creates executable called 'game'.
- run game on linux via ./game


## Misc

### Example Map (Randomized, Apr 2025)
![image](https://github.com/user-attachments/assets/540c0799-3ae6-4e06-9d31-45e39ba3aaab)

### Possible rendering issues
- firstly, make sure SDL2 is installed
- SDL2 might have rendering problem depending on Wayland / Xorg usage. See if switching between these helps.
- certain laptops resolutions might render hexagons with a blurry edge (currently investigating) 

### Reach out if you'd like to contribute / help.
- See my profile for more information 
