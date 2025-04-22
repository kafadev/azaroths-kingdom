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
    this->tm = tm;
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
    setColor(renderer, BLACK);
    SDL_Point points[NUM_POINTS + 1];
    for (int i = 0; i < NUM_POINTS; ++i) {
        points[i].x = static_cast<int>(vertices[i].position.x);
        points[i].y = static_cast<int>(vertices[i].position.y);
    }
    points[NUM_POINTS] = points[0];

    SDL_RenderDrawLines(renderer, points, NUM_POINTS + 1);
}

/* Generated function to draw a singular digit */
void drawDigit(SDL_Renderer* renderer, char digit, int x, int y) {
    switch (digit) {
        case '0':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x, y, x, y + 6);   // Left
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '1':
            SDL_RenderDrawLine(renderer, x + 2, y, x + 2, y + 6); // Vertical Line
            break;
        case '2':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 3); // Upper right
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x, y + 3, x, y + 6); // Lower left
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '3':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '4':
            SDL_RenderDrawLine(renderer, x, y, x, y + 3);   // Left
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            break;
        case '5':
            SDL_RenderDrawLine(renderer, x + 4, y, x, y);   // Top
            SDL_RenderDrawLine(renderer, x, y, x, y + 3);   // Left
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x + 4, y + 3, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '6':
            SDL_RenderDrawLine(renderer, x + 4, y, x, y);   // Top
            SDL_RenderDrawLine(renderer, x, y, x, y + 6);   // Left
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x + 4, y + 3, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '7':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            break;
        case '8':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x, y, x, y + 6);   // Left
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
        case '9':
            SDL_RenderDrawLine(renderer, x, y, x + 4, y);   // Top
            SDL_RenderDrawLine(renderer, x, y, x, y + 3);   // Left
            SDL_RenderDrawLine(renderer, x, y + 3, x + 4, y + 3); // Middle
            SDL_RenderDrawLine(renderer, x + 4, y, x + 4, y + 6); // Right
            SDL_RenderDrawLine(renderer, x, y + 6, x + 4, y + 6); // Bottom
            break;
    }
}

/* Generated function that utilizes drawDigit to draw digits onto each tile */
void drawNumber(SDL_Renderer* renderer, int num, int x, int y) {
    // Convert number to string
    std::string numStr = std::to_string(num);

    // Loop through each character in the string and draw pixels
    int xOffset = 0;
    for (char digit : numStr) {
        drawDigit(renderer, digit, x + xOffset, y);
        xOffset += 6; // Move right for the next digit
    }
}

/* Generated Render function :: generates hexagonal tile with filled color */
void HexGrid::render(SDL_Renderer* renderer) {
    // Clear the screen
    setColor(renderer, BLACK); // Create black background
    SDL_RenderClear(renderer);

    const int cols = COLS; // Number of columns in the grid
    const int rows = ROWS; // Number of rows in the grid
    const float x_modifier = 1.75 * (cRadius / 100);
    const float y_modifier = 2 - (1 - cRadius / 100);
    float x_off = 1;

    for (int c = 0; c < cols; c++) {
        // Base case modifier
        if (c > 0) {
            x_off = x_off + x_modifier;
        }

        for (int r = 0; r < rows; r++) {
            // Get Tile information
            Color tileColor = tm->getTile(r, c)->getColor();

            // Calculate hexagon center coordinates
            Coords tileCoords;
            if (isEven(c)) {
                tileCoords = {
                    static_cast<int>(startingCoords.x * x_off),
                    static_cast<int>(startingCoords.y + (r * cRadius * 2))
                };
            } else {
                tileCoords = {
                    static_cast<int>(startingCoords.x * x_off),
                    static_cast<int>((startingCoords.y * y_modifier) + (r * cRadius * 2))
                };
            }

            // Draw the hexagon
            drawHexagon(renderer, tileCoords, tileColor);

            // Draw numbers manually as simple pixel-based digits
            setColor(renderer, BLACK);
            drawNumber(renderer, r, tileCoords.x - 8, tileCoords.y); // Draw r at left
            drawNumber(renderer, c, tileCoords.x + 8, tileCoords.y); // Draw c at right
        }
    }

    // Display updated changes
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

void HexGrid::rippleEffect(SDL_Renderer* renderer, Tile* tile) {

    std::unordered_set<std::pair<int, int>, pair_hash> old_items = {std::make_pair(tile->getCoords().x, tile->getCoords().y)};
    std::unordered_set<std::pair<int, int>, pair_hash> new_items = {};

    for (int i = 0; i < ITERATIONS; i++) {
        // get all new items
        for (auto item : old_items) {
            new_items.insert(std::make_pair(item.first, (item.second + 1) % COLS));
            new_items.insert(std::make_pair((item.first + 1) % ROWS, item.second));
        }

        // set old items color to white
        for (auto item : old_items) {
            Tile* tile = tm->getTile(item.first, item.second);
            tile->setColor(WHITE);
        }

        //render(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // set new items color to red
        for (auto item : old_items) {
            Tile* tile = tm->getTile(item.first, item.second);
            tile->setColor(RED);
        }

        //render(renderer);

        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        old_items.clear();
        std::swap(old_items, new_items);
    }
}

Tile* HexGrid::getTileFromCoords(Coords coords) {

    return nullptr;

}