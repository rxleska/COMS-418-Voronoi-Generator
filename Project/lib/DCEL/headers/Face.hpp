#ifndef FACE_HPP
#define FACE_HPP

#include "Edge.hpp"
#include "Vertex.hpp"

// forward declaration
class Edge;
class Vertex;

#include <iostream>
#include <string>
#include <vector>

class Face{
    private: 
        static int idCounter;
        int id;
        Edge* outerComponent;
        Edge* innerComponent;
        bool isUnbounded;
    public:
        //Getters
        int getId();
        Edge* getOuterComponent();
        Edge* getInnerComponent();
        bool getIsUnbounded();
        //Setters
        void setOuterComponent(Edge* outerComponent);
        void setInnerComponent(Edge* innerComponent);
        void setId(int id);
        void setIsUnbounded(bool isUnbounded);
        //Constructors
        Face();
        Face(Edge* outerComponent, Edge* innerComponent);
        Face(Edge* outerComponent, Edge* innerComponent, int id);
        //Destructor
        ~Face();

        //Methods
        void printFace();
        std::string getFaceName();

        //Methods
        std::vector<Vertex> getVertices();
        std::vector<Edge> getEdges();
};



#endif // FACE_HPP