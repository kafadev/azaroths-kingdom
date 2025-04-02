
#define NUM_CONNECTED 6

#include <algorithm>  // For std::fill_n
#include <complex>    // If needed, depending on your use case
#include <iostream>   // If needed for debugging or printing
#include <iterator>   // If needed, for iterators
#include <vector>     // If needed, for STL containers (e.g., std::vector)
#include "Colors.hpp"

struct Coords {
    int x;
    int y;
};


class Tile {
    public:
        // Destructor
        ~Tile();

        // Default Constructor: Initializes connectedTiles to nullptr
        Tile(std::string name, const Color color);

        /* Tile Functions */
        const std::string& getName();

        /* UI Information */
        Color color;

        /* Public Tile Information */
        Color getColor();
        Coords getCoords();
        std::string getTileType();
        //std::vector<Tile*> getConnectedTiles();

        /* Public Setters */
        void setCoords(Coords newCoords);
        void setColor(Color color);
        bool checkColor(Color color);

        const std::map<Color, std::string> tileTypeToColor = {
            {GRAY, "Non-Fertile"},
            {BROWN, "Mineral-Rich"},
            {YELLOW, "Fertile"},
            {GREEN, "Wildcard"},
            {BLUE, "Ocean"},
        };


    private:
        std::string name;
        Coords coords;
};