// HexGrid class exists to manage all the UI rendering aspects of the Tile Grid
/* Used as an interface with SDL2 */
#include "HexGrid.hpp"
#include <cmath>
#include <vector>
#include <unordered_set>

#include <chrono>
#include <thread>

HexGrid::HexGrid(TileManager* tm) {
    cRadius = 50;
    startingCoords.x = 100;
    startingCoords.y = 100;

    tm->generateRandomGrid();
    tileManager = tm;
}   

/* Calculate the height of the entire hexagon (diameter from one side to another) */
float HexGrid::getHeight(float cRadius) {
    return getApothem(cRadius) * 2;
}

/* Distance between the radius and a vertex */
float HexGrid::getApothem(float cRadius) {
    return cRadius * cos(30);
}

/* Check if value is even */
bool HexGrid::isEven(int x) {
    return (x % 2 == 0);
}

void HexGrid::setColor(SDL_Renderer* renderer, const Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// (Generated Code)
// Draw a single flat-topped hexagon centered at (x, y).
// For a flat-topped hexagon, we use angles of 0°, 60°, 120°, …, 300°.
// void HexGrid::drawHexagon(SDL_Renderer* renderer, Coords tileCoords, const Color color) {
//     const int NUM_POINTS = 6;
//     SDL_Point points[NUM_POINTS + 1]; // +1 to close the polygon

//     // For a flat-topped hexagon, the vertices are computed at:
//     // angle = 0, 60, 120, 180, 240, and 300 degrees (converted to radians)
//     for (int i = 0; i < NUM_POINTS; ++i) {
//         float angle = M_PI / 3.0f * i; // M_PI/3 = 60° in radians
//         points[i].x = static_cast<int>(tileCoords.x + cRadius * cos(angle));
//         points[i].y = static_cast<int>(tileCoords.y + cRadius * sin(angle));
//     }
//     // Close the hexagon by repeating the first point.
//     points[NUM_POINTS] = points[0];

//     // Set the drawing color (e.g., white) and draw the hexagon outline.
//     setColor(renderer, color);
//     SDL_RenderDrawLines(renderer, points, NUM_POINTS + 1);
// }

/* Generated function based on previous drawHexagon that fills in the hexagons with respective color */
void HexGrid::drawHexagon(SDL_Renderer* renderer, Coords tileCoords, const Color color) {
    const int NUM_POINTS = 6;
    SDL_Vertex vertices[NUM_POINTS];

    // Compute the hexagon vertices
    for (int i = 0; i < NUM_POINTS; ++i) {
        float angle = M_PI / 3.0f * i;
        vertices[i].position.x = tileCoords.x + cRadius * cos(angle);
        vertices[i].position.y = tileCoords.y + cRadius * sin(angle);
        vertices[i].color = { (unsigned char) color.r, (unsigned char) color.g, (unsigned char) color.b, (unsigned char) color.a }; // SDL_Color format
    }

    // Set the drawing color (if needed)
    setColor(renderer, color);

    // Draw the filled hexagon using triangles (fan method)
    for (int i = 1; i < NUM_POINTS - 1; ++i) {
        SDL_Vertex triangle[3] = {
            vertices[0],
            vertices[i],
            vertices[i + 1]
        };
        SDL_RenderGeometry(renderer, nullptr, triangle, 3, nullptr, 0);
    }

    // Draw the hexagon outline (optional)
    SDL_Point points[NUM_POINTS + 1];
    for (int i = 0; i < NUM_POINTS; ++i) {
        points[i].x = static_cast<int>(vertices[i].position.x);
        points[i].y = static_cast<int>(vertices[i].position.y);
    }
    points[NUM_POINTS] = points[0];

    SDL_RenderDrawLines(renderer, points, NUM_POINTS + 1);
}


// Render a grid of flat-topped hexagons/
void HexGrid::render(SDL_Renderer* renderer) {

    // Clear all items that existed before 
    setColor(renderer, BLACK); // create black background
    SDL_RenderClear(renderer);

    const int cols = COLS; // number of columns in the grid
    const int rows = ROWS; // number of rows in the grid
    const float x_modifier = 1.75 * (cRadius / 100);
    const float y_modifier = 2 - (1 - cRadius / 100);
    float x_off = 1;

    for (int c = 0; c < cols; c++) {
        
        // base case modifier
        if (c > 0) {
            x_off = x_off + x_modifier;
        }
        
        // generate the up shifted column
        if (isEven(c)) { 
            for (int r = 0; r < rows; r++) {

                // Get Tile information
                Color tileColor = tileManager->getTile(r, c)->getColor();
                Coords tileCoords {
                    static_cast<int>(startingCoords.x * x_off), 
                     static_cast<int>(startingCoords.y + (r * cRadius * 2))
                };

                drawHexagon(renderer, tileCoords, tileColor);
            }
        } else { // generate the down shifted column
            for (int r = 0; r < rows; r++) {

                // Get Tile information
                Color tileColor = tileManager->getTile(r, c)->getColor();

                Coords tileCoords {
                     static_cast<int>(startingCoords.x  * x_off), 
                     static_cast<int>((startingCoords.y * y_modifier) + (r * cRadius * 2))
                };

                drawHexagon(renderer, tileCoords, tileColor);
            }
        }
        
    }

    // display updated changes
    SDL_RenderPresent(renderer);
}

/* Function not in usage */
void HexGrid::updateDisplayedTileColor(SDL_Renderer* renderer, Tile* tile) {
    drawHexagon(renderer, tile->getCoords(), tile->getColor());
}

/* Generated Pair Hash*/
struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combines the hashes
    }
};

void HexGrid::rippleEffect(SDL_Renderer* renderer, Tile* unusedTile) {

    std::unordered_set<std::pair<int, int>, pair_hash> old_items = {std::make_pair(0, 0)};
    std::unordered_set<std::pair<int, int>, pair_hash> new_items = {};

    const int ITERATIONS = 200;

    for (int i = 0; i < ITERATIONS; i++) {
        // get all new items
        for (auto item : old_items) {
            new_items.insert(std::make_pair(item.first, (item.second + 1) % COLS));
            new_items.insert(std::make_pair((item.first + 1) % ROWS, item.second));
        }

        // set old items color to white
        for (auto item : old_items) {
            Tile* tile = tileManager->getTile(item.first, item.second);
            tile->setColor(WHITE);
        }

        //render(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // set new items color to red
        for (auto item : old_items) {
            Tile* tile = tileManager->getTile(item.first, item.second);
            tile->setColor(RED);
        }

        //render(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        old_items.clear();
        std::swap(old_items, new_items);
    }



    /* Unused Code : Loops forever through one column highlighting each item in red or blue */
    // loop absolutely forever
    // while (true) {


    //     Tile* tile = tileManager->getTile(r, 0);

    //     if (tile->checkColor(RED)) {
    //         tile->setColor(BLUE);
    //     } else {
    //         tile->setColor(RED);
    //     }
    //     render(renderer);

    //     std::this_thread::sleep_for(std::chrono::seconds(1));

    //     r = (r + 1) % ROWS;

    // }
}