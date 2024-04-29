
#include "headers/DelaunayDCEL.hpp"
#include "../CONST.hpp"

DelaunayDCEL::DelaunayDCEL(){
    this->vertices = std::vector<DVertex *>();
    this->edges = std::vector<DEdge *>();
    this->faces = std::vector<DFace *>();
}

DelaunayDCEL::DelaunayDCEL(std::vector<DVertex *> vertices, std::vector<DEdge *> edges, std::vector<DFace *> faces){
    this->vertices = vertices;
    this->edges = edges;
    this->faces = faces;
}

std::vector<DVertex *> DelaunayDCEL::getVertices(){
    return this->vertices;
}

std::vector<DEdge *> DelaunayDCEL::getEdges(){
    return this->edges;
}

std::vector<DFace *> DelaunayDCEL::getFaces(){
    return this->faces;
}

void DelaunayDCEL::setVertices(std::vector<DVertex *> vertices){
    this->vertices = vertices;
}

void DelaunayDCEL::setEdges(std::vector<DEdge *> edges){
    this->edges = edges;
}

void DelaunayDCEL::setFaces(std::vector<DFace *> faces){
    this->faces = faces;
}

void DelaunayDCEL::generateTriangulation(){
    //TODO implement
}