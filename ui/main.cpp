// main.cpp
#include <SDL2/SDL.h>
#include "HexGrid.hpp"
#include <memory>
#include <iostream>
#include <memory>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Hex Grid", 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SCREEN_WIDTH, 
                                        SCREEN_HEIGHT, 
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); /* Additional Flags */

    /* Test that the window actually worked */
    if (!window) {
        SDL_Quit();
        return -1;
    }

    /* Generate renderer */
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    /* Generate HexGrid */
    TileManager tm;
    HexGrid hexGrid(&tm);

    bool running = true;
    SDL_Event event;

    /* render it one time */

    // render hexGrid
    hexGrid.render(renderer);
    
    // update screen with new changes
    SDL_RenderPresent(renderer);

    // run infinitely to check for events
    while (running) {

        // ensure program is running & has not quit. 
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            running = false;
        }

        hexGrid.render(renderer);

        // if (event.type == SDL_KEYUP) {

        //     tm.getTile(0, 0)->setColor(GREEN);
        //     hexGrid.render(renderer);
        // }

        // if (event.type == SDL_KEYDOWN) {
        //     hexGrid.rippleEffect(renderer, tm.getTile(0, 0));
        //     // tm.getTile(0, 0)->setColor(RED);

        // }
    }

    // if program has finished running, gracefully exit.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
