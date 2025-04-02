#include "TileManager.hpp"

/* Empire Info Holder :: Possibly Refactor into a class system later */
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

        TileLogic(TileManager* tm);

    private:
        TileManager* tm; 
        std::vector<Empire> empires; /* List of Empires, current naive implementation */

};
