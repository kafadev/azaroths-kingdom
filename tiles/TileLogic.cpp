#include "TileLogic.hpp"

TileLogic::~TileLogic() {

}

TileLogic::TileLogic(TileManager* tm) {
    this->tm = tm;
    create_empire(100, 100, 100, Coords{0, 0}, &this->empires);
}


/* Short helper functions */
/* Short helper function to create a dummy empire */

void create_empire(int f, int p, int m, Coords coords, std::vector<Empire> *empires) {
    Empire e = {
        f, 
        p,
        0, 
        m,
        coords
    };

    empires->push_back(e);
}







