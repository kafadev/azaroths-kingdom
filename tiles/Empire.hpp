#include <vector>
#include <Coords.hpp>

struct Yields {


};

class Empire {

    public: 
        Empire();
        ~Empire();

        Yields calculateYields();
        bool isEmpireGrowing();
        double calculateInfluence();
        void updateEmpire();




    private: 
        int food;               /* Used to calculate growth */
        int population;         /* Used to calculate growth */
        int number_of_towns;    /* Used for influence multiplier */
        int minerals;           /* Used for military strength */

        Coords capitalCoords;



};