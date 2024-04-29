#ifndef DCEL_HPP
#define DCEL_HPP

#include "Face.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include "../../CONST.hpp"
#include "PseudoEdge.hpp"

//forward declaration
class Face;
class Edge;
class Vertex;
class PseudoEdge;

#include <vector>
#include <iostream>
#include <string>



class DCEL{
    private: 
        std::vector<Vertex*> vertices;
        Vertex **xSortedVertices; //array of pointers to vertices in the vertices list, used for binary search lookup based on x value (then y value) left to right, bottom to top (for simplicity)
        int xSortedSize;
        std::vector<Edge*> edges;
        std::vector<Face*> faces;
    public:
        DCEL();
        DCEL(int n);
        ~DCEL();
        //Getters
        std::vector<Vertex*> getVertices();
        std::vector<Edge*> getEdges();
        std::vector<Face*> getFaces();
        Vertex** getXSortedVertices();
        int getXSortedSize();

        //Setters //these setters are not used in the project
        void setVertices(std::vector<Vertex*> vertices);
        void setEdges(std::vector<Edge*> edges);
        void setFaces(std::vector<Face*> faces);
        void setXSortedVertices(Vertex** xSortedVertices);
        void setXSortedSize(int xSortedSize);

        //Methods
        bool compareVertices(Vertex v1, Vertex v2);
        void addVertex(Vertex *vertex);
        void addEdge(Edge *edge);
        void addFace(Face *face);
        //Dynamically add an edge to the DCEL
        void addEdge(Vertex origin, Vertex destination);

        //CONSTRUCT DCEL
        void constructDCEL(std::vector<PseudoEdge> pseudoEdges);

        //other methods 
        std::vector<Edge*> getEdgesFromVertex(Vertex *vertex); //get all edges that have the vertex as origin
        Edge * getNextEdgeOnVertices(Edge *edge); //gets a pointer to the next edge on the same vertices pointer out
        Edge * getPrevEdgeOnVertices(Edge *edge); //gets a pointer to the previous edge on the same vertices pointer in (used when adding an edge)
        //search for a vertex in the DCEL
        Vertex* searchVertex(Vertex vertex);

        void printDCEL();

};



#endif // DCEL_HPP