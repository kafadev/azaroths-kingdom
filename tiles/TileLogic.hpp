#include "TileManager.hpp"
#include "Empire.hpp"

class TileLogic {
    public:
        ~TileLogic();

        TileLogic(TileManager* tm);

    private:
        TileManager* tm; 
        std::vector<Empire*> empires; /* List of Empires, current naive implementation */

};
