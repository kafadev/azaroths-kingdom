#include <algorithm>
#include <complex>
#include <iostream>
#include <iterator>
#include <vector>
#include "Tile.hpp"

#define TILE_LOGGING false

/* const map of colors to description for all tiles */
// maybe best to later aggregate this into some config file & possibly create a utils.cpp to house this.
/* Also best to possibly refactor into multiple Tile.cpp specific classes w/ inheritance. */
static std::map<Color, std::string, ColorComparator> ColorToType = {
    {GRAY, "Town"},
    {BROWN, "Mineral-Rich"},
    {YELLOW, "Fertile"},
    {GREEN, "Wildcard"},
    {BLUE, "Ocean"},
    {WHITE, "Tundra"},
    {CYAN, "Capital City"},
    {BLACK, "Non-existant"}
};

Tile::~Tile() {
    // destroy something?
}

Tile::Tile(std::string name, const Color color) {
    this->name = name;
    this->color = color;
};

const std::string& Tile::getName() {
    return name;
}


Color Tile::getColor() {
    return this->color;
}

Coords Tile::getCoords() {
    return this->coords;
}

/* Public Setters */
void Tile::setCoords(Coords newCoords) {
    this->coords = newCoords;
};

void Tile::setColor(Color color) {
    this->color = color;
}

bool Tile::checkColor(Color color) {
    return  (this->color.a == color.a) &&
            (this->color.b == color.b) &&
            (this->color.g == color.g) &&
            (this->color.r == color.r); 
}

std::string Tile::getTileType() {
    return ColorToType[this->color];
}

void Tile::changeToTown() {
    this->color = GRAY;
}
