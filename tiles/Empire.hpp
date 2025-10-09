#pragma once
#include <vector>
#include <string>
#include "Coords.hpp"
#include "utils.hpp"

class Empire {
    public: 

        // ----- Constructors -----
                    Empire();
                    Empire(float food, 
                        float population,  
                        int number_of_towns, 
                        float minerals, 
                        std::string name);
                    ~Empire();

        // ------ General Functions ------
        bool        IsEmpireGrowing();
        float       CalculateInfluence(Yields* yields);
        void        UpdateEmpire(Yields* yields);
        float       CalculateMilitaryStrength(Yields* yields);

        /* ----- Getters ------ */
        Coords      GetCapitalCoords();
        void        PrintEmpire();

    private: 
        float               food;               /* Used to calculate growth */
        float               population;         /* Used to calculate growth */
        int                 number_of_towns;    /* Used for influence multiplier */
        float               minerals;           /* Used for military strength */
        float               influence;
        float               capitalPopulation;
        std::string         name;

        Coords              capitalCoords;
        std::vector<Coords> towns;
};