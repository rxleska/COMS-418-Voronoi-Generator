// This is an implementations of an beach line sweep event, which is used in the beach line sweep algorithm
// There are 2 possible types of events: site events and circle events


#include "headers/Event.hpp"

CircleEvent::CircleEvent(Node *leftA, Node *leftE, Node *pinchingA, Node *rightE, Node *rightA){
    this->leftArc = leftA;
    this->leftEdge = leftE;
    this->pinchingArc = pinchingA;
    this->rightEdge = rightE;
    this->rightArc = rightA;
}

CircleEvent::~CircleEvent(){
    //TODO check if we want to delete any of these nodes on circle event deletion
    //delete this->leftEdge;
    //delete this->rightEdge;
    //delete this->pinchingArc;
}


Event::Event(){
    this->type = -1;
    this->point = nullptr;
}

Event::Event(Vertex *point){
    this->type = 0;
    this->point = point;
}

Event::Event(CircleEvent *circleEvent){
    this->type = 1;
    this->circleEvent = circleEvent;
}

Event::Event(Vertex *point, Node *leftA, Node *leftE, Node *pinchingA, Node *rightE, Node *rightA){
    this->type = 1;
    this->point = point;
    this->circleEvent = new CircleEvent(leftA, leftE, pinchingA, rightE, rightA);
}

Event::Event(Event const &event){
    this->type = event.type;
    if(this->type == 1)
        this->circleEvent = new CircleEvent(event.circleEvent->leftArc, event.circleEvent->leftEdge, event.circleEvent->pinchingArc, event.circleEvent->rightEdge, event.circleEvent->rightArc);
    this->point = event.point;
}

Event::~Event(){
    // if(this->type == 1){
    //     delete this->circleEvent;
    // }
}

int Event::getType(){
    return this->type;
}

Vertex* Event::getPoint(){
    return this->point;
}

CircleEvent* Event::getCircleEvent(){
    return this->circleEvent;
}

void Event::setType(int type){
    this->type = type;
}

void Event::setPoint(Vertex *point){
    this->point = point;
}

void Event::setCircleEvent(CircleEvent *circleEvent){
    this->circleEvent = circleEvent;
}
