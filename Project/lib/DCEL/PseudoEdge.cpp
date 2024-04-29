#include "headers/PseudoEdge.hpp"


PseudoEdge::PseudoEdge(Vertex * start, Vertex * end) {
    this->start = start;
    this->end = end;
    this->isBoundary = false;
}

PseudoEdge::PseudoEdge() {
    this->start = new Vertex(0.0,0.0,-1);
    this->end = new Vertex(0.0,0.0,-1);
    this->isBoundary = false;
}

PseudoEdge::PseudoEdge(Vertex * start, Vertex * end, bool ib) {
    this->start = start;
    this->end = end;
    this->isBoundary = ib;
}

double PseudoEdge::getAngle() {
    double angle = atan2(this->end->getY() - this->start->getY(), this->end->getX() - this->start->getX());
    if (angle < 0) {
        angle += 2 * PI;
    }
    return angle;
}