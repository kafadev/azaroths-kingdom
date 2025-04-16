#include "TileManager.hpp"
#include <algorithm>  
#include <iostream>
#include <cassert> 
#include <vector> 
#include <functional>
#include <cstdlib>
#include <unordered_set>

// allocate a 2d array of tiles
TileManager::TileManager() {
    // Resize the outer vector to have `rows` elements
    allTiles.resize(ROWS);

    // Resize each inner vector to have `cols` elements and initialize to nullptr
    for (size_t i = 0; i < ROWS; ++i) {
        allTiles[i].resize(COLS, nullptr);
    }
}

// delete the allocated 2d array
TileManager::~TileManager() {

    // delete each individual tile
    for (size_t i = 0; i < allTiles.size(); i++) {
        for (size_t j = 0; j < allTiles[i].size(); j++) {
            delete allTiles[i][j];      // Deallocate each Tile* if dynamically allocated
            allTiles[i][j] = nullptr;   // Avoid dangling pointers
        }
    }
    allTiles.clear(); // Clear the vector
}
 
// Remove Tile item at location (r, c) [not implemented]
// requires that the tile exists
bool TileManager::removeTile(int r, int c) {

    assert(allTiles[r][c]); 
    //allTiles[r][c] = VOID TILE

    return false;
}

Tile* TileManager::getTileByName(const std::string& tileName) const {\

    // dig for it
    for(int r = 0; r < allTiles.size(); r++) {
        for (int c = 0; c < allTiles[r].size(); c++) {
            if (allTiles[r][c]->getName() == tileName) {
                return allTiles[r][c];
            }
        }
    }

    return nullptr;         // Return nullptr if the tile is not found
}

// Tile*** TileManager::getAllTiles() {
//     return allTiles;
// }

bool row_in_range(int x) {
    if ((x >= 0) && (x < ROWS)) {
        return true;
    }

    return false;
}

bool col_in_range(int x) {
    if ((x >= 0) && (x < COLS)) {
        return true;
    }

    return false;
}

/* Helper functions to simplify */
Tile* TileManager::getTopItem(int r, int c) {

    int newRow = r - 1;

    // error checking if we're out of bounds
    if (!row_in_range(newRow)) {
        return nullptr;
    }

    return allTiles[newRow][c];
}

Tile* TileManager::getBottomItem(int r, int c) {

    int newRow = r + 1;

    // error checking if we're out of bounds
    if (!row_in_range(newRow)) {
        return nullptr;
    }
    
    return allTiles[newRow][c];

}

Tile* TileManager::getRightItem(int r, int c) {
    int newCol = c + 1;

    // error checking if we're out of bounds
    if (!col_in_range(newCol)) {
        return nullptr;
    }

    return allTiles[r][newCol];
}

Tile* TileManager::getLeftItem(int r, int c) {
    int newCol = c - 1;

    // error checking if we're out of bounds
    if (!col_in_range(newCol)) {
        return nullptr;
    }

    return allTiles[r][newCol];

}

Tile* TileManager::getTopRightItem(int r, int c) {

    int newRow = r - 1;
    int newCol = c + 1;

    if (col_in_range(newCol) && row_in_range(newRow)) {
        return allTiles[newRow][newCol];
    }

    return nullptr;
}

Tile* TileManager::getTopLeftItem(int r, int c) {
    int newRow = r - 1;
    int newCol = c - 1;

    if (col_in_range(newCol) && row_in_range(newRow)) {
        return allTiles[newRow][newCol];
    }

    return nullptr;
}

Tile* TileManager::getBottomLeftItem(int r, int c) {
    int newRow = r + 1;
    int newCol = c - 1;

    if (col_in_range(newCol) && row_in_range(newRow)) {
        return allTiles[newRow][newCol];
    }

    return nullptr;
}

Tile* TileManager::getBottomRightItem(int r, int c) {
    int newRow = r + 1;
    int newCol = c + 1;

    if (col_in_range(newCol) && row_in_range(newRow)) {
        return allTiles[newRow][newCol];
    }

    return nullptr;
}

// helper function to push back
void push_back_non_null(Tile* foundTile, std::unordered_set<Tile*>* tiles) {
    if (foundTile) {
        tiles->insert(foundTile);
    }
}

/*  Purpose: Return all the tiles connected to the given tile
    use 'gold general' pattern to determine which tiles are closest

                x * x               * * *
    NORMAL:     * o *    REVERSE:   * o *
                * * *               x * x
    
    where * refers to a tile that is in usage
*/
std::unordered_set<Tile*> TileManager::getConnectedTiles(Tile* tile) {

    std::unordered_set<Tile*> connectedTiles;
    int tileRow = tile->getCoords().x;
    int tileCol = tile->getCoords().y; 

    bool use_reverse = (tileCol % 2 == 0);

    #if TILE_LOGGING
    SDL_Log("Getting Coords for tile at (%d, %d)", tileRow, tileCol);
    #endif

    // use the reverse pattern
    if (use_reverse) {
        push_back_non_null(getTopItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getBottomItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getTopRightItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getTopLeftItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getLeftItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getRightItem(tileRow, tileCol), &connectedTiles);
    } else {    // use the standard pattern
        push_back_non_null(getTopItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getBottomItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getBottomRightItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getBottomLeftItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getLeftItem(tileRow, tileCol), &connectedTiles);
        push_back_non_null(getRightItem(tileRow, tileCol), &connectedTiles);
    }

    return connectedTiles;
}

/* Extension fo getConnectedTiles but in a radius r */
/* Includes the current given tile as well. */
std::unordered_set<Tile*> TileManager::getConnectedTilesInRadius(Tile* tile, int radius) {

    std::unordered_set<Tile*> visitedTiles = {}; 
    std::unordered_set<Tile*> nextTiles = getConnectedTiles(tile);
    std::unordered_set<Tile*> tmpTiles;

    for (int r = 0; r < radius; r++) {
        for (auto* t : nextTiles) {
            
            #if TILE_LOGGING
            SDL_Log("Acessing Tile (%d, %d)", t->getCoords().x, t->getCoords().y);
            #endif

            if (visitedTiles.find(t) == visitedTiles.end()) {

                // set tile t to be visited
                #if TILE_LOGGING
                SDL_Log("Tile has not been visited, adding to visited set");
                #endif

                if (t != tile) {visitedTiles.insert(t);}

                // run getConnectedTiles() on each tile t
                #if TILE_LOGGING
                SDL_Log("Investigating what this tile is connected to");
                #endif

                for (auto nt: getConnectedTiles(t)) {
                    tmpTiles.insert(nt);
                }
            }
        }


        #if TILE_LOGGING
        SDL_Log("TmpTiles has %ld len", tmpTiles.size());
        #endif

        nextTiles.clear();
        std::swap(nextTiles, tmpTiles);
        
    }

    return visitedTiles;
    
}

/* Assumes an existing array has been constructed, tries to generate random tiles for each item. */
void TileManager::generateRandomGrid() {

    srand ( time(NULL) );

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

           int x = (int) (rand() % 8);
           Color color;

            switch (x) {
                case 0:
                    color = RED;
                    break;
                case 1:
                    color = GREEN;
                    break;
                case 2:
                    color = BLUE;
                    break;
                case 3:
                    color = WHITE;
                    break;
                case 4:
                    color = BLACK;
                    break;
                case 5:
                    color = YELLOW;
                    break;
                case 6:
                    color = BROWN;
                    break;
                default:
                    color = GRAY;
                    break;
            }
            
            allTiles[r][c] = new Tile("Test Tile", color);
            allTiles[r][c]->setCoords(Coords{r, c});
            
        }
    }
}

Tile* TileManager::getTile(int r, int c) {

    assert(r >= 0);
    assert(r < ROWS);
    assert(c >= 0);
    assert(c < COLS);

    return allTiles[r][c];
}

Tile* TileManager::getTile(Coords coords) {

    return getTile(coords.x, coords.y);
}

void TileManager::colorNearbyTiles(Tile* tile) {

    std::unordered_set<Tile*>  tiles = getConnectedTilesInRadius(tile, 4);

    for (auto t : tiles) {
        t->setColor(RED);
    }

}
