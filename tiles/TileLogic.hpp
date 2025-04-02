/* TileLogic.hpp */

#include "TileManager.hpp"

struct Empire {
    int food;               /* Used to calculate growth */
    int population;         /* Used to calculate growth */
    int number_of_towns;    /* Used for influence multiplier */
    int minerals;           /* Used for military strength */

    Coords capitalCoords;
};

class TileLogic {
    public:
        ~TileLogic();

        TileLogic();

    private:

};
