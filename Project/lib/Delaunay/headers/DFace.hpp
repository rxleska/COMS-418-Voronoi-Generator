#ifndef DFACE_HPP
#define DFACE_HPP

#include "DEdge.hpp"
#include "DVertex.hpp"

//forward declaration
class DEdge;
class DVertex;

class DFace {
    private:
        int id;
        static int idCounter;
        DEdge * outerComponent;
    public:
        DFace();
        DFace(int id, DEdge * outerComponent);
        int getId();
        DEdge * getOuterComponent();
        void setId(int id);
        void setOuterComponent(DEdge * outerComponent);
};


#endif