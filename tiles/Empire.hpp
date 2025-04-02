#include <vector>
#include <Coords.hpp>

struct Yields {
    int food;               /* Used to calculate growth */
    int population;         /* Used to calculate growth */
    int minerals;   
};

class Empire {

    public: 
        Empire();
        ~Empire();

        Yields* calculateYields();
        bool isEmpireGrowing();
        double calculateInfluence(Yields* yields);
        void updateEmpire(Yields* yields);

        void expand();
        void shrink();


    private: 
        int food;               /* Used to calculate growth */
        int population;         /* Used to calculate growth */
        int number_of_towns;    /* Used for influence multiplier */
        int minerals;           /* Used for military strength */

        Coords capitalCoords;
        std::vector<Coords> towns;
};