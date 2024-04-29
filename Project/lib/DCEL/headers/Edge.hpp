#ifndef DECL_EDGE_HPP
#define DECL_EDGE_HPP

#include <iostream>
#include <string>
#include "Vertex.hpp"
#include "Face.hpp"

//forward declaration
class Vertex;
class Face;


class Edge {
    private: 
        Vertex* origin;
        Edge* twin;
        Edge* next;
        Edge* prev;
        Face* incidentFace;
        bool isBorder;
        Vertex *site;
        int id;
        static int idCounter;
    public:
        //Getters
        Vertex* getOrigin();
        Edge* getTwin();
        Edge* getNext();
        Edge* getPrev();
        Face* getIncidentFace();
        double getAngle();
        int getId();
        bool getIsBorder();
        Vertex * getSite();
        //Setters
        void setOrigin(Vertex* origin);
        void setTwin(Edge* twin);
        void setNext(Edge* next);
        void setPrev(Edge* prev);
        void setIncidentFace(Face* incidentFace);
        void setIsBorder(bool isBorder);
        void setSite(Vertex * site);
        void setSite(Vertex * site, Vertex * site2);
        //Constructors
        Edge();
        Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev, Face* incidentFace);
        Edge(Vertex* origin, Edge* twin, Edge* next, Edge* prev);
        //other constructors omitted for brevity use getters and setters (sorry me from the future)
        //Destructor
        ~Edge();
        //Methods
        void printEdge();
        bool getIsClosed(); //returns true if the face of the edge is complete (i.e cycles back to the origin edge without hitting the twin of the origin edge)
        //get edge name
        std::string getEdgeName();
};



#endif // DECL_EDGE_HPP