
#include "headers/EdgeNode.hpp"
#include "headers/ParabolaMath.hpp"


//constructors
EdgeNode::EdgeNode() {
    this->x = 0;
    this->y = 0;
    this->angle = 0;
    this->left = nullptr;
    this->right = nullptr;
}

EdgeNode::EdgeNode(double x, double y, double angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->left = nullptr;
    this->right = nullptr;
}

EdgeNode::EdgeNode(double x, double y, double angle, EdgeNode *left, EdgeNode *right) {
    this->x = x;
    this->y = y;
    this->angle = angle;
    this->left = left;
    this->right = right;
}

//copyers
EdgeNode::EdgeNode(const EdgeNode &e) {
    this->x = e.x;
    this->y = e.y;
    this->angle = e.angle;
    this->left = e.left;
    this->right = e.right;
}

EdgeNode& EdgeNode::operator=(const EdgeNode &e) {
    this->x = e.x;
    this->y = e.y;
    this->angle = e.angle;
    this->left = e.left;
    this->right = e.right;
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


//value functions

/**
 * Gets where the edge intersects the arcs at the given sweepline height
*/
double EdgeNode::getValue(double sweepline) {
    double x;
    double y;
    if(ParabolaMath::doesLineIntersectParabolaOO(this->leftArc, sweepline, this, &x, &y)){
        return x;
    }
    else{
        ParabolaMath::doesLineIntersectParabolaOO(this->rightArc, sweepline, this, &x, &y);
        return x;
    }
    
}

