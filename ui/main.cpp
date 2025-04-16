// main.cpp
#include "HexGrid.hpp"
#include <memory>
#include <iostream>
#include <memory>
#include <thread>
#include <SDL2/SDL_mixer.h>
#include "../tiles/utils.hpp"
#include "../tiles/GameLogic.hpp"

#define MUSIC false

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

std::mutex tileManagerLock;

int colorRandomTilesYellow(void* data) {
    //HexGrid* hexGrid, TileManager* tm, SDL_Renderer* renderer 
    //hexGrid->rippleEffect(renderer, tm->getTile(0, 0));
    TileManager* tm = (TileManager*) data;


    std::lock_guard<std::mutex>guard1(tileManagerLock);

    for (int i = 0; i < 5; i++) {
        
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        float r = rand() % ROWS;
        float c = rand() % COLS;

        #ifdef LOGGING
        SDL_Log(tm->getTile(r,c)->getTileType().c_str());
        #endif
    
        tm->getTile(r, c)->setColor(YELLOW);

        #ifdef LOGGING
        SDL_Log(tm->getTile(r,c)->getTileType().c_str());
        #endif 
    }
   

    //successful function
    return 0;
}

int colorNearbyTiles(void* data) {
    TileManager* tm = (TileManager*) data;

    SDL_Log("ColorNearbyTiles begun");
    // std::set<Tile*> tiles = tm->getConnectedTiles(tm->getTile(3,3));

    // for (auto t : tiles) {
    //     std::string s = std::to_string(t->getCoords().x) + " " + std::to_string(t->getCoords().y);
    //     SDL_Log(s.c_str());
    // }
    tm->colorNearbyTiles(tm->getTile(3,3));

    return 0;
}

int playMusic(void* data) {

    // Load the WAV file
    Mix_Chunk* sound = Mix_LoadWAV("/home/deven/Documents/coding/azaroths-kingdom/music/output.wav");
    if (!sound) {
        std::cerr << "Mix_LoadWAV failed: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return -1;
    }

    // Play the sound
    while (true) {
        Mix_PlayChannel(-1, sound, 0);
    }

    return 0;
}

/* Perhaps good to change this in the future to a more appropriate name */
int playGame(void* data) {

    // initialize TileManager
    TileManager* tm = (TileManager*) data;

    // lock some kind of lock (doing operations on tm)

    // Initialize GameLogic
    GameLogic gl = GameLogic(tm);

    // run infinitely
    while (true) {
        gl.calculateAllEmpiresDirection();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    // unlock lock
}

int main(int argc, char* argv[]) {

    /* Set up video-related things */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogCritical(0, "SDL_Init(SDL_INIT_VIDEO) failed");
        SDL_Quit();
        return -1;
    }

    /* Set up audio-related SDL items */
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        SDL_LogCritical(0, "SDL_Init(SDL_INIT_AUDIO) failed");
        SDL_Quit();
        return -1;
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        SDL_LogCritical(0, "Mix_Init failed: %s", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    // Open audio device
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogCritical(0, "Mix_Init failed: %s", Mix_GetError());
        Mix_Quit(); // done here because the last if statement initialized this
        SDL_Quit();
        return -1;
    }

    // Create SDL Window
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
    TileManager* tm = new TileManager();
    HexGrid hexGrid(tm);

    bool running = true;
    SDL_Event event;

    /* render it one time */

    // render hexGrid
    hexGrid.render(renderer);
    
    // update screen with new changes
    SDL_RenderPresent(renderer);

    // enable capturing of mouse
    SDL_CaptureMouse(SDL_TRUE);

    // run loop of music (DISABLED)
    #ifdef MUSIC 
    SDL_CreateThread(playMusic, "music", nullptr);
    #endif

    // run infinitely to check for events
    while (running) {

        // ensure program is running & has not quit. 
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            running = false;
        }
        
        // render & refresh all the time (checking for updates)
        hexGrid.render(renderer);

        /* Run the thread to color nearby tiles*/
        if (event.type == SDL_KEYDOWN) {
            
            #ifdef LOGGING
            SDL_Log("Thread Activated");
            #endif 

            SDL_CreateThread(colorNearbyTiles, "test", &tm); // currently hardcoded to 3
        }
    }

    // if program has finished running, gracefully exit.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


