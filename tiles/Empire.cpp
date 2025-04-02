#include "Empire.hpp"
#include <vector> 
#

Empire::~Empire() {

}

Empire::Empire() {

}

Yields* Empire::calculateYields() {
    // std::vector -> Add tiles in 2x radius
    
    // calculate 
}

bool Empire::isEmpireGrowing() {
    
}

double Empire::calculateInfluence(Yields* yields) {

}

/* Function to take a Yields item and calculate influence, etc. */
void Empire::updateEmpire(Yields* yields) {


    struct Yields *yields = calculateYields();

    double inf = calculateInfluence(&yields);


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