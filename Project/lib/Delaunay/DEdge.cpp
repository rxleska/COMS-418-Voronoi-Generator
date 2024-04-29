
#include "headers/DEdge.hpp"

DEdge::DEdge(){
    this->origin = nullptr;
    this->twin = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
    this->incidentFace = nullptr;
    this->id = idCounter++;
}

DEdge::DEdge(DVertex * origin, DEdge * twin, DEdge * next, DEdge * prev, DFace * incidentFace){
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = incidentFace;
    this->id = idCounter++;
}

DEdge::DEdge(DVertex * origin, DEdge * twin, DEdge * next, DEdge * prev){
    this->origin = origin;
    this->twin = twin;
    this->next = next;
    this->prev = prev;
    this->incidentFace = nullptr;
    this->id = idCounter++;
}

DVertex * DEdge::getOrigin(){
    return this->origin;
}

DEdge * DEdge::getTwin(){
    return this->twin;
}

DEdge * DEdge::getNext(){
    return this->next;
}

DEdge * DEdge::getPrev(){
    return this->prev;
}

DFace * DEdge::getIncidentFace(){
    return this->incidentFace;
}

int DEdge::getId(){
    return this->id;
}


void DEdge::setOrigin(DVertex * origin){
    this->origin = origin;
}

void DEdge::setTwin(DEdge * twin){
    this->twin = twin;
}

void DEdge::setNext(DEdge * next){
    this->next = next;
}

void DEdge::setPrev(DEdge * prev){
    this->prev = prev;
}

void DEdge::setIncidentFace(DFace * incidentFace){
    this->incidentFace = incidentFace;
}

void DEdge::setId(int id){
    this->id = id;
}