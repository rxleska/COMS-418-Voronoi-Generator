//implementation of a beach line item which is sorted in a BBST (lib/BBST.cpp)
// If a beach line item is a leaf node, it represents a arc in the beach line (labeled by a site)
// If a beach line item is a internal node, it represents a breakpoint in the beach line


#include "Beach_Line_Item.hpp"

// Constructors
Beach_Line_Item::Beach_Line_Item(){
    this->isLeaf = 0;
    this->point = nullptr;
    this->leftarc = nullptr;
    this->rightarc = nullptr;
    this->x = -1048576.0; // set to a large negative number
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *point){
    this->isLeaf = 1;
    this->point = point;
    this->leftarc = nullptr;
    this->rightarc = nullptr;
    this->x = -1048576.0; // set to a large negative number
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *point, Beach_Line_Item *parent){
    this->isLeaf = 1;
    this->point = point;
    this->leftarc = nullptr;
    this->rightarc = nullptr;
    this->x = -1048576.0; // set to a large negative number
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *leftarc, Vertex *rightarc){
    this->isLeaf = 0;
    this->point = nullptr;
    this->leftarc = leftarc;
    this->rightarc = rightarc;
    this->x = -1048576.0; // set to a large negative number
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x){
    this->isLeaf = 0;
    this->point = nullptr;
    this->leftarc = leftarc;
    this->rightarc = rightarc;
    this->x = x;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x, Beach_Line_Item *left, Beach_Line_Item *right){
    this->isLeaf = 0;
    this->point = nullptr;
    this->leftarc = leftarc;
    this->rightarc = rightarc;
    this->x = x;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
    this->isRed = 0; // set to black by default
}

Beach_Line_Item::Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x, Beach_Line_Item *left, Beach_Line_Item *right, Beach_Line_Item *parent){
    this->isLeaf = 0;
    this->point = nullptr;
    this->leftarc = leftarc;
    this->rightarc = rightarc;
    this->x = x;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->isRed = 0; // set to black by default
}

// Getters
int Beach_Line_Item::getIsLeaf(){
    return this->isLeaf;
}

Vertex* Beach_Line_Item::getPoint(){
    return this->point;
}

Vertex* Beach_Line_Item::getLeftArc(){
    return this->leftarc;
}

Vertex* Beach_Line_Item::getRightArc(){
    return this->rightarc;
}

double Beach_Line_Item::getX(){
    return this->x;
}

Beach_Line_Item* Beach_Line_Item::getLeft(){
    return this->left;
}

Beach_Line_Item* Beach_Line_Item::getRight(){
    return this->right;
}

Beach_Line_Item* Beach_Line_Item::getParent(){
    return this->parent;
}

int Beach_Line_Item::getIsRed(){
    return this->isRed;
}

Beach_Line_Item* Beach_Line_Item::getUncle(){
    if(this->parent == nullptr || this->parent->parent == nullptr){
        return nullptr;
    }
    if(this->parent == this->parent->parent->left){
        return this->parent->parent->right;
    }else{
        return this->parent->parent->left;
    }
}

// Setters
void Beach_Line_Item::setIsLeaf(int isLeaf){
    this->isLeaf = isLeaf;
}

void Beach_Line_Item::setPoint(Vertex *point){
    this->point = point;
}

void Beach_Line_Item::setLeftArc(Vertex *leftarc){
    this->leftarc = leftarc;
}

void Beach_Line_Item::setRightArc(Vertex *rightarc){
    this->rightarc = rightarc;
}

void Beach_Line_Item::setX(double x){
    this->x = x;
}

void Beach_Line_Item::setLeft(Beach_Line_Item *left){
    this->left = left;
}

void Beach_Line_Item::setRight(Beach_Line_Item *right){
    this->right = right;
}

void Beach_Line_Item::setParent(Beach_Line_Item *parent){
    this->parent = parent;
}

void Beach_Line_Item::setIsRed(int isRed){
    this->isRed = isRed;
}