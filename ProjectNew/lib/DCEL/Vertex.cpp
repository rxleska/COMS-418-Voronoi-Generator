#include "headers/Vertex.hpp"

int Vertex::idCounter{0}; //initialize the static variable


//constructors
Vertex::Vertex() {
    this->x = 0;
    this->y = 0;
    this->id = idCounter;
    idCounter++;
}

Vertex::Vertex(double x, double y) {
    this->x = x;
    this->y = y;
    this->id = idCounter;
    idCounter++;
}

Vertex::Vertex(double x, double y, int id) {
    this->x = x;
    this->y = y;
    this->id = id;
    if(id > idCounter) {
        idCounter = id++;
    }
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

void Vertex::setX(double x) {
    this->x = x;
}

void Vertex::setY(double y) {
    this->y = y;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::set(double x, double y) {
    this->x = x;
    this->y = y;
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