#include "Empire.hpp"
#include <vector> 
#

Empire::~Empire() {

}

// Default constructor -- populate default values
Empire::Empire() {
    this->food = 50;
    this->population = 5;        
    this->number_of_towns = 0;
    this->minerals = 50;   
};

Empire::Empire(int food, int population,  int number_of_towns, int minerals) {
    this->food = food;
    this->population = population;        
    this->number_of_towns = number_of_towns;
    this->minerals = minerals;   
}

Yields* Empire::calculateYields() {
    // std::vector -> Add tiles in 2x radius
    
    // calculate 
}

bool Empire::isEmpireGrowing() {
    
}

double Empire::calculateInfluence(Yields* yields) {
    if yields
}

/* Function to take a Yields item and calculate influence, etc. */
void Empire::updateEmpire(Yields* yields) {


    struct Yields *yields = calculateYields();

    double inf = calculateInfluence(yields);


    if (isEmpireGrowing()) {
        expand();
    } else {
        shrink();
    }


    delete(yields);
}

/* If Empire is growing, then run expand on it */
void Empire::expand() {

}

/* If Empire is not growing, shrink it */
void Empire::shrink() {

}