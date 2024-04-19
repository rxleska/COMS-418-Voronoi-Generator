//header file defining the DCEL face data structure (Doubly connected edge list face) (lib/DCELFace.cpp)



#ifndef DCEL_FACE_HPP
#define DCEL_FACE_HPP

#include "DCELEdge.hpp"

class DCELEdge;

class DCELFace{
    private:
        DCELEdge *edge;
    public:
        DCELFace();
        DCELFace(DCELEdge* edge);
        void setEdge(DCELEdge* edge);
        DCELEdge* getEdge();
};


#endif