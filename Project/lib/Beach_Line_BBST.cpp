//implementation of a balanced binary search tree (BBST), used to store the beach line of the voronoi diagram algorithm
// will sort beach line items (lib/beach_line_item.cpp)
#include "Beach_Line_BBST.hpp"

#include <iostream>

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

    // if the parent is red, fix the tree
    //3 cases uncle is red too, uncle is black or null
    // note for self uncles is the sibling of the parent i.e the other child of the grandparent
    if(parent->getIsRed()){
        Beach_Line_Item *uncle = item->getUncle();
        Beach_Line_Item *grandparent = parent->getParent();
        if(uncle != nullptr && uncle->getIsRed()){ // uncle is a red node 
            parent->setIsRed(0); // set the parent to black
            uncle->setIsRed(0); // set the uncle to black
            //if grandparent is not root 
            if(parent->getParent() != this->root){ //prevent root from becoming red (not allowed in RB trees)
                parent->getParent()->setIsRed(1); // set the grandparent to red
            }
        }
        else{ //uncle is a black node, 4 cases 
            int parentIsRightChild = (parent == grandparent->getRight());
            int itemIsRightChild = (item == parent->getRight());
            if(parentIsRightChild && itemIsRightChild){// Parent is right child of grandparent and new node is right child of parent
                //left rotation at grandparent
                Beach_Line_Item *sibling = parent->getLeft();
                //if grandparent is root (use this->root instead of greatparent)
                if(grandparent == this->root){ //using root
                    //set in order of top down left right
                    //top
                    this->root = parent;
                    parent->setParent(nullptr);
                    parent->setIsRed(0); // set the parent to black

                    //left
                    parent->setLeft(grandparent);
                    grandparent->setParent(parent);
                    grandparent->setIsRed(0); // set the grandparent to black (black next to black is fine due to the upper node being the root)

                    //right
                    parent->setRight(item);
                    item->setParent(parent);
                    item->setIsRed(0); // set the item to black (black next to black is fine due to the upper node being the root)

                    //left left already set 
                    grandparent->getLeft()->setIsRed(1); // set the left left to red

                    //left right 
                    grandparent->setLeft(sibling);
                    if(sibling != nullptr){
                        sibling->setParent(grandparent);
                        sibling->setIsRed(1); // set the left right to red
                    }

                    //right left and right right are null since they are null on addition 
                }
                else{ //using greatparent
                    Beach_Line_Item *greatparent = grandparent->getParent();
                    if(greatparent->getLeft() == grandparent){ //grandparent is left child of greatparent
                        //set in order of top down left right 
                        //top
                        greatparent->setLeft(parent);
                        parent->setParent(greatparent);

                    }else{ //grandparent is right child of greatparent
                        //set in order of top down left right
                        //top
                        greatparent->setRight(parent);
                        parent->setParent(greatparent);
                    }
                    //left 
                    parent->setLeft(grandparent);
                    grandparent->setParent(parent);

                    //right
                    parent->setRight(item);
                    item->setParent(parent);

                    //left left already set 

                    //left right 
                    grandparent->setRight(sibling);
                    sibling->setParent(grandparent);

                    //right left and right right are null since they are null 

                }
            
            }else if(parentIsRightChild && (!itemIsRightChild)){// Parent is right child of grandparent and new node is left child of parent
                //right rotation at parent
                grandparent->setRight(item);
                item->setParent(grandparent);

                item->setRight(parent);
                parent->setParent(item);

                parent->setLeft(nullptr);


            }else if((!parentIsRightChild) && (!itemIsRightChild)){// Parent is left child of grandparent and new node is left child of parent
                //right rotation at grandparent
                //if grandparent is root (use this->root instead of greatparent)
                if(grandparent == this->root){ //using root
                    //set in order of top down right left
                    //top
                    this->root = parent;
                    parent->setParent(nullptr);

                    //left
                    parent->setLeft(item);
                    item->setParent(parent);

                    //right
                    parent->setRight(grandparent);
                    grandparent->setParent(parent);

                    //left right and left left are null since they are null

                    //right left 
                    grandparent->setRight(nullptr);

                    //right right already set 

                }
                else{ //using greatparent
                    Beach_Line_Item *greatparent = grandparent->getParent();
                    Beach_Line_Item *sibling = parent->getRight();
                    if(greatparent->getRight() == grandparent){ //grandparent is right child of greatparent
                        //set in order of top down right left 
                        //top
                        greatparent->setRight(parent);
                        parent->setParent(greatparent);

                    }else{ //grandparent is left child of greatparent
                        //set in order of top down right left
                        //top
                        greatparent->setLeft(parent);
                        parent->setParent(greatparent);
                    }
                    
                    //left
                    parent->setLeft(item);
                    item->setParent(parent);
                    
                    //right 
                    parent->setRight(grandparent);
                    grandparent->setParent(parent);

                    //left right and left left are null since they are null 

                    //right left 
                    grandparent->setLeft(sibling);
                    sibling->setParent(grandparent);

                    //right right already set 

                }
            
            }else{// Parent is left child of grandparent and new node is right child of parent 
                //left rotation at parent
                grandparent->setLeft(item);
                item->setParent(grandparent);

                item->setLeft(parent);
                parent->setParent(item);

                parent->setRight(nullptr);
            }
        }
    }
}




void Beach_line_BBST::remove(Beach_Line_Item *item){
    // if the tree is empty, return
    if(this->root == nullptr){
        return;
    }

    // find the item to remove
    Beach_Line_Item *current = this->root;
    while(current != nullptr){
        if(item->getX() == current->getX()){
            break;
        }else if(item->getX() < current->getX()){
            current = current->getLeft();
        }else{
            current = current->getRight();
        }
    }

    // if item is not found, return
    if(current == nullptr){
        return;
    }

    //if the item has 0 children remove it (case 1)
    if(current->getLeft() == nullptr && current->getRight() == nullptr){
        if(current == this->root){
            this->root = nullptr;
        }else{
            if(current->getParent()->getLeft() == current){
                current->getParent()->setLeft(nullptr);
            }else{
                current->getParent()->setRight(nullptr);
            }
        }
        return;
    }

    //if the item has 1 child the child replaces item (case 2)
    if(current->getLeft() == nullptr || current->getRight() == nullptr){
        Beach_Line_Item *child = current->getLeft() == nullptr ? current->getRight() : current->getLeft();
        if(current == this->root){
            this->root = child;
            child->setParent(nullptr);
        }else{
            if(current->getParent()->getLeft() == current){
                current->getParent()->setLeft(child);
            }else{
                current->getParent()->setRight(child);
            }
            child->setParent(current->getParent());
        }
        return;
    }

    //if the item has 2 children, replace the item with the inorder successor (case 3)
    //which is the leftmost node in the right subtree. Then delete the in-order successor node as if it has at most one child.
    Beach_Line_Item *successor = current->getRight();
    while(successor->getLeft() != nullptr){
        successor = successor->getLeft();
    } 
    //if the successor has a right child, replace item with successor and successor with its right child
    if(successor->getRight() != nullptr){
        if(successor->getParent()->getLeft() == successor){
            successor->getParent()->setLeft(successor->getRight());
        }else{
            successor->getParent()->setRight(successor->getRight());
        }
        successor->getRight()->setParent(successor->getParent());
    }
    //replace item with successor
    if(current == this->root){
        this->root = successor;
        successor->setParent(nullptr);
    }else{
        if(current->getParent()->getLeft() == current){
            current->getParent()->setLeft(successor);
        }else{
            current->getParent()->setRight(successor);
        }
        successor->setParent(current->getParent());
    }

    //set the children of the successor to the children of the item
    successor->setLeft(current->getLeft());
    current->getLeft()->setParent(successor);
    successor->setRight(current->getRight());
    current->getRight()->setParent(successor);


}


void Beach_line_BBST::printForestViewLatex(Beach_Line_Item *item){
    if(this->root == nullptr){
        std::cout << "" << std::endl;
        return;
    }

    std::cout << "[" << std::endl;
    std::cout << "    " << item->getX() << " " << item->getPoint()->y << " " << item->getIsRed() << std::endl;
    if(item->getLeft() != nullptr){
        printForestViewLatex(item->getLeft());
    }else{
        std::cout << "    " << "null" << std::endl;
    }
    if(item->getRight() != nullptr){
        printForestViewLatex(item->getRight());
    }else{
        std::cout << "    " << "null" << std::endl;
    }
    std::cout << "]" << std::endl;
}