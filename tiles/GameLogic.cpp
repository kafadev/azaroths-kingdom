#include "GameLogic.hpp"
#include <random>
#include <cassert> 

#define YIELD_RADIUS 2 

/* Short helper functions */
/* Short helper function to create a dummy empire */

static int timestep = 0;

/* Defintions of some static items */
TileManager* GameLogic::tm = nullptr;
static std::vector<Empire*> empires;

/* Main GameLogic Functions */
GameLogic::~GameLogic() {

}

GameLogic::GameLogic(TileManager* tm) {

    assert(tm); // make sure tm is not nullptr

    this->tm = tm;

    /* Move this code later on */
    Empire* e = new Empire();
    empires.push_back(e);
}

/* Allocates a Yields struct from a coordinate */
Yields* GameLogic::calculateYields(std::unordered_set<Tile*> tiles) {
    Yields* y = new Yields;

    for (auto t : tiles) {
        std::string tileType = t->getTileType();
        
        if (tileType == "Non-Fertile") {
            // do nothing
        } else if (tileType == "Mineral-Rich") {
            y->minerals += 1;
            
        } else if (tileType == "Fertile") {
            y->food += 1;

        } else if (tileType == "Wildcard") {
            y->food += 0.5;
            y->minerals += 0.5;

        } else if (tileType == "Ocean") {
            y->food += 1.0;

        } else if (tileType == "Tundra") {
            y->food += 0.25;
            y->minerals += 0.25;
            
        } else {
            // do nothing here
        }
    }

    #ifdef LOGGING
    printYields(y);
    #endif

    return y;
}

void GameLogic::incrementTimestep() {
    timestep += 1;

    #ifdef LOGGING
    SDL_Log("Current Timestep: %d\n", timestep);
    #endif
}

void GameLogic::printYields(Yields* y) {
    SDL_Log("Food: %d, Population: %d, Minerals: %d", y->food, y->population, y->minerals);
}

void GameLogic::calculateEmpireDirection(Empire *e) {

    // get all tiles in a pre-defined radius of the capital (no support for towns yet)
    std::unordered_set<Tile*> tiles = tm->getConnectedTilesInRadius(tm->getTile(e->getCapitalCoords()), YIELD_RADIUS);

    assert(!tiles.empty()); // checker to make sure the getConnectedTiles function actually worked

    // calculate yields from the given tiles 
    Yields* y = calculateYields(tiles);
    
    e->updateEmpire(y); // update all the empire's values

    // change RANDOM tile to be a TOWN
    /* reference: https://www.reddit.com/r/cpp_questions/comments/r6fqsb/deleted_by_user/*/
    /* https://stackoverflow.com/questions/39288595/why-not-just-use-stdrandom-device*/

    /* Note: mt19937 (Mersenne Twister algorithm) is used here as an 
             efficient number generator, std::random_device provides a random number too
             we use a random number as a seed to generate another random number,
             this ensures that each run is different and non-deterministic */
    std::mt19937 gen( std::random_device{}() );
    std::vector<Tile*> sampledTiles;
    int numberOfTiles = 1; // HARDCODED!  
    std::sample( tiles.begin(), tiles.end(), std::back_inserter(sampledTiles), numberOfTiles, gen);

    // change the random tile into a town
    for (auto t : sampledTiles) {
        t->changeToTown();
    }
    
    // increment to the next time step
    incrementTimestep();
}

void GameLogic::calculateAllEmpiresDirection() {

    for (auto e : empires) {

        // make sure empire is VALID
        assert(e);

        // calculate direction of each empire.
        #ifdef LOGGING
        SDL_Log("Before:");
        e->printEmpire();
        #endif
        
        calculateEmpireDirection(e);

        #ifdef LOGGING
        SDL_Log("After:");
        e->printEmpire();
        #endif
    }
}














