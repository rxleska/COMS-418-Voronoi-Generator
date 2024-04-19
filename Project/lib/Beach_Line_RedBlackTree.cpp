#include <iostream>
#include "headers/Vertex.hpp"
#include "headers/ProjectCalculations.hpp"

#ifndef BEACH_LINE_RBT 
#define BEACH_LINE_RBT

enum COLOR
{
    RED,
    BLACK
};

class Node
{
public: 

    //implementation idea let leaves be assumed to exist stored in the vertices of the arcs
    //instead of comparing a value then updating the value, store a line that the arc left side is on, use this line to compare the arcs at the given sweep line height
    //could always add the leaves back using val


    float val;
    bool isArc;
    Vertex *leftarc, *rightarc; 
    COLOR color;
    Node *left, *right, *parent;
    float slope, intercept;

    Node() : val(-183484516925440.0), isArc(true) //note I am using an arbitrary value to represent the negative infinity
    {
        parent = left = right = NULL;

        // Node is created during insertion
        // Node is red at insertion
        color = RED;
    }

    Node(float val) : val(val), isArc(false)
    {
        parent = left = right = NULL;

        // Node is created during insertion
        // Node is red at insertion
        color = RED;
    }

    // returns pointer to uncle
    Node *uncle()
    {
        // If no parent or grandparent, then no uncle
        if (parent == NULL || parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right;
        else
            // uncle on left
            return parent->parent->left;
    }

    //returns pointer to next left node from the current node
    Node *nextLeft(){
        //if no left child, return parent, if no parent return null or if parent is right of this node (parent->left = this)
        if(left == NULL){
            if(parent == NULL || parent->left == this){
                return NULL;
            }
            return parent;
        }
        //if left child exists, return the rightmost child of the left child
        Node *temp = left;
        while(temp->right != NULL){
            temp = temp->right;
        }
        return temp;
    }

    //returns pointer to next right node from the current node
    Node *nextRight(){
        //if no right child, return parent, if no parent return null or if parent is left of this node (parent->right = this)
        if(right == NULL){
            if(parent == NULL || parent->right == this){
                return NULL;
            }
            return parent;
        }
        //if right child exists, return the leftmost child of the right child
        Node *temp = right;
        while(temp->left != NULL){
            temp = temp->left;
        }
        return temp;
    }




    // check if node is left child of parent
    bool isOnLeft() { return this == parent->left; }

    // returns pointer to sibling
    Node *sibling()
    {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    // moves node down and moves given node in its place
    void moveDown(Node *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild()
    {
        return (left != NULL && left->color == RED) ||
               (right != NULL && right->color == RED);
    }


    float getVal(){
        if(isArc){
            //calculate the x value of the arc at the sweep line y,
            // y=mx + b => x = (y-b)/m
            if(slope == 0){
                return leftarc->x; //this is used when there is only 1 arc in the beach line
            }

            float result = (sweepLine - intercept) / slope;
            return result;
        }
        else{
            return val;
        }
    }

    void swapStoredValues(Node* u){

        //load into temp
        Node* temp = new Node();
        temp->slope = this->slope;
        temp->intercept = this->intercept;
        temp->leftarc = this->leftarc;
        temp->rightarc = this->rightarc;
        temp->val = this->val;
        temp->isArc = this->isArc;

        //u into this
        this->slope = u->slope;
        this->intercept = u->intercept;
        this->leftarc = u->leftarc;
        this->rightarc = u->rightarc;
        this->val = u->val;
        this->isArc = u->isArc;

        //temp into u
        u->slope = temp->slope;
        u->intercept = temp->intercept;
        u->leftarc = temp->leftarc;
        u->rightarc = temp->rightarc;
        u->val = temp->val;
        u->isArc = temp->isArc;
    }


};

class RBTree
{
    Node *root;
    public:
        int count = 0;

    // left rotates the given node
    void leftRotate(Node *x)
    {
        // new parent will be node's right child
        Node *nParent = x->right;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right = nParent->left;
        // connect new parent's left element with node
        // if it is not null
        if (nParent->left != NULL)
            nParent->left->parent = x;

        // connect new parent with x
        nParent->left = x;
    }

    void rightRotate(Node *x)
    {
        // new parent will be node's left child
        Node *nParent = x->left;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left = nParent->right;
        // connect new parent's right element with node
        // if it is not null
        if (nParent->right != NULL)
            nParent->right->parent = x;

        // connect new parent with x
        nParent->right = x;
    }

    void swapColors(Node *x1, Node *x2)
    {
        COLOR temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node *u, Node *v)
    {
        u->swapStoredValues(v);
    }

    // fix red red at given node
    void fixRedRed(Node *x)
    {
        // if x is root color it black and return
        if (x == root)
        {
            x->color = BLACK;
            return;
        }

        // initialize parent, grandparent, uncle
        Node *parent = x->parent, *grandparent = parent->parent,
             *uncle = x->uncle();

        if (parent->color != BLACK)
        {
            if (uncle != NULL && uncle->color == RED)
            {
                // uncle red, perform recoloring and recurse
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            }
            else
            {
                // Else perform LR, LL, RL, RR
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                    {
                        // for left right
                        swapColors(parent, grandparent);
                    }
                    else
                    {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // for left left and left right
                    rightRotate(grandparent);
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        // for right left
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else
                    {
                        swapColors(parent, grandparent);
                    }

                    // for right right and right left
                    leftRotate(grandparent);
                }
            }
        }
    }

    // find node that do not have a left child
    // in the subtree of the given node
    Node *successor(Node *x)
    {
        Node *temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    // find node that replaces a deleted node in BST
    Node *BSTreplace(Node *x)
    {
        // when node have 2 children
        if (x->left != NULL && x->right != NULL)
            return successor(x->right);

        // when leaf
        if (x->left == NULL && x->right == NULL)
            return NULL;

        // when single child
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }

    // deletes the given node
    void deleteNode(Node *v)
    {
        Node *u = BSTreplace(v);

        // True when u and v are both black
        bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
        Node *parent = v->parent;

        if (u == NULL)
        {
            // u is NULL therefore v is leaf
            if (v == root)
            {
                // v is root, making root null
                root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    // u and v both black
                    // v is leaf, fix double black at v
                    fixDoubleBlack(v);
                }
                else
                {
                    // u or v is red
                    if (v->sibling() != NULL)
                        // sibling is not null, make it red"
                        v->sibling()->color = RED;
                }

                // delete v from the tree
                if (v->isOnLeft())
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            delete v;
            return;
        }

        if (v->left == NULL || v->right == NULL)
        {
            // v has 1 child
            if (v == root)
            {
                // v is root, assign the value of u to v, and delete u
                v->val = u->val;
                v->isArc = u->isArc;
                v->leftarc = u->leftarc;
                v->rightarc = u->rightarc;
                v->slope = u->slope;
                v->intercept = u->intercept;

                v->left = v->right = NULL;
                delete u;
            }
            else
            {
                // Detach v from tree and move u up
                if (v->isOnLeft())
                {
                    parent->left = u;
                }
                else
                {
                    parent->right = u;
                }
                delete v;
                u->parent = parent;
                if (uvBlack)
                {
                    // u and v both black, fix double black at u
                    fixDoubleBlack(u);
                }
                else
                {
                    // u or v red, color u black
                    u->color = BLACK;
                }
            }
            return;
        }

        // v has 2 children, swap values with successor and recurse
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node *x)
    {
        if (x == root)
            // Reached root
            return;

        Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == NULL)
        {
            // No sibling, double black pushed up
            fixDoubleBlack(parent);
        }
        else
        {
            if (sibling->color == RED)
            {
                // Sibling red
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft())
                {
                    // left case
                    rightRotate(parent);
                }
                else
                {
                    // right case
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {
                // Sibling black
                if (sibling->hasRedChild())
                {
                    // at least 1 red children
                    if (sibling->left != NULL && sibling->left->color == RED)
                    {
                        if (sibling->isOnLeft())
                        {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                }
                else
                {
                    // 2 black children
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }



    // prints inorder recursively
    void inorder(Node *x)
    {
        if (x == NULL)
            return;
        inorder(x->left);
        std::cout << x->getVal() << " ";
        inorder(x->right);
    }
   



public:
    // constructor
    // initialize root
    RBTree() { root = NULL; }

    Node *getRoot() { return root; }

    // searches for given value
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node *search(int n)
    {
        Node *temp = root;
        while (temp != NULL)
        {
            if (n < temp->getVal())
            {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->getVal())
            {
                break;
            }
            else
            {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    // inserts the given value to tree
    void insert(float n)
    {
        Node *newNode = new Node(n);
        if (root == NULL)
        {
            // when root is null
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            Node *temp = search(n);

            if (temp->getVal() == n)
            {
                // return if value already exists
                return;
            }

            // if value is not found, search returns the node
            // where the value is to be inserted

            // connect new node to correct node
            newNode->parent = temp;

            if (n < temp->getVal())
                temp->left = newNode;
            else
                temp->right = newNode;

            // fix red red violation if exists
            fixRedRed(newNode);
        }
    }

    void insert(Vertex *newPoint) //Goal: remove the current arc at this point replacing it with 3 new arcs 
    {
        Node *newNode = new Node();
        if (root == NULL)
        {
            // when root is null
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            Node *temp = search(newPoint->x);

            if (temp->getVal() == newPoint->x)
            {
                // TODO: I believe this is one of the edge cases where the new arc lands on an intersection point, will fix later
                return;
            }

            // if value is found, check if it is the left breakpoint or the right breakpoint
            if (newPoint->x < temp->getVal()){// right breakpoint
                //need to also get the next left arc
                Node *nLeft = temp->nextLeft();
                Node *nRight = temp; // for readability

                //replace nLeft right arc with newPoint
                nLeft->rightarc = newPoint;
                //replace nRight left arc with newPoint
                nRight->leftarc = newPoint;


                //create the new arcs
                //going left and going right 


            }
            else{ //left breakpoint
                //need to also get the next right arc
                Node *nLeft = temp; // for readability
                Node *nRight = temp->nextRight();
                
            }

            // fix red red violation if exists
            fixRedRed(newNode);
        }
    }

    void insert(Vertex *newPoint, float leftmostX) //special case, used to insert the first arc into the beach line
    {
        Node *newNode = new Node();
        if (root == NULL)
        {
            // when root is null
            // simply insert value at root
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            Node *temp = search(n);

            if (temp->getVal() == n)
            {
                // return if value already exists
                return;
            }

            // if value is not found, search returns the node
            // where the value is to be inserted

            // connect new node to correct node
            newNode->parent = temp;

            if (n < temp->getVal())
                temp->left = newNode;
            else
                temp->right = newNode;

            // fix red red violation if exists
            fixRedRed(newNode);
        }
    }

    // utility function that deletes the node with given value
    void deleteByVal(int n)
    {
        if (root == NULL)
            // Tree is empty
            return;

        Node *v = search(n), *u;

        u = u;

        if (v->getVal() != n)
        {
            std::cout << "No node found to delete with value:" << n << std::endl;
            return;
        }

        deleteNode(v);
    }

    // prints inorder of the tree
    void printInOrder()
    {
        std::cout << "Inorder: " << std::endl;
        if (root == NULL)
            std::cout << "Tree is empty" << std::endl;
        else
            inorder(root);
        std::cout << std::endl;
    }

         //print the tree in latex forest format
    void forest(Node *x){
        if (x == NULL){
            std::cout << "[" << "null" << "]" << std::endl;
            return;
        }
        std::cout << "[" << x->getVal() << ":" << (x->color == RED ? "red" : "black");
        forest(x->left);
        forest(x->right);
        std::cout << "]" << std::endl;

    }
    

};


#endif