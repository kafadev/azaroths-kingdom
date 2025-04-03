#include "GameLogic.hpp"

/* Short helper functions */
/* Short helper function to create a dummy empire */

Empire* create_empire(int f, int p, int m, Coords coords) {

    Empire* e = new Empire();

    return e;
}

TileManager* TileLogic::tm = nullptr;
std::vector<Empire*> TileLogic::empires;

TileLogic::~TileLogic() {

}

TileLogic::TileLogic(TileManager* tm) {
    this->tm = tm;
    Empire* e = create_empire(100, 100, 100, Coords{0, 0});
    this->empires.push_back(e);
}










