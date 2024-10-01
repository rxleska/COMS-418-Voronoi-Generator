
#ifndef PSEUDOEDGE_HPP
#define PSEUDOEDGE_HPP
#include "Vertex.hpp"


// //forward declaration
class Vertex;

class PseudoEdge {
    public:
        Vertex* start;
        Vertex* end;
        bool isBoundary;
        Vertex *arc1;
        Vertex *arc2;
        PseudoEdge(Vertex* start, Vertex* end, bool ib);
        PseudoEdge(Vertex* start, Vertex* end, bool ib, Vertex *arc1, Vertex *arc2);
        PseudoEdge(Vertex* start, Vertex* end);
        PseudoEdge();
        double getAngle();
        //copy constructor
        PseudoEdge(const PseudoEdge &pe);
        //copy assignment
        PseudoEdge& operator=(const PseudoEdge &pe);
};

#endif // PSEUDOEDGE_HPP