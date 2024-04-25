#include "headers/Event.hpp"


//###############
// Event class
//###############

//initialize the count
int Event::count = 0;

//default constructor
Event::Event(){
    x = 0;
    y = 0;
    isCircle = false;
    isSite = false;
    isDeleted = false;
    index = count;
    count++;
}

//constructor
Event::Event(double x, double y, bool isCircle, bool isSite){
    this->x = x;
    this->y = y;
    this->isCircle = isCircle;
    this->isSite = isSite;
    this->isDeleted = false;
    this->index = count;
    count++;
}

Event::Event(double x, double y, bool isCircle, bool isSite, int index){
    this->x = x;
    this->y = y;
    this->isCircle = isCircle;
    this->isSite = isSite;
    this->isDeleted = false;
    this->index = index;
}

//destructor
Event::~Event(){
    //nothing to do
}

//getters
double Event::getX(){
    return x;
}

double Event::getY(){
    return y;
}

bool Event::getIsCircle(){
    return isCircle;
}

bool Event::getIsSite(){
    return isSite;
}

bool Event::getIsDeleted(){
    return isDeleted;
}

int Event::getIndex(){
    return index;
}

//setters
void Event::setX(double x){
    this->x = x;
}

void Event::setY(double y){
    this->y = y;
}

void Event::setIsCircle(bool isCircle){
    this->isCircle = isCircle;
}

void Event::setIsSite(bool isSite){
    this->isSite = isSite;
}

void Event::setIsDeleted(bool isDeleted){
    this->isDeleted = isDeleted;
}

void Event::setIndex(int index){
    this->index = index;
}

//overload the = operator
Event& Event::operator=(const Event &e){
    x = e.x;
    y = e.y;
    isCircle = e.isCircle;
    isSite = e.isSite;
    isDeleted = e.isDeleted;
    index = e.index;
    return *this;
}

//copy constructor
Event::Event(const Event &e){
    x = e.x;
    y = e.y;
    isCircle = e.isCircle;
    isSite = e.isSite;
    isDeleted = e.isDeleted;
    index = e.index;
}

//###############
// CircleEvent class
//###############

//default constructor
CircleEvent::CircleEvent(){
    //call the parent constructor
    this->setX(0);
    this->setY(0);
    this->setIsCircle(true);
    this->setIsSite(false);
    this->setIsDeleted(false);
    leftEdge = NULL;
    rightEdge = NULL;
}

//constructor
CircleEvent::CircleEvent(double x, double y, EdgeNode *leftEdge, EdgeNode *rightEdge){
    //call the parent constructor
    this->setX(x);
    this->setY(y);
    this->setIsCircle(true);
    this->setIsSite(false);
    this->setIsDeleted(false);
    this->leftEdge = leftEdge;
    this->rightEdge = rightEdge;
}

//destructor
CircleEvent::~CircleEvent(){
    //nothing to do
}

//getters
EdgeNode *CircleEvent::getLeftEdge(){
    return leftEdge;
}

EdgeNode *CircleEvent::getRightEdge(){
    return rightEdge;
}

//setters
void CircleEvent::setLeftEdge(EdgeNode *leftEdge){
    this->leftEdge = leftEdge;
}

void CircleEvent::setRightEdge(EdgeNode *rightEdge){
    this->rightEdge = rightEdge;
}

//handle the event
void CircleEvent::handleEvent(){
    //TODO implement this
}

//###############
// SiteEvent class
//###############

//default constructor
SiteEvent::SiteEvent(){
    //call the parent constructor
    this->setX(0);
    this->setY(0);
    this->setIsCircle(false);
    this->setIsSite(true);
    this->setIsDeleted(false);
}

//constructor
SiteEvent::SiteEvent(double x, double y){
    //call the parent constructor
    this->setX(x);
    this->setY(y);
    this->setIsCircle(false);
    this->setIsSite(true);
    this->setIsDeleted(false);
}

//destructor
SiteEvent::~SiteEvent(){
    //nothing to do
}

//handle the event
void SiteEvent::handleEvent(){
    //TODO implement this
}