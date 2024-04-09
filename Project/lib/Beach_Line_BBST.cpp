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