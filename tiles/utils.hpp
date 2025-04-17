/* This file should contain conditional values and other predefined information;
    NOTE: later on, Colors.hpp and Coords.hpp might be aggregated here if this file doesn't get too large */

// ensure compiler only runs this file once. 
#pragma once

// Logging-related conditionals / values
#define LOGGING true
#define TILE_LOGGING false

/* Phase 1 testing */
#define EMPIRE_TEST true


/* Universally used yields struct to collect information from tiles */
struct Yields {
    float food;               /* Used to calculate growth */
    float population;         /* Used to calculate growth */
    float minerals;   
};