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
        Empire(float food, float population,  int number_of_towns, float minerals, std::string name);
        ~Empire();

        bool isEmpireGrowing();
        float calculateInfluence(Yields* yields);
        void updateEmpire(Yields* yields);
        float calculateMilitaryStrength(Yields* yields);

        /* Getters */
        Coords getCapitalCoords();
        void printEmpire();

    private: 
        float food;               /* Used to calculate growth */
        float population;         /* Used to calculate growth */
        int number_of_towns;    /* Used for influence multiplier */
        float minerals;           /* Used for military strength */
        float influence;
        std::string name;

        Coords capitalCoords;
        std::vector<Coords> towns;
};