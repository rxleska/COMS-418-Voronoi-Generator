
#include "headers/Edge.hpp"


//init static variable
int Edge::idCounter = 1;

Edge::Edge(int id) {
    this->origin = nullptr;
    this->twin = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->incidentFace = nullptr;
    this->isBorder = false;
    this->id = id;
    this->site = nullptr;
    this->converted = false;
}

// constructors
Edge::Edge() {
    this->origin = nullptr;
    this->twin = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->incidentFace = nullptr;
    this->isBorder = false;
    this->id = idCounter++;
    this->site = nullptr;
    this->converted = false;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev, Face* incidentFace) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->isBorder = false;
    this->id = idCounter++;
    this->site = nullptr;
    this->converted = false;
}

Edge::Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev) {
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = nullptr;
    this->isBorder = false;
    this->id = idCounter++;
    this->site = nullptr;
    this->converted = false;
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

bool Edge::getConverted() {
    return this->converted;
}

Vertex * Edge::getSite() {
    return this->site;
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

void Edge::setConverted(bool converted) {
    this->converted = converted;
}

void Edge::setSite(Vertex * site) {
    this->site = site;
}

void Edge::setSite(Vertex * site, Vertex * site2) {
    //check which site is to the right of the edge
    //turn the edge into a vector 
    double x = this->twin->getOrigin()->getX() - this->origin->getX();
    double y = this->twin->getOrigin()->getY() - this->origin->getY();

    //turn the sites into vectors with the edge as the origin
    double x1 = site->getX() - this->origin->getX();
    double y1 = site->getY() - this->origin->getY();
    double x2 = site2->getX() - this->origin->getX();
    double y2 = site2->getY() - this->origin->getY();

    //calculate the cross product of the edge and the two sites
    double cross1 = x * y1 - y * x1;
    double cross2 = x * y2 - y * x2;

    if (cross1 > cross2) {
        // std::cout << "choosing site 2: (" << site2->getX() << ", " << site2->getY() << ")" << std::endl; 
        this->site = site2;
    } else if (cross1 < cross2) {
        // std::cout << "choosing site 1: (" << site->getX() << ", " << site->getY() << ")" << std::endl; 
        this->site = site;
    } else {
        //if the sites are colinear choose the one with the smallest y value
        this->site = site->getY() < site2->getY() ? site : site2;
    }

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
    std::cout << "e" << this->getEdgeName() << " " << 
    (this->origin == nullptr ? "nil" : this->origin->getVertexName()) << " " << 
    (this->twin == nullptr ? "nil" : this->twin->getEdgeName()) << " " << 
    (this->next == nullptr ? "nil" : this->next->getEdgeName()) << " " << 
    (this->prev == nullptr ? "nil" : this->prev->getEdgeName()) << " " << 
    (this->incidentFace == nullptr ? "nil" : this->incidentFace->getFaceName()) << " " 
    << std::endl;    
}

std::string Edge::edgeToString(bool isVoronoi) {
    std::string edgeString = "";
    if(isVoronoi){
        edgeString += "e" + this->getEdgeName() + " " + 
        (this->origin == nullptr ? "nil" : this->origin->getVertexName(isVoronoi)) + " " + 
        (this->twin == nullptr ? "nil" : this->twin->getEdgeName(isVoronoi)) + " " + 
        (this->next == nullptr ? "nil" : this->next->getEdgeName(isVoronoi)) + " " + 
        (this->prev == nullptr ? "nil" : this->prev->getEdgeName(isVoronoi)) + " " + 
        (this->incidentFace == nullptr ? "nil" : this->incidentFace->getFaceName(isVoronoi));
    }
    else{
        edgeString += "d" + this->getEdgeName() + " " + 
        (this->origin == nullptr ? "nil" : this->origin->getVertexName(isVoronoi)) + " " + 
        (this->twin == nullptr ? "nil" : this->twin->getEdgeName(isVoronoi)) + " " + 
        (this->next == nullptr ? "nil" : this->next->getEdgeName(isVoronoi)) + " " + 
        (this->prev == nullptr ? "nil" : this->prev->getEdgeName(isVoronoi)) + " " + 
        (this->incidentFace == nullptr ? "nil" : this->incidentFace->getFaceName(isVoronoi));
    }
    return edgeString;
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
    return std::to_string(this->getOrigin()->getId()) + "," +  std::to_string(this->getTwin()->getOrigin()->getId());
}

std::string Edge::getEdgeName(bool isVoronoi) {
    if(isVoronoi){
        return "e" + std::to_string(this->getOrigin()->getId()) + "," +  std::to_string(this->getTwin()->getOrigin()->getId());
    }
    return "d" + std::to_string(this->getOrigin()->getId()) + "," +  std::to_string(this->getTwin()->getOrigin()->getId());
}