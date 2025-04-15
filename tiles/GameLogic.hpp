#pragma once
#include "Empire.hpp"
#include "TileManager.hpp"
#include "utils.hpp"

class GameLogic {
    public:
        ~GameLogic();
        GameLogic(TileManager* tm);

        Yields* calculateYields(std::unordered_set<Tile*> tiles);
        void printYields(Yields* y);
        void incrementTimestep();
        void calculateEmpireDirection(Empire *e);
        void calculateAllEmpiresDirection();


    private:
        //static std::vector<Empire*> empires; /* List of Empires, current naive implementation */
        static TileManager* tm; 

};  
