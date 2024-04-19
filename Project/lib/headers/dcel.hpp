// header file for DCEL data structure (Doubly connected edge list) (lib/DCEL.cpp)
#include <vector>
#include "DCELEdge.hpp"
#include "DCELFace.hpp"
#include "Vertex.hpp"

#ifndef DCEL_HPP
#define DCEL_HPP

class DCEL{
    private:
        std::vector<Vertex> vertices;
        std::vector<DCELEdge> edges;
        std::vector<DCELFace> faces;
    public:
        DCEL();
        void addVertex(Vertex v);
        void addEdge(DCELEdge e);
        void addFace(DCELFace f);
        std::vector<Vertex> getVertices();
        std::vector<DCELEdge> getEdges();
        std::vector<DCELFace> getFaces();
};

#endif