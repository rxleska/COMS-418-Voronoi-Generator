//header file for DCEL edge data structure (Doubly connected edge list edge) (lib/DCELEdge.cpp)
#ifndef DCEL_EDGE_HPP
#define DCEL_EDGE_HPP

#include "Vertex.hpp"

class DCELEdge{
    private: 
        Vertex* origin;
        DCELEdge* twin;
        DCELEdge* next;
        DCELEdge* prev;
        DCELEdge* incidentFace;
    public:
        DCELEdge();
        DCELEdge(Vertex* origin);
        void setOrigin(Vertex* origin);
        void setTwin(DCELEdge* twin);
        void setNext(DCELEdge* next);
        void setPrev(DCELEdge* prev);
        void setIncidentFace(DCELEdge* incidentFace);
        Vertex* getOrigin();
        DCELEdge* getTwin();
        DCELEdge* getNext();
        DCELEdge* getPrev();
        DCELEdge* getIncidentFace();

};

#endif