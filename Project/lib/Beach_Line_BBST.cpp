//implementation of a balanced binary search tree (BBST), used to store the beach line of the voronoi diagram algorithm
// will sort beach line items (lib/beach_line_item.cpp)
#include "Beach_Line_BBST.hpp"

Beach_line_BBST::Beach_line_BBST(){
    this->root = nullptr;
}

Beach_line_BBST::Beach_line_BBST(Beach_Line_Item *root){
    this->root = root;
}

Beach_Line_Item* Beach_line_BBST::getRoot(){
    return this->root;
}

void Beach_line_BBST::setRoot(Beach_Line_Item *root){
    this->root = root;
}

void Beach_line_BBST::insert(Beach_Line_Item *item){
    // if the tree is empty, set the root to the new item
    if(this->root == nullptr){
        this->root = item;
        this->root->setIsRed(0); // set the root to black
        return;
    }
    // if the tree is not empty, find the correct place to insert the new item
    Beach_Line_Item *current = this->root;
    Beach_Line_Item *parent = nullptr;
    while(current != nullptr){
        parent = current;
        if(item->getX() < current->getX()){
            current = current->getLeft();
        }else{
            current = current->getRight();
        }
    }
    // set the parent of the new item to the parent found in the while loop
    item->setParent(parent);
    // set the new item as the left or right child of the parent depending on the x-coordinate
    if(item->getX() < parent->getX()){
        parent->setLeft(item);
    }else{
        parent->setRight(item);
    }

    // check if the tree is still a valid red-black tree after the insertion
    


}