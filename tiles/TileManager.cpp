#include "TileManager.hpp"
#include <algorithm>  // For std::remove_if
#include <iostream>
#include <cassert> 
#include <vector> 
#include <functional>
#include <cstdlib>


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
void push_back_non_null(Tile* foundTile, std::set<Tile*>* tiles) {
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
std::set<Tile*> TileManager::getConnectedTiles(Tile* tile) {

    // do some algorithm to determine using reverse or normal
    bool use_reverse = true; // Hard coded true for now

    std::set<Tile*> connectedTiles;
    int tileRow = 0;
    int tileCol = 0; 

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

/* Assumes an existing array has been constructed, tries to generate random tiles for each item. */
void TileManager::generateRandomGrid() {

    srand ( time(NULL) );

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {

           float x = rand() % 100;

            if (x >= 75) {
                allTiles[r][c] = new Tile("Yellow Tile", WHITE);
            }
            else if (x >= 25) {
                allTiles[r][c] = new Tile("Green Tile", BROWN);
            }
            else {
                allTiles[r][c] = new Tile("White Tile", GRAY);
            }
            
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
