#include "Empire.hpp"
#include <vector> 
#include "SDL2/SDL.h"

Empire::~Empire() {

}

// Default constructor -- populate default values
Empire::Empire() {
    this->food = 50;
    this->population = 5;    
    this->capitalPopulation = STARTING_CAPITAL_POPULATION;    
    this->number_of_towns = 0;
    this->minerals = 50;   
    this->influence = 0;
    this->capitalCoords = Coords{3,3};
    this->name = "Test Empire";
};

Empire::Empire(float food, float population,  int number_of_towns, float minerals, std::string name) {
    this->food = food;
    this->population = population;        
    this->number_of_towns = number_of_towns;
    this->minerals = minerals;   
    this->name = name;
    this->capitalPopulation = STARTING_CAPITAL_POPULATION;   
}

bool Empire::isEmpireGrowing() {
    return this->food > this->population;
}

/* Influence is determined primarily from the population values, but also some yield values */
float Empire::calculateInfluence(Yields* yields) {
    return yields->population + 0.75 * (yields->minerals);
}

float Empire::calculateMilitaryStrength(Yields* yields) {
    return yields->minerals + 0.5 * yields->food;
}

/* Function to take a Yields item and calculate influence, etc. */
void Empire::updateEmpire(Yields* yields) {

    this->influence += calculateInfluence(yields);
    this->food += (yields->food - this->population);
    this->population = yields->population + this->capitalPopulation;
    this->minerals += yields->minerals;

    #if DISABLE_NEGATIVE_FOOD
    if (this->food < 0) {this->food = 0;}
    #endif
 
    #if LOGGING
    printEmpire();
    #endif

}

/* Getters */

Coords Empire::getCapitalCoords() {
    return this->capitalCoords;
};

void Empire::printEmpire() {
    SDL_Log("============\n"
            "Name: %s\n"
            "Food: %f\n"
            "Minerals: %f\n"
            "Influence: %f\n"
            "Population: %f\n"
            "Number of Towns: %d\n"
            "Capital Coords: (%d, %d)\n"
            "============\n",
            this->name.c_str(), 
            this->food, 
            this->minerals, 
            this->influence, 
            this->population, 
            this->number_of_towns, 
            getCapitalCoords().x, 
            getCapitalCoords().y);
}