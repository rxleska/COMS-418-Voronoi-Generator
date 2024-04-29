#ifndef DEDGE_HPP
#define DEDGE_HPP

#include "DVertex.hpp"
#include "DFace.hpp"

//forward declaration
class DVertex;
class DFace;


class  DEdge{
    private:
        DVertex * origin;
        DEdge * twin;
        DEdge * next;
        DEdge * prev;
        DFace * incidentFace;
        int id;
        static int idCounter;
    public:
        //Constructors
        DEdge();
        DEdge(DVertex * origin, DEdge * twin, DEdge * next, DEdge * prev, DFace * incidentFace);
        DEdge(DVertex * origin, DEdge * twin, DEdge * next, DEdge * prev);
        //Getters
        DVertex * getOrigin();
        DEdge * getTwin();
        DEdge * getNext();
        DEdge * getPrev();
        DFace * getIncidentFace();
        int getId();
        //Setters
        void setOrigin(DVertex * origin);
        void setTwin(DEdge * twin);
        void setNext(DEdge * next);
        void setPrev(DEdge * prev);
        void setIncidentFace(DFace * incidentFace);
        void setId(int id);
};

#endif