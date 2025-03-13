
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

        /* Public Setters */
        void setCoords(Coords newCoords);
        void setColor(Color color);
        bool checkColor(Color color);


    private:
        // You can add any private members or helper methods here
        std::string name;
        Coords coords;
};