

#include "headers/BeachLine.hpp"

BeachLine::BeachLine() {
    this->root = nullptr;
    this->sweepLine = 0;
}

BeachLine::BeachLine(double sweepLine) {
    this->root = nullptr;
    this->sweepLine = sweepLine;
}

//getters and setters
EdgeNode *BeachLine::getRoot() {
    return this->root;
}

void BeachLine::setRoot(EdgeNode *root) {
    this->root = root;
}

double BeachLine::getSweepLine() {
    return this->sweepLine;
}

void BeachLine::setSweepLine(double sweepLine) {
    this->sweepLine = sweepLine;
}

//tree functions

void BeachLine::rightRotate(EdgeNode *node) {
    EdgeNode *y  = node->getLeft();
    node->setLeft(y->getRight());
    if (y->getRight() != nullptr) {
        y->getRight()->setParent(node);
    }
    y->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root = y;
    } else if (node == node->getParent()->getRight()) {
        node->getParent()->setRight(y);
    } else {
        node->getParent()->setLeft(y);
    }
    y->setRight(node);
    node->setParent(y);
}

void BeachLine::leftRotate(EdgeNode *node) {
    EdgeNode *y = node->getRight();
    node->setRight(y->getLeft());
    if (y->getLeft() != nullptr) {
        y->getLeft()->setParent(node);
    }
    y->setParent(node->getParent());
    if (node->getParent() == nullptr) {
        this->root = y;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(y);
    } else {
        node->getParent()->setRight(y);
    }
    y->setLeft(node);
    node->setParent(y);
}

void BeachLine::splay(EdgeNode *node) {
    while(node->getParent() != nullptr){
        if(node->getParent()->getParent() == nullptr){
            if(node->getParent()->getLeft() == node) rightRotate(node->getParent());
            else leftRotate(node->getParent());
        } else if(node->getParent()->getLeft() == node && node->getParent()->getParent()->getLeft() == node->getParent()){
            rightRotate(node->getParent()->getParent());
            rightRotate(node->getParent());
        } else if(node->getParent()->getRight() == node && node->getParent()->getParent()->getRight() == node->getParent()){
                leftRotate(node->getParent()->getParent());
                leftRotate(node->getParent());
        } else if(node->getParent()->getLeft() == node && node->getParent()->getParent()->getRight() == node->getParent()){
            rightRotate(node->getParent());
            leftRotate(node->getParent());
        } else {
            leftRotate(node->getParent());
            rightRotate(node->getParent());
        }
    }
}


EdgeNode *BeachLine::search(double searchX) {
    //TODO return the node that is closest to the searchX
    EdgeNode *current = this->root;
    while (current != nullptr) {
        double value = current->getValue(this->sweepLine);
        if (searchX < value) current = current->getLeft();
        else if (searchX > value) current = current->getRight();
        else {
            splay(current);
            return current;
        }
    
    }
    return nullptr;
}



void BeachLine::insert(EdgeNode *node){
    if(this->root == nullptr){
        this->root = node;
        return;
    }
    EdgeNode *current = this->root;
    EdgeNode *parent = nullptr;
    while(current != nullptr){
        parent = current;
        if(node->getValue(this->sweepLine) < current->getValue(this->sweepLine)){
            current = current->getLeft();
        } else {
            current = current->getRight();
        }
    }

    node->setParent(parent);
    if(node->getValue(this->sweepLine) < parent->getValue(this->sweepLine)){
        parent->setLeft(node);
    } else {
        parent->setRight(node);
    }

    splay(node);
}


