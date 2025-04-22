
#define NUM_CONNECTED 6

#include <algorithm>  // For std::fill_n
#include <complex>    // If needed, depending on your use case
#include <iostream>   // If needed for debugging or printing
#include <iterator>   // If needed, for iterators
#include <vector>     // If needed, for STL containers (e.g., std::vector)
#include "Colors.hpp"
#include <map>
#include "utils.hpp"
#include "Coords.hpp"

class Tile {
    public:
        // Destructor
        ~Tile();

        // Default Constructor: Initializes connectedTiles to nullptr
        Tile(std::string name, const Color color);

        /* Public Tile Information */
        Color getColor();
        Coords getCoords();
        std::string getTileType();
        const std::string& getName();

        /* Public Setters */
        void setCoords(Coords newCoords);
        void setColor(Color color);
        bool checkColor(Color color);

        /* Prototype Functions (to be deprecated later) */
        void changeToTown();
        void regressTileColor();
        bool isOceanTile();
        bool isVoidTile();
        bool isValid();
        

    private:
        std::string name;
        Coords coords;
        Color color;
        Color originalColor; 

        Yields resources; /* To be custom-set in each inheriting class */
};