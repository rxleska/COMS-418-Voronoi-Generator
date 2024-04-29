
#include "DFace.hpp"

//initialize static variable
int Face::idCounter = 1;

Face::Face(){
    this->id = idCounter++;
    this->outerComponent = nullptr;
}

Face::Face(int id, Edge * outerComponent){
    this->id = id;
    this->outerComponent = outerComponent;
}

int Face::getId(){
    return this->id;
}

DEdge * Face::getOuterComponent(){
    return this->outerComponent;
}

void Face::setId(int id){
    this->id = id;
}

void Face::setOuterComponent(DEdge * outerComponent){
    this->outerComponent = outerComponent;
}