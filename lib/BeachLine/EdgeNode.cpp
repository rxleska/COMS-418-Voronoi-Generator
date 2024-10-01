
#include "headers/EdgeNode.hpp"
#include "headers/ParabolaMath.hpp"


//constructors
EdgeNode::EdgeNode() {
    this->x = 0;
    this->y = 0;
    this->angle = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

EdgeNode::EdgeNode(double x, double y, double angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

EdgeNode::EdgeNode(double x, double y, double angle, EdgeNode *left, EdgeNode *right) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

//destructor
EdgeNode::~EdgeNode() {
    //nothing to do
}

//copyers
EdgeNode::EdgeNode(const EdgeNode &e) {
    this->x = e.x;
    this->y = e.y;
    this->angle = e.angle;
    this->left = e.left;
    this->right = e.right;
    this->parent = e.parent;
}

EdgeNode& EdgeNode::operator=(const EdgeNode &e) {
    this->x = e.x;
    this->y = e.y;
    this->angle = e.angle;
    this->left = e.left;
    this->right = e.right;
    this->parent = e.parent;
    return *this;
}

//getters and setters
EdgeNode *EdgeNode::getLeft() {
    return this->left;
}

EdgeNode *EdgeNode::getRight() {
    return this->right;
}

EdgeNode *EdgeNode::getParent() {
    return this->parent;
}

double EdgeNode::getX() {
    return this->x;
}

double EdgeNode::getY() {
    return this->y;
}

double EdgeNode::getAngle() {
    if(this->angle < 0){
        while(this->angle < 0){
            this->angle += 2*PI;
        }
    }

    return this->angle;
}

Arc *EdgeNode::getLeftArc() {
    return this->leftArc;
}

Arc *EdgeNode::getRightArc() {
    return this->rightArc;
}

void EdgeNode::setLeft(EdgeNode *left) {
    this->left = left;
}

void EdgeNode::setRight(EdgeNode *right) {
    this->right = right;
}

void EdgeNode::setParent(EdgeNode *parent) {
    this->parent = parent;
}

void EdgeNode::setX(double x) {
    this->x = x;
}

void EdgeNode::setY(double y) {
    this->y = y;
}

void EdgeNode::setAngle(double angle) {
    this->angle = angle;
}

void EdgeNode::setLeftArc(Arc *leftArc) {
    this->leftArc = leftArc;
}

void EdgeNode::setRightArc(Arc *rightArc) {
    this->rightArc = rightArc;
}

bool EdgeNode::pointsDown() {
    return this->getAngle() > PI;
}

bool EdgeNode::pointsUp() {
    return this->getAngle() < PI;
}


//value functions

/**
 * Gets where the edge intersects the arcs at the given sweepline height
*/
double EdgeNode::getValue(double sweepline) {
    if(this->getAngle() == PI/2.0 || this->getAngle() == 3*PI/2.0){
        return this->getX();
    }

    double x;
    double y;
    if(ParabolaMath::doesLineIntersectParabolaOO(this->leftArc, sweepline, this, &x, &y)){
        return x;
    }
    else{
        if(ParabolaMath::doesLineIntersectParabolaOO(this->rightArc, sweepline, this, &x, &y)){
            return x;
        }
        else{
            return this->getX();
        }
    }
    
}

