
#include "headers/Face.hpp"


//Static variable initialization
int Face::idCounter = 1;

//Getters
int Face::getId(){
    return id;
}

Edge* Face::getOuterComponent(){
    return outerComponent;
}

Edge* Face::getInnerComponent(){
    return innerComponent;
}

bool Face::getIsUnbounded(){
    return isUnbounded;
}

Vertex * Face::getSite(){
    return site;
}

//Setters
void Face::setOuterComponent(Edge* outerComponent){
    this->outerComponent = outerComponent;
}

void Face::setInnerComponent(Edge* innerComponent){
    this->innerComponent = innerComponent;
}

void Face::setId(int id){
    this->id = id;
}

void Face::setIsUnbounded(bool isUnbounded){
    this->isUnbounded = isUnbounded;
}

void Face::setSite(Vertex * site){
    this->site = site;
}

//Constructors
Face::Face(){
    id = idCounter++;
    outerComponent = nullptr;
    innerComponent = nullptr;
    this->isUnbounded = false;
    this->site = nullptr;
}

Face::Face(int id){
    this->id = id;
    outerComponent = nullptr;
    innerComponent = nullptr;
    this->isUnbounded = false;
    this->site = nullptr;
}

Face::Face(Edge* outerComponent, Edge* innerComponent){
    id = idCounter++;
    this->outerComponent = outerComponent;
    this->innerComponent = innerComponent;
    this->isUnbounded = false;
    this->site = nullptr;
}

Face::Face(Edge* outerComponent, Edge* innerComponent, int id){
    this->id = id;
    this->outerComponent = outerComponent;
    this->innerComponent = innerComponent;
    this->isUnbounded = false;
    this->site = nullptr;
}

//Destructor
Face::~Face(){
    //delete outerComponent;
    //delete innerComponent;
}

//Methods
void Face::printFace(){
    if(isUnbounded) std::cout << "uf" << id << " " << (outerComponent == nullptr? "nil" : outerComponent->getEdgeName()) << " " << (innerComponent == nullptr? "nil" : innerComponent->getEdgeName()) << std::endl;
    else std::cout << "f" << id << " " << (outerComponent == nullptr? "nil" : outerComponent->getEdgeName()) << " " << (innerComponent == nullptr? "nil" : innerComponent->getEdgeName()) << std::endl;
}

std::string Face::faceToString(bool isVoronoi){
    std::string faceString = "";
    if(isUnbounded){
        faceString += "uf" + std::to_string(id) + " " + 
        (outerComponent == nullptr? "nil" : outerComponent->getEdgeName(isVoronoi)) + " " + 
        (innerComponent == nullptr? "nil" : innerComponent->getEdgeName(isVoronoi));
    }
    else{
        faceString += (isVoronoi? "f" :"t") + std::to_string(id) + " " + 
        (outerComponent == nullptr? "nil" : outerComponent->getEdgeName(isVoronoi)) + " " + 
        (innerComponent == nullptr? "nil" : innerComponent->getEdgeName(isVoronoi));
    }
    return faceString;
}

std::string Face::getFaceName(){
    if(isUnbounded){
        return "uf" + std::to_string(id);
    }
    return "f" + std::to_string(id);
}

std::string Face::getFaceName(bool isVoronoi){
    if(isUnbounded){
        return "uf" + std::to_string(id);
    }
    return (isVoronoi? "f" :"t") + std::to_string(id);
}

//Methods
std::vector<Vertex> Face::getVertices(){
    std::vector<Vertex> vertices;
    Edge* edge = outerComponent;
    do{
        vertices.push_back(*edge->getOrigin());
        edge = edge->getNext();
    }while(edge != outerComponent);
    return vertices;
}

std::vector<Edge> Face::getEdges(){
    std::vector<Edge> edges;
    Edge* edge = outerComponent;
    do{
        edges.push_back(*edge);
        edge = edge->getNext();
    }while(edge != outerComponent);
    return edges;
}