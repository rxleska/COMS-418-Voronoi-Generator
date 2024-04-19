// DCEL edge class de
#include "headers/DCELEdge.hpp"

//initialize the id counter
int DCELEdge::idCounter = 0;

DCELEdge::DCELEdge(){
    origin = nullptr;
    twin = nullptr;
    next = nullptr;
    prev = nullptr;
    incidentFace = nullptr;
    this->id = idCounter;
    idCounter++;
}

DCELEdge::DCELEdge(Vertex* origin){
    this->origin = origin;
    twin = nullptr;
    next = nullptr;
    prev = nullptr;
    incidentFace = nullptr;
    this->id = idCounter;
    idCounter++;
} 

DCELEdge::DCELEdge(Vertex* origin, DCELEdge* twin, DCELEdge* next, DCELEdge* prev, DCELFace* incidentFace){
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->id = -1;
}

DCELEdge::DCELEdge(Vertex* origin, int id){
    this->origin = origin;
    twin = nullptr;
    next = nullptr;
    prev = nullptr;
    incidentFace = nullptr;
    this->id = id;
} 

DCELEdge::DCELEdge(Vertex* origin, DCELEdge* twin, DCELEdge* next, DCELEdge* prev, DCELFace* incidentFace, int id){
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->id = id;
}

void DCELEdge::setOrigin(Vertex* origin){
    this->origin = origin;
}

void DCELEdge::setTwin(DCELEdge* twin){
    this->twin = twin;
}

void DCELEdge::setNext(DCELEdge* next){
    this->next = next;
}

void DCELEdge::setPrev(DCELEdge* prev){
    this->prev = prev;
}

void DCELEdge::setIncidentFace(DCELFace* incidentFace){
    this->incidentFace = incidentFace;
}

Vertex* DCELEdge::getOrigin(){
    return origin;
}

Vertex* DCELEdge::getDestination(){
    return twin->getOrigin();
}

DCELEdge* DCELEdge::getTwin(){
    return twin;
}

DCELEdge* DCELEdge::getNext(){
    return next;
}

DCELEdge* DCELEdge::getPrev(){
    return prev;
}

DCELFace* DCELEdge::getIncidentFace(){
    return incidentFace;
}

