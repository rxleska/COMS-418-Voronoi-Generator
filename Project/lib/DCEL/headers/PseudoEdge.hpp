
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
        PseudoEdge(Vertex* start, Vertex* end, bool ib);
        PseudoEdge(Vertex* start, Vertex* end);
        PseudoEdge();
        double getAngle();
};

#endif // PSEUDOEDGE_HPP