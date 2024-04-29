
#include "headers/Edge.hpp"


//init static variable
int Edge::idCounter = 1;

// constructors
Edge::Edge() {
    this->origin = nullptr;
    this->twin = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->incidentFace = nullptr;
    this->isBorder = false;
    this->id = idCounter++;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev, Face* incidentFace) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->isBorder = false;
    this->id = idCounter++;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = nullptr;
    this->isBorder = false;
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

bool Edge::getIsBorder() {
    return this->isBorder;
}

double Edge::getAngle() {
    Vertex *v1 = this->origin;
    Vertex *v2 = this->twin->getOrigin();
    //calculate the angle between the two vectors
    double angle = atan2(v2->getY() - v1->getY(), v2->getX() - v1->getX());
    if(angle < 0){
        angle += 2 * PI;
    }  
    return angle; 
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

void Edge::setIsBorder(bool isBorder) {
    this->isBorder = isBorder;
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
    std::cout << this->getEdgeName() << " " << 
    (this->origin == nullptr ? "nil" : this->origin->getVertexName()) << " " << 
    (this->twin == nullptr ? "nil" : this->twin->getEdgeName()) << " " << 
    (this->next == nullptr ? "nil" : this->next->getEdgeName()) << " " << 
    (this->prev == nullptr ? "nil" : this->prev->getEdgeName()) << " " << 
    (this->incidentFace == nullptr ? "nil" : this->incidentFace->getFaceName()) << std::endl;    
}

bool Edge::getIsClosed() {
    Edge *edge = this;
    do {
        edge = edge->getNext();
        if (edge == this) {
            return true;
        }
        if(edge == this->getTwin()){
            return false;
        }
    } while (edge != nullptr);
    return false;
}

std::string Edge::getEdgeName() {
    return "e" + std::to_string(this->getOrigin()->getId()) + "," +  std::to_string(this->getTwin()->getOrigin()->getId());
}