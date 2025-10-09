#include "Empire.hpp"
#include "SDL2/SDL.h"

// SDL imports 
#include <vector> 

// Empty constructor -- do nothing
Empire::~Empire() 
{

}

// Default constructor -- populate default values
Empire::Empire() 
{
    this->food = 50;
    this->population = 5;    
    this->capitalPopulation = STARTING_CAPITAL_POPULATION;    
    this->number_of_towns = 0;
    this->minerals = 50;   
    this->influence = 0;
    this->capitalCoords = Coords{3,3};
    this->name = "Test Empire";
};

/*
    Constructor 
    Takes in starting parameters for an Empire.  

    @param food : 
    @param population :
    @param number_of_towns :
    @param minerals :
    @param name
*/
Empire::Empire(float food, float population,  
               int number_of_towns, float minerals, 
               std::string name) 
{
    this->food = food;
    this->population = population;        
    this->number_of_towns = number_of_towns;
    this->minerals = minerals;   
    this->name = name;
    this->capitalPopulation = STARTING_CAPITAL_POPULATION;   
}

/*
    Checks if the empire is in a growing state based on food and population

    @returns true/false based on growing/shrinking of empire

*/
bool Empire::IsEmpireGrowing() 
{
    return this->food > this->population;
}

/*  Calculates influence value at a timestep
    Influence is determined primarily from the population values

    @param yields : struct with yields per timestep
*/
float Empire::CalculateInfluence(Yields* yields) 
{
    return yields->population + 0.75 * (yields->minerals);
}

 
/* Calculates Military Strength of an Empire at a timestep 
   Military strength is determined by minerals (metal for medieval weaponry) and food

   @param Yields* yields
*/
float Empire::CalculateMilitaryStrength(Yields* yields) 
{
    return yields->minerals + 0.5 * yields->food;
}

/* Recalculate Empire values based on yields at a timestep
   Recalculates resources : food, influence, population, minerals

   @param Yields* yields
*/
void Empire::UpdateEmpire(Yields* yields) 
{

    this->influence += CalculateInfluence(yields);
    this->food += (yields->food - this->population);
    this->population = yields->population + this->capitalPopulation;
    this->minerals += yields->minerals;

    // temporary debugging methods
    #if DISABLE_NEGATIVE_FOOD
    if (this->food < 0) {this->food = 0;}
    #endif
 
    #if LOGGING
    PrintEmpire();
    #endif

}

/* ------ Getters ----- */


/* Return the coordinates of capital city of empire

   @return Coords struct 
*/
Coords Empire::GetCapitalCoords() 
{
    return this->capitalCoords;
};

/* Debugging function to print all empire values
   Warning: Relies on SDL_Log() to print
*/
void Empire::PrintEmpire() 
{
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
            GetCapitalCoords().x, 
            GetCapitalCoords().y);
}