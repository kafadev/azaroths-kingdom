#include "GameLogic.hpp"

#define YIELD_RADIUS 2 

/* Short helper functions */
/* Short helper function to create a dummy empire */

Empire* create_empire(int f, int p, int m, Coords coords) {

    Empire* e = new Empire();

    return e;
}

TileManager* GameLogic::tm = nullptr;
std::vector<Empire*> GameLogic::empires;

GameLogic::~GameLogic() {

}

GameLogic::GameLogic(TileManager* tm) {
    this->tm = tm;
    Empire* e = create_empire(100, 100, 100, Coords{0, 0});
    this->empires.push_back(e);
}

/* Allocates a Yields struct from a coordinate */
Yields* GameLogic::calculateYields(Coords coords) {
    std::unordered_set<Tile*> tiles = tm->getConnectedTilesInRadius(tm->getTile(coords), YIELD_RADIUS);
    Yields* y = new Yields;

    for (auto t : tiles) {
        std::string tileType = t->getTileType();
        
        if (tileType == "Non-Fertile") {
            

        } else if (tileType == "Mineral-Rich") {
            
        } else if (tileType == "Fertile") {
            

        } else if (tileType == "Wildcard") {
           

        } else if (tileType == "Ocean") {
            
        } else if (tileType == "Tundra") {
            
        } else {
            
        }
    }

}










