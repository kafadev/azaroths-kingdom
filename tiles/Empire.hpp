#pragma once
#include <vector>
#include <string>
#include "Coords.hpp"
#include "utils.hpp"

struct Yields {
    float food;               /* Used to calculate growth */
    float population;         /* Used to calculate growth */
    float minerals;   
};

class Empire {

    public: 
        Empire();
        Empire(int food, int population,  int number_of_towns, int minerals, std::string name);
        ~Empire();

        bool isEmpireGrowing();
        float calculateInfluence(Yields* yields);
        void updateEmpire(Yields* yields);
        float calculateMilitaryStrength(Yields* yields);

        /* Getters */
        Coords getCapitalCoords();
        void printEmpire();

    private: 
        int food;               /* Used to calculate growth */
        int population;         /* Used to calculate growth */
        int number_of_towns;    /* Used for influence multiplier */
        int minerals;           /* Used for military strength */
        float influence;
        std::string name;

        Coords capitalCoords;
        std::vector<Coords> towns;
};