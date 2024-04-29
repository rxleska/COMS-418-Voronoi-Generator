
#ifndef DDCEL_HPP
#define DDCEL_HPP

#include "DVertex.hpp"
#include "DEdge.hpp"
#include "DFace.hpp"
#include <vector>
#include "../../DCEL/headers/DCEL.hpp"

//forward declaration
class DVertex;
class DEdge;
class DFace;

class DelaunayDCEL {
    private:
        std::vector<DVertex *> vertices;
        std::vector<DEdge *> edges;
        std::vector<DFace *> faces;
    public:
        DelaunayDCEL();
        DelaunayDCEL(std::vector<DVertex *> vertices, std::vector<DEdge *> edges, std::vector<DFace *> faces);
        std::vector<DVertex *> getVertices();
        std::vector<DEdge *> getEdges();
        std::vector<DFace *> getFaces();
        void setVertices(std::vector<DVertex *> vertices);
        void setEdges(std::vector<DEdge *> edges);
        void setFaces(std::vector<DFace *> faces);
        void generateTriangulation();
};

#endif