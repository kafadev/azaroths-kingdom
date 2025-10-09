#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include "../tiles/TileManager.hpp"


/* Generated Pair Hash*/
struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combines the hashes
    }
};

class HexGrid {
public:
    HexGrid(TileManager* tm);
    void render(SDL_Renderer* renderer);
    void drawHexagon(SDL_Renderer* renderer, Coords tileCoords, const Color color);
    void setColor(SDL_Renderer* renderer, const Color color);
    void updateDisplayedTileColor(SDL_Renderer* renderer, Tile* tile);
    void rippleEffect(SDL_Renderer* renderer, Tile* unusedTile);
    Tile* getTileFromCoords(Coords coords);

private:

    /* Helper functions to calculate hexagon */
    float getHeight(float cRadius);
    float getApothem(float cRadius);
    bool isEven(int x);

    /* Variables to help organize the grid */
    float cRadius;
    Coords startingCoords; 

    /* Actual Tile Data */
    TileManager* tm;
    
};