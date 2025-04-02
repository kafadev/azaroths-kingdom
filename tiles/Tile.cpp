#include <algorithm>
#include <complex>
#include <iostream>
#include <iterator>
#include <vector>
#include "Tile.hpp"

/* const map of colors to description for all tiles */
std::map<Color, std::string, ColorComparator> tileTypeToColor = {
    {GRAY, "Non-Fertile"},
    {BROWN, "Mineral-Rich"},
    {YELLOW, "Fertile"},
    {GREEN, "Wildcard"},
    {BLUE, "Ocean"},
    {WHITE, "Tundra"}
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
    return tileTypeToColor[this->color];
}
