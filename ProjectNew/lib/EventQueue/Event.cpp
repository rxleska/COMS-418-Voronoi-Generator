#include "headers/Event.hpp"
#include "../BeachLine/headers/BeachLine.hpp"
#include "../BeachLine/headers/ParabolaMath.hpp"


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
CircleEvent::CircleEvent(double x, double y, double isy, EdgeNode *leftEdge, EdgeNode *rightEdge){
    //call the parent constructor
    this->setX(x);
    this->setY(y);
    this->setIntersectionY(isy);
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

double CircleEvent::getIntersectionY(){
    return intersectionY;
}

//setters
void CircleEvent::setLeftEdge(EdgeNode *leftEdge){
    this->leftEdge = leftEdge;
}

void CircleEvent::setRightEdge(EdgeNode *rightEdge){
    this->rightEdge = rightEdge;
}

void CircleEvent::setIntersectionY(double intersectionY){
    this->intersectionY = intersectionY;
}

//handle the event
void CircleEvent::handleEvent(){
    //set the sweep line
    beachLine->setSweepLine(this->getY());

    Arc *leftArc = leftEdge->getLeftArc();
    Arc *rightArc = rightEdge->getRightArc();

    beachLine->remove(leftEdge);
    beachLine->remove(rightEdge);

    //create a new edge 
    EdgeNode *newEdge = new EdgeNode();
    newEdge->setLeftArc(leftArc);
    newEdge->setRightArc(rightArc);

    EdgeNode temp;
    if(ParabolaMath::isLessThanDouble(leftArc->getY(), rightArc->getY())){ //use right intersection
        ParabolaMath::getParabolaEdges(*leftArc, *rightArc, beachLine->getSweepLine(), &temp, newEdge);
    }
    else{ //use left intersection
        ParabolaMath::getParabolaEdges(*rightArc, *leftArc, beachLine->getSweepLine(), newEdge, &temp);
    }

    beachLine->insert(newEdge);

    //todo check for more circle events 
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
    beachLine->setSweepLine(this->getY());
    EdgeNode * searchResult = beachLine->search(this->getX());
    if(searchResult == nullptr){
        throw "SiteEvent::handleEvent() - searchResult is nullptr";
    } 
    else{
        
        EdgeNode *leftEdge = new EdgeNode();
        EdgeNode *rightEdge = new EdgeNode();

        Arc *aboveArc;
        //find which arc the site event is below
        if(ParabolaMath::areSameDouble(this->getX(), searchResult->getValue(beachLine->getSweepLine()))){
            //left edge gets left arc and right edge gets right arc
            Arc *newArc = new Arc(this->getX(), this->getY());
            leftEdge->setLeftArc(searchResult->getLeftArc());
            leftEdge->setRightArc(newArc);
            rightEdge->setLeftArc(newArc);
            rightEdge->setRightArc(searchResult->getRightArc());

            EdgeNode temp = EdgeNode(); //used a proxy for the other edge
            ParabolaMath::getParabolaEdges(*searchResult->getLeftArc(), *newArc, beachLine->getSweepLine(), leftEdge, &temp);
            ParabolaMath::getParabolaEdges(*newArc, *searchResult->getRightArc(), beachLine->getSweepLine(), &temp,  rightEdge);
            
            beachLine->remove(searchResult);
        }
        else{ 
            if(ParabolaMath::isLessThanDouble(this->getX(), searchResult->getValue(beachLine->getSweepLine()))){ //use left arc
                aboveArc = searchResult->getLeftArc();
            }
            else{ //use right arc
                aboveArc = searchResult->getRightArc();
            }

            //created 2 new edges and 1 new arc
            Arc *newArc = new Arc(this->getX(), this->getY());
            leftEdge->setLeftArc(aboveArc);
            leftEdge->setRightArc(newArc);
            rightEdge->setLeftArc(newArc);
            rightEdge->setRightArc(aboveArc);

            //set the new edges
            ParabolaMath::getParabolaEdges(*aboveArc, *newArc, beachLine->getSweepLine(), leftEdge, rightEdge);

        }
        //insert the new edges
        beachLine->insert(leftEdge);
        beachLine->insert(rightEdge);

        beachLine->checkCircleEvent(leftEdge, rightEdge);
    }
}