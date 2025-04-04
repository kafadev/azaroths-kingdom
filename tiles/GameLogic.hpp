#pragma once
#include "Empire.hpp"
#include "TileManager.hpp"

class GameLogic {
    public:
        ~GameLogic();
        GameLogic(TileManager* tm);

        Yields* calculateYields(Coords coords);

    private:
        static std::vector<Empire*> empires; /* List of Empires, current naive implementation */
        static TileManager* tm; 

};  
