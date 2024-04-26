
#include "headers/Edge.hpp"


//init static variable
int Edge::idCounter = 0;

// constructors
Edge::Edge() {
    this->origin = nullptr;
    this->twin = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->incidentFace = nullptr;
    this->id = idCounter++;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev, Face* incidentFace) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->id = idCounter++;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = nullptr;
    this->id = idCounter++;
}

// getters
Vertex* Edge::getOrigin() {
    return this->origin;
}

Edge* Edge::getTwin() {
    return this->twin;
}

Edge* Edge::getNext() {
    return this->next;
}

Edge* Edge::getPrev() {
    return this->prev;
}

Face* Edge::getIncidentFace() {
    return this->incidentFace;
}

int Edge::getId() {
    return this->id;
}

// setters

void Edge::setOrigin(Vertex* origin) {
    this->origin = origin;
}

void Edge::setTwin(Edge* twin) {
    this->twin = twin;
}

void Edge::setNext(Edge* next) {
    this->next = next;
}

void Edge::setPrev(Edge* prev) {
    this->prev = prev;
}

void Edge::setIncidentFace(Face* incidentFace) {
    this->incidentFace = incidentFace;
}

// destructor
Edge::~Edge() {
    //nothing to delete all pointers that are used elsewhere
    //delete this->origin;
    //delete this->twin;
    //delete this->next;
    //delete this->prev;
    //delete this->incidentFace;
}

// methods
void Edge::printEdge() {
    std::cout << "Edge id: " << this->id << std::endl;
    std::cout << "Origin: " << this->origin->getX() << " " << this->origin->getY() << std::endl;
    std::cout << "Twin: " << this->twin->getId() << std::endl;
    std::cout << "Next: " << this->next->getId() << std::endl;
    std::cout << "Prev: " << this->prev->getId() << std::endl;
    // std::cout << "Incident Face: " << this->incidentFace->getId() << std::endl;
}