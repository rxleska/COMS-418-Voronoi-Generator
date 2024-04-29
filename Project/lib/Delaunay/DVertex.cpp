
#include "headers/DVertex.hpp"

int DVertex::idCounter = 1;

DVertex::DVertex(){
    this->x = 0;
    this->y = 0;
    this->id = idCounter++;
}

DVertex::DVertex(double x, double y){
    this->x = x;
    this->y = y;
    this->id = idCounter++;
}

DVertex::DVertex(double x, double y, int id){
    this->x = x;
    this->y = y;
    this->id = id;
}

double DVertex::getX(){
    return this->x;
}

double DVertex::getY(){
    return this->y;
}

int DVertex::getId(){
    return this->id;
}

void DVertex::setX(double x){
    this->x = x;
}

void DVertex::setY(double y){
    this->y = y;
}

void DVertex::setId(int id){
    this->id = id;
}