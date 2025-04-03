#pragma once

#include "TileManager.hpp"
#include "Empire.hpp"

class TileLogic {
    public:
        ~TileLogic();

        TileLogic(TileManager* tm);

    private:
        static TileManager* tm; 
        static std::vector<Empire*> empires; /* List of Empires, current naive implementation */

};
