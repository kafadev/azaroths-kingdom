#include "Empire.hpp"
#include <vector> 

Empire::~Empire() {

}

// Default constructor -- populate default values
Empire::Empire() {
    this->food = 50;
    this->population = 5;        
    this->number_of_towns = 0;
    this->minerals = 50;   
    this->influence = 0;
};

Empire::Empire(int food, int population,  int number_of_towns, int minerals) {
    this->food = food;
    this->population = population;        
    this->number_of_towns = number_of_towns;
    this->minerals = minerals;   
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
    this->food += yields->food;
    this->population += yields->population;
    this->minerals += minerals;
 
    #ifdef LOGGING
    printEmpire();

    #endif


}

/* Getters */

Coords Empire::getCapitalCoords() {
    return this->capitalCoords;
};

void Empire::printEmpire() {
    printf("""============\n"
            "%s\n",
            "Food: %d\n",
            "Minerals: %d\n",
            "Influence: %f\n",
            "Population: %d\n",
            "Number of Towns: %d\n",
            "Capital Coords: (%d, %d)\n",
            "============\n",
            this->name, 
            this->food, 
            this->minerals, 
            this->influence, 
            this->population, 
            this->number_of_towns, 
            getCapitalCoords().x, 
            getCapitalCoords().y);
}