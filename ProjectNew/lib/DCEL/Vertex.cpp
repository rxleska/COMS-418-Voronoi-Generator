#include "headers/Vertex.hpp"

int Vertex::idCounter{1}; //initialize the static variable
int Vertex::idCounterBoundary{5};


//constructors
Vertex::Vertex() {
    this->x = 0;
    this->y = 0;
    this->incidentEdge = nullptr;
    outwardsEdges = std::vector<Edge*>();
    inwardsEdges = std::vector<Edge*>();
    this->id = idCounter++;
    this->isBoundary = false;
}

Vertex::Vertex(double x, double y) {
    this->x = x;
    this->y = y;
    this->incidentEdge = nullptr;
    outwardsEdges = std::vector<Edge*>();
    inwardsEdges = std::vector<Edge*>();
    this->id = idCounter++;
    this->isBoundary = false;
    // std::cout << "Vertex created with id: " << id << std::endl;
}

Vertex::Vertex(double x, double y, int id) {
    this->x = x;
    this->y = y;
    this->incidentEdge = nullptr;
    outwardsEdges = std::vector<Edge*>();
    inwardsEdges = std::vector<Edge*>();
    this->id = id;
    if(id > idCounter) {
        idCounter = id++;
    }
    this->isBoundary = false;
    // std::cout << "Vertex created with id: " << id << std::endl;
}

Vertex::Vertex(double x, double y, bool isBoundary) {
    this->x = x;
    this->y = y;
    this->incidentEdge = nullptr;
    outwardsEdges = std::vector<Edge*>();
    inwardsEdges = std::vector<Edge*>();
    if(isBoundary) {
        this->id = idCounterBoundary++;
    }
    else {
        this->id = idCounter++;
    }
    this->isBoundary = isBoundary;
}

//getters and setters
double Vertex::getX() {
    return this->x;
}

double Vertex::getY() {
    return this->y;
}

int Vertex::getId() {
    return this->id;
}

Edge * Vertex::getIncidentEdge() {
    return this->incidentEdge;
}

std::vector<Edge*> Vertex::getOutwardsEdges() {
    return this->outwardsEdges;
}

std::vector<Edge*> Vertex::getInwardsEdges() {
    return this->inwardsEdges;
}

bool Vertex::getIsBoundary() {
    return this->isBoundary;
}

void Vertex::setX(double x) {
    this->x = x;
}

void Vertex::setY(double y) {
    this->y = y;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setIncidentEdge(Edge * incidentEdge) {
    this->incidentEdge = incidentEdge;
}

void Vertex::set(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vertex::setIsBoundary(bool isBoundary) {
    this->isBoundary = isBoundary;
}

void Vertex::addOutwardsEdge(Edge * edge) {
    this->outwardsEdges.push_back(edge);
}

void Vertex::addInwardsEdge(Edge * edge) {
    this->inwardsEdges.push_back(edge);
}

//overload the = operator
Vertex& Vertex::operator=(const Vertex &v) {
    this->x = v.x;
    this->y = v.y;
    this->id = v.id;
    return *this;
}

//copy constructor
Vertex::Vertex(const Vertex &v) {
    this->x = v.x;
    this->y = v.y;
    this->id = v.id;
}

//print vertex
void Vertex::printVertex() {
    if(isBoundary){
        std::cout << "b" << id << " (" << x << ", " << y << ") " << (incidentEdge == nullptr ? "nil": incidentEdge->getEdgeName()) << std::endl;
        return;
    }
    std::cout << "v" << id << " (" << x << ", " << y << ") " << (incidentEdge == nullptr ? "nil": incidentEdge->getEdgeName()) << std::endl;
}

//get vertex name
std::string Vertex::getVertexName() {
    if(isBoundary) {
        return "b" + std::to_string(id);
    }

    return "v" + std::to_string(id);
}

