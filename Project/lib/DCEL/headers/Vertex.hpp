

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <string>
#include "../../CONST.hpp"
#include "Edge.hpp"

//forward declaration
class Edge;

class Vertex {
    private:
        static int idCounter;
        static int idCounterBoundary;
        std::vector<Edge*> outwardsEdges;
        std::vector<Edge*> inwardsEdges;
        double x;
        double y;
        Edge * incidentEdge;
        int id;
        bool isBoundary;
    public:
        //constructors
        Vertex();
        Vertex(double x, double y);
        Vertex(double x, double y, int id);
        Vertex(double x, double y, bool isBoundary);

        //getters and setters
        double getX();
        double getY();
        int getId();
        Edge * getIncidentEdge();
        std::vector<Edge*> getOutwardsEdges();
        std::vector<Edge*> getInwardsEdges();
        bool getIsBoundary();
        void setX(double x);
        void setY(double y);
        void setId(int id);
        void setIncidentEdge(Edge * incidentEdge);
        void set(double x, double y);
        void setIsBoundary(bool isBoundary);
        void addOutwardsEdge(Edge * edge);
        void addInwardsEdge(Edge * edge);
        //overload the = operator
        Vertex& operator=(const Vertex &v);
        //copy constructor
        Vertex(const Vertex &v);

        //print vertex
        void printVertex();

        //get vertex name  
        std::string getVertexName();
};

#endif // VERTEX_HPP