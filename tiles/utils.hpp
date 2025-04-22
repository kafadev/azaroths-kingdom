/* This file should contain conditional values and other predefined information;
    NOTE: later on, Colors.hpp and Coords.hpp might be aggregated here if this file doesn't get too large */

// ensure compiler only runs this file once. 
#pragma once

// Logging-related conditionals / values
#define LOGGING true
#define TILE_LOGGING false

/* Phase 1 testing */
#define EMPIRE_TEST true
#define STARTING_CAPITAL_POPULATION 5
#define DISABLE_NEGATIVE_FOOD true

// relating to main() file
#define MUSIC false
#define ITERATIONS 1000

/* Universally used yields struct to collect information from tiles */
struct Yields {
    float food;               /* Used to calculate growth */
    float population;         /* Used to calculate growth */
    float minerals;   
};