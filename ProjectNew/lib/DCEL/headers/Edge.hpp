#ifndef DECL_EDGE_HPP
#define DECL_EDGE_HPP

#include "Vertex.hpp"
// TODO #include "Face.hpp"


// Forward declaration
class Face;

class Edge {
    private: 
        Vertex* origin;
        Edge* twin;
        Edge* next;
        Edge* prev;
        Face* incidentFace;
        int id;
        static int idCounter;
    public:
        //Getters
        Vertex* getOrigin();
        Edge* getTwin();
        Edge* getNext();
        Edge* getPrev();
        Face* getIncidentFace();
        int getId();
        //Setters
        void setOrigin(Vertex* origin);
        void setTwin(Edge* twin);
        void setNext(Edge* next);
        void setPrev(Edge* prev);
        void setIncidentFace(Face* incidentFace);
        //Constructors
        Edge();
        Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev, Face* incidentFace);
        Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev);
        //other constructors omitted for brevity use getters and setters (sorry me from the future)
        //Destructor
        ~Edge();
        //Methods
        void printEdge();
};



#endif // DECL_EDGE_HPP