// This is an implementations of an beach line sweep event, which is used in the beach line sweep algorithm
// There are 2 possible types of events: site events and circle events


#include "headers/Event.hpp"


Event::Event(){
    this->type = -1;
    this->point = nullptr;
}

Event::Event(int type, Vertex *point){
    this->type = type;
    this->point = point;
}

int Event::getType(){
    return this->type;
}

Vertex* Event::getPoint(){
    return this->point;
}

void Event::setType(int type){
    this->type = type;
}

void Event::setPoint(Vertex *point){
    this->point = point;
}

