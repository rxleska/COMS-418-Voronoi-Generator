//header file for DCEL edge data structure (Doubly connected edge list edge) (lib/DCELEdge.cpp)


#ifndef DCEL_EDGE_HPP
#define DCEL_EDGE_HPP

#include "Vertex.hpp"
#include "DCELFace.hpp"

class DCELFace;

class DCELEdge{
    private: 
        static int idCounter;
        Vertex* origin;
        DCELEdge* twin;
        DCELEdge* next;
        DCELEdge* prev;
        DCELFace* incidentFace;
        int id;
    public:
        DCELEdge();
        DCELEdge(Vertex* origin);
        DCELEdge(Vertex* origin, DCELEdge* twin, DCELEdge* next, DCELEdge* prev, DCELFace* incidentFace);
        DCELEdge(Vertex* origin, int id);
        DCELEdge(Vertex* origin, DCELEdge* twin, DCELEdge* next, DCELEdge* prev, DCELFace* incidentFace, int id);
        void setOrigin(Vertex* origin);
        void setTwin(DCELEdge* twin);
        void setNext(DCELEdge* next);
        void setPrev(DCELEdge* prev);
        void setIncidentFace(DCELFace* incidentFace);
        Vertex* getOrigin();
        Vertex* getDestination();
        DCELEdge* getTwin();
        DCELEdge* getNext();
        DCELEdge* getPrev();
        DCELFace* getIncidentFace();

};

#endif