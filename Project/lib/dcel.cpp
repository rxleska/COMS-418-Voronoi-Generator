// Doubly Connected Edge List (DCEL) implementation
#include "headers/DCEL.hpp"
#include <vector>


DCEL::DCEL(){
    vertices = std::vector<Vertex>();
    edges = std::vector<DCELEdge>();
    faces = std::vector<DCELFace>();
}

void DCEL::addVertex(Vertex v){
    vertices.push_back(v);
}

void DCEL::addEdge(DCELEdge e){
    edges.push_back(e);
}

void DCEL::addFace(DCELFace f){
    faces.push_back(f);
}

std::vector<Vertex> DCEL::getVertices(){
    return vertices;
}

std::vector<DCELEdge> DCEL::getEdges(){
    return edges;
}

std::vector<DCELFace> DCEL::getFaces(){
    return faces;
}
