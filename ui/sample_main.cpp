/* This file exists to test UI components 
// Source: https://en.wikibooks.org/wiki/SDL_(Simple_DirectMedia_Layer)/Basics/Creating_a_window */

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */

/* Sets constants */
#define WIDTH 800
#define HEIGHT 800
#define DELAY 3000

int sample_main() {

    /* Initialises data */
    SDL_Window *window = NULL;
    
    /*
    * Initialises the SDL video subsystem (as well as the events subsystem).
    * Returns 0 on success or a negative error code on failure using SDL_GetError().
    */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    /* Creates a SDL window */
    window = SDL_CreateWindow("SDL Example", /* Title of the SDL window */
                    SDL_WINDOWPOS_UNDEFINED, /* Position x of the window */
                    SDL_WINDOWPOS_UNDEFINED, /* Position y of the window */
                    WIDTH, /* Width of the window in pixels */
                    HEIGHT, /* Height of the window in pixels */
                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); /* Additional flag(s) */

    SDL_SetWindowSize(window, 2000, 2000);

    /* Checks if window has been created; if not, exits program */
    if (window == NULL) {
        fprintf(stderr, "SDL window failed to initialise: %s\n", SDL_GetError());
        return 1;
    }

    /* Pauses all SDL subsystems for a variable amount of milliseconds */
    SDL_Delay(DELAY);

    /* Frees memory */
    SDL_DestroyWindow(window);
    
    /* Shuts down all SDL subsystems */
    SDL_Quit(); 
    
    return 0;
}