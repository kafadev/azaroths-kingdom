
#define NUM_CONNECTED 6

#include <algorithm>  // For std::fill_n
#include <complex>    // If needed, depending on your use case
#include <iostream>   // If needed for debugging or printing
#include <iterator>   // If needed, for iterators
#include <vector>     // If needed, for STL containers (e.g., std::vector)
#include "Colors.hpp"
#include <map>
#include "Coords.hpp"

/* Generated Comparator for Color Struct */
struct ColorComparator {
    bool operator()(const Color& lhs, const Color& rhs) const {
        return std::tie(lhs.r, lhs.g, lhs.b, lhs.a) < std::tie(rhs.r, rhs.g, rhs.b, rhs.a);
    }
};

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

    private:
        std::string name;
        Coords coords;
        Color color;

    protected:
        static std::map<Color, std::string, ColorComparator> TypeToColor;
};