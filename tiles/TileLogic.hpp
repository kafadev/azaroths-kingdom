#include "TileManager.hpp"

/* Empire Info Holder :: Possibly Refactor into a class system later */
struct Empire {

};

class TileLogic {
    public:
        ~TileLogic();

        TileLogic(TileManager* tm);

    private:
        TileManager* tm; 
        std::vector<Empire> empires; /* List of Empires, current naive implementation */

};
