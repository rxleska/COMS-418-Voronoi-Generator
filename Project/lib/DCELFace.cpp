// DCEL Face Class Definition
#include "headers/DCELFace.hpp"

DCELFace::DCELFace(){
    edge = nullptr;
}

DCELFace::DCELFace(DCELEdge* edge){
    this->edge = edge;
}

void DCELFace::setEdge(DCELEdge* edge){
    this->edge = edge;
}

DCELEdge* DCELFace::getEdge(){
    return edge;
}