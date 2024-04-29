#include "headers/PseudoEdge.hpp"


PseudoEdge::PseudoEdge(Vertex * start, Vertex * end) {
    this->start = start;
    this->end = end;
    this->isBoundary = false;
    this->arc1 = nullptr;
    this->arc2 = nullptr;
}

PseudoEdge::PseudoEdge() {
    this->start = new Vertex(0.0,0.0,-1);
    this->end = new Vertex(0.0,0.0,-1);
    this->isBoundary = false;
    this->arc1 = nullptr;
    this->arc2 = nullptr;
}

PseudoEdge::PseudoEdge(Vertex * start, Vertex * end, bool ib) {
    this->start = start;
    this->end = end;
    this->isBoundary = ib;
    this->arc1 = nullptr;
    this->arc2 = nullptr;
}

PseudoEdge::PseudoEdge(Vertex * start, Vertex * end, bool ib, Vertex *arc1, Vertex *arc2) {
    this->start = start;
    this->end = end;
    this->isBoundary = ib;
    this->arc1 = arc1;
    this->arc2 = arc2;
}

double PseudoEdge::getAngle() {
    double angle = atan2(this->end->getY() - this->start->getY(), this->end->getX() - this->start->getX());
    if (angle < 0) {
        angle += 2 * PI;
    }
    return angle;
}

PseudoEdge::PseudoEdge(const PseudoEdge &pe) {
    this->start = pe.start;
    this->end = pe.end;
    this->isBoundary = pe.isBoundary;
    this->arc1 = pe.arc1;
    this->arc2 = pe.arc2;
}

PseudoEdge &PseudoEdge::operator=(const PseudoEdge &pe) {
    this->start = pe.start;
    this->end = pe.end;
    this->isBoundary = pe.isBoundary;
    this->arc1 = pe.arc1;
    this->arc2 = pe.arc2;
    return *this;
}