#pragma once

#define ROWS 7
#define COLS 14

#include <SDL2/SDL.h>

#include <vector>
#include <string>
#include <set>
#include <map> 
#include <unordered_set>
#include "Tile.hpp"
#include "utils.hpp"
#include <mutex>

class TileManager {
    private:
        std::vector<std::vector<Tile*>> allTiles; 
        
    public:
        // Destructor to clean up dynamically allocated tiles
        ~TileManager();
        TileManager();

        // Method to remove a tile from the manager
        bool removeTile(int r, int c);

        // Getters
        Tile *getTile(int r, int c);
        Tile *getTile(Coords coords);
        Tile *getTileByName(const std::string& tileName) const;
        Tile *getTopItem(int r, int c);
        Tile *getBottomItem(int r, int c);
        Tile *getRightItem(int r, int c);
        Tile *getLeftItem(int r, int c);
        Tile *getTopRightItem(int r, int c);
        Tile *getTopLeftItem(int r, int c);
        Tile *getBottomLeftItem(int r, int c);
        Tile *getBottomRightItem(int r, int c);
        std::unordered_set<Tile*>  getConnectedTiles(Tile *tile);
        std::unordered_set<Tile*>  getConnectedTilesInRadius(Tile* tile, int radius);
        void generateRandomGrid();

        void colorNearbyTiles(Tile* tile);

};
