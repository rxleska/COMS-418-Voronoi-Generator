#include "headers/Beach_Line_RedBlackTree.hpp"
#include <iostream>


// ------------------------------------------------------------
// -------------------------- Arc -----------------------------
// ------------------------------------------------------------

Arc::Arc(){
    focus = Vertex();
    id = -1;
    associatedCircleEvents = new Event[3];
}

Arc::Arc(Vertex f, int i){
    focus = f;
    id = i;
    associatedCircleEvents = new Event[3];
}

Arc::~Arc(){
    delete[] associatedCircleEvents;
}

Arc::Arc(const Arc& a){
    focus = a.focus;
    id = a.id;
    associatedCircleEvents = a.associatedCircleEvents;
}

Arc& Arc::operator=(const Arc& a){
    focus = a.focus;
    id = a.id;
    associatedCircleEvents = new Event[3];
    for(int i = 0; i < 3; i++){
        associatedCircleEvents[i] = a.associatedCircleEvents[i];
    }
    return *this;
}

// ------------------------------------------------------------
// ----------------------- HalfLine ---------------------------
// ------------------------------------------------------------

HalfLine::HalfLine(){
    start = Vertex();
    end = Vertex();
    pointsUp = true; //default to true
    leftArc = nullptr;
    rightArc = nullptr;
}

HalfLine::HalfLine(Vertex s, Vertex e, bool ex, Arc *l, Arc *r){
    start = s;
    end = e;
    pointsUp = ex;
    leftArc = l;
    rightArc = r;
}

HalfLine::HalfLine(const HalfLine& h){
    start = h.start;
    end = h.end;
    pointsUp = h.pointsUp;
    leftArc = h.leftArc;
    rightArc = h.rightArc;
}

HalfLine& HalfLine::operator=(const HalfLine& h){
    start = h.start;
    end = h.end;
    pointsUp = h.pointsUp;
    leftArc = h.leftArc;
    rightArc = h.rightArc;
    return *this;
}

// ------------------------------------------------------------
// -------------------------- Node ----------------------------
// ------------------------------------------------------------

Node::Node(){
    isArc = false;
    color = BLACK;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

Node::~Node(){

}

//these are public but for ease of reading they are here as functions
void Node::SetLeft(Node *n){
    left = n;
    if(n != nullptr){
        n->parent = this;
    }
}

void Node::SetRight(Node *n){
    right = n;
    if(n != nullptr){
        n->parent = this;
    }
}

void Node::SetParent(Node *n){
    parent = n;
}

Node *Node::uncle(){
    if(parent == nullptr || parent->parent == nullptr){
        return nullptr;
    }
    if(parent->isOnLeft()){
        return parent->parent->right;
    }else{
        return parent->parent->left;
    }
}

bool Node::isOnLeft(){
    //if root return false
    if(parent == nullptr){
        return false;
    }
    return this == parent->left;
}

Node *Node::sibling(){
    if(parent == nullptr){
        return nullptr;
    }
    if(isOnLeft()){
        return parent->right;
    }
    return parent->left;
}

void Node::moveDown(Node *nParent){
    if(parent != nullptr){
        if(isOnLeft()){
            parent->left = nParent;
        }else{
            parent->right = nParent;
        }
    }
    nParent->parent = parent;
    parent = nParent;
}

bool Node::hasRedChild(){
    return (left != nullptr && left->color == RED) || (right != nullptr && right->color == RED);
}

double Node::getEdgeValue(){ //assumes that the node has been checked to be an edge
    if(this->isArc){
        throw "Node is not an edge, cannot get edge value";
    }
    else{
        double leftinterceptX;
        double rightinterceptX;
        BeachLineRedBlackTree::getParabolaSides(this->edge.leftArc->focus.x, this->edge.rightArc->focus.x, this->edge.leftArc->focus.y, this->edge.rightArc->focus.y, sweepLine, &leftinterceptX, &rightinterceptX);

        // if(DEBUG) std::cout << "sweep" << sweepLine << std::endl;
        // if(DEBUG) std::cout << "leftFocus" << this->edge.leftArc->focus.x << " " << this->edge.leftArc->focus.y << " rightFocus: " << this->edge.rightArc->focus.x << " " << this->edge.rightArc->focus.y << std::endl;
        // if(DEBUG) std::cout << "edgevalue: left: " << leftinterceptX << " right: " << rightinterceptX << std::endl;
        // if(DEBUG) std::cout << "edgevalue: left: " << leftinterceptX << " right: " << rightinterceptX << std::endl;

        if(this->edge.leftArc->focus.y < this->edge.rightArc->focus.y){ //left below right, get right intersection
            return rightinterceptX;
        }
        else{ //right below left, get left intersection
            return leftinterceptX;
        }
    }

}

// ------------------------------------------------------------
// -------------- Beach Line Red Black Tree -------------------
// ------------------------------------------------------------

BeachLineRedBlackTree::BeachLineRedBlackTree(){
    root = nullptr;
    size = 0;
    sweepLine = 0;
}

Node *BeachLineRedBlackTree::getRoot(){
    return root;
}

void BeachLineRedBlackTree::setRoot(Node *n){
    root = n;
}

void BeachLineRedBlackTree::rotateLeft(Node *x)
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
    if (nParent->left != nullptr)
        nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
}

void BeachLineRedBlackTree::rotateRight(Node *x)
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
    if (nParent->right != nullptr)
        nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
}

void BeachLineRedBlackTree::swapColors(Node *x1, Node *x2)
{
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

void BeachLineRedBlackTree::swapValues(Node *u, Node *v)
{
    //fill temp with u's values
    Node temp;
    if(u->isArc){
        temp.isArc = true;
        temp.arc = u->arc;
        temp.color = u->color;
    }
    else{
        temp.isArc = false;
        temp.edge = u->edge;
        temp.color = u->color;
    }

    //fill u with v's values
    if(v->isArc){
        u->isArc = true;
        u->arc = v->arc;
        u->color = v->color;
    }
    else{
        u->isArc = false;
        u->edge = v->edge;
        u->color = v->color;
    }

    //fill v with temp's values (u's values)
    if(temp.isArc){
        v->isArc = true;
        v->arc = temp.arc;
        v->color = temp.color;
    }
    else{
        v->isArc = false;
        v->edge = temp.edge;
        v->color = temp.color;
    }
}

void BeachLineRedBlackTree::fixDoubleBlack(Node *x)
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
                rotateRight(parent);
            }
            else
            {
                // right case
                rotateLeft(parent);
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
                        rotateRight(parent);
                    }
                    else
                    {
                        // right left
                        sibling->left->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                }
                else
                {
                    if (sibling->isOnLeft())
                    {
                        // left right
                        sibling->right->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    }
                    else
                    {
                        // right right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
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

void BeachLineRedBlackTree::fixRedRed(Node *x){
    // if x is root color it black and return
    if (x == root)
    {
        x->color = BLACK;
        return;
    }

    if(x->parent == nullptr){
        printTreeForest(root);
        if(DEBUG){
            if(x->isArc){
                std::cout << "Arc: " << x->arc.focus.x << " " << x->arc.focus.y << std::endl;
            }
            else{
                std::cout << "Edge: start: " << x->edge.start.x << " " << x->edge.start.y << " end: " << x->edge.end.x << " " << x->edge.end.y << std::endl;
            }
        }
    }


    // initialize parent, grandparent, uncle
    Node *parent = x->parent, *grandparent = parent->parent,
            *uncle = x->uncle();

    if(grandparent == nullptr){
        return;
        // if(DEBUG) std::cout << "node: " << x->edge.start.x << " " << x->edge.start.y << " " << x->edge.end.x << " " << x->edge.end.y << std::endl;
        // if(DEBUG) std::cout << "parent: " << parent->edge.start.x << " " << parent->edge.start.y << " " << parent->edge.end.x << " " << parent->edge.end.y << std::endl;
        // if(DEBUG) printTreeForest(root);
    }

    if (parent->color != BLACK)
    {
        if (uncle != nullptr && uncle->color == RED)
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
                    rotateLeft(parent);
                    swapColors(x, grandparent);
                }
                // for left left and left right
                rotateRight(grandparent);
            }
            else
            {
                if (x->isOnLeft())
                {
                    // for right left
                    rotateRight(parent);
                    swapColors(x, grandparent);
                }
                else
                {
                    swapColors(parent, grandparent);
                }

                // for right right and right left
                rotateLeft(grandparent);
            }
        }
    }
}

Node *BeachLineRedBlackTree::successor(Node *x){
    Node *temp = x;

    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

Node *BeachLineRedBlackTree::BSTreplace(Node *x){
    // when node have 2 children
    if (x->left != nullptr && x->right != nullptr)
        return successor(x->right);

    // when leaf
    if (x->left == nullptr && x->right == nullptr)
        return nullptr;

    // when single child
    if (x->left != nullptr)
        return x->left;
    else
        return x->right;
}

void BeachLineRedBlackTree::deleteNode(Node *v){
    Node *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
    Node *parent = v->parent;

    if (u == nullptr)
    {
        // u is NULL therefore v is leaf
        if (v == root)
        {
            // v is root, making root null
            root = nullptr;
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
                if (v->sibling() != nullptr)
                    // sibling is not null, make it red"
                    v->sibling()->color = RED;
            }

            // delete v from the tree
            if (v->isOnLeft())
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        delete v;
        this->size--;
        return;
    }

    if (v->left == nullptr || v->right == nullptr)
    {
        // v has 1 child
        if (v == root)
        {
            // v is root, assign the value of u to v, and delete u
            swapValues(v, u);
            // v->val = u->val; // this is from when the code evaulated with a value
            v->left = v->right = nullptr;
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

Node *BeachLineRedBlackTree::search(double x){ //returns an arc, shouldn't return an edge, TODO add degenerate case check in insert
    Node *temp = root;
    while(temp != nullptr){
        if(temp->isArc){
            return temp;
        }
        else{
                if(false && temp->edge.pointsUp){
                    //if temp is root only one side should be valid, if so return that side
                    if(temp->parent == nullptr){
                        if(temp->left != nullptr){
                            temp = temp->left;
                        }
                        else{
                            temp = temp->right;
                        }
                    
                    }else{
                        //if right child of parent return left, else return right
                        if(temp->isOnLeft()){
                            if(DEBUG) std::cout << "Edge: start:" << temp->edge.start.x << " " << temp->edge.start.y << " end: " << temp->edge.end.x << " " << temp->edge.end.y << std::endl;
                            if(DEBUG) printTreeForest(root);
                            throw "Error: Edge is pointing up, should not be in the tree";
                            // temp = temp->parent->right;
                        }
                        else{
                            if(DEBUG) std::cout << "Edge: start:" << temp->edge.start.x << " " << temp->edge.start.y << " end: " << temp->edge.end.x << " " << temp->edge.end.y << std::endl;
                            if(DEBUG) printTreeForest(root);
                            throw "Error: Edge is pointing up, should not be in the tree";
                            // temp = temp->parent->left;
                        }
                    }

                }
                else if(temp->getEdgeValue() == x){
                    return temp;
                }
                else if(temp->getEdgeValue() < x){
                    temp = temp->right;
                }
                else{
                    temp = temp->left;
                }
            
        }
    }
    return nullptr;
}

void BeachLineRedBlackTree::getParabolaSides(double x1, double x2, double y1, double y2, double sweep, double *left, double *right){
    //Check if points are colinear parallel to the x axis and if so return no intersection
    if(y1 == y2){
        // std::cout << "no intersection" << std::endl;
        left = nullptr;
        right = nullptr;
        return;
    }

    //if one point is touching the sweep line
    if(y1 == sweep){
        *left = x1;
        *right = x1;
        return;
    }
    if(y2 == sweep){
        *left = x2;
        *right = x2;
        return;
    }


    double a = 1.0 / (y1-sweep) - 1.0 / (y2-sweep);
    double b  = -2.0 * x1/(y1-sweep) + 2.0 * x2/(y2-sweep);
    double c = x1*x1/(y1-sweep) - x2*x2/(y2-sweep) + y1 - y2;

    // std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;

    // test for no intersection
    if(b*b - 4*a*c < 0){
        // std::cout << "no intersection" << std::endl;
        left = nullptr;
        right = nullptr;
        return;
    }

    //else calculate the intersections 
    double xIntersection1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
    double xIntersection2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
    if(xIntersection1 < xIntersection2){
        *left = xIntersection1;
        *right = xIntersection2;
    }else{
        *left = xIntersection2;
        *right = xIntersection1;
    }
    return;
}

double BeachLineRedBlackTree::getParabolaYAtX(double xf, double yf, double ysweep, double x){ //gets the y value of a parabola at a given x value
    return (x-xf)*(x-xf)/(2*(yf-ysweep)) + 0.5*(yf+ysweep);

}

void BeachLineRedBlackTree::insert(Vertex v, std::vector<Event> *eventQueue){
    //this is a specialized insert for the beach line
    //this will insert an arc into the beach line, edge creation will be handled in this function as well

    //if root is null, create a new node and insert it as root
    if(root == nullptr){
        Node *newNode = new Node();
        newNode->isArc = true;
        newNode->arc = Arc(v, v.id);
        newNode->color = BLACK;
        root = newNode;
        size = 1;
        return;
    }



    //search the tree for the arc that is above the point
    Node *above = search(v.x);

    //sanity check that it is an arc
    if(above == nullptr){
        throw "Error: The node above the point is undefined";
    }
    if(!above->isArc){ //TODO Replace with new edge on each intersection degenerate case
        throw "Error: The node above the point is not an arc";
    }

    //Remove the arc above the point, replace it the new arc the 2 split arcs and the new edges from the split
    Node *newArcLeft = new Node();
    Node *newArcCenter = new Node();
    Node *newArcRight = new Node();
    Node *newEdgeLeft = new Node();
    Node *newEdgeRight = new Node();

    //from this point forward we know that above is an arc
    // COLOR arcColor = above->color;

    //Assign left and right to use the same vertex as the arc above
    newArcLeft->isArc = true;
    newArcLeft->arc = Arc(above->arc.focus, above->arc.id);
    newArcRight->isArc = true;
    newArcRight->arc = Arc(above->arc.focus, above->arc.id);

    //Assign newArcCenter to the new vertex
    newArcCenter->isArc = true;
    newArcCenter->arc = Arc(v, v.id);   

    //
    newEdgeLeft->isArc = false;
    newEdgeLeft->edge.leftArc = &newArcLeft->arc;
    newEdgeLeft->edge.rightArc = &newArcCenter->arc;
    newEdgeRight->isArc = false;
    newEdgeRight->edge.leftArc = &newArcCenter->arc;
    newEdgeRight->edge.rightArc = &newArcRight->arc;

    //Calculate the new edges half edges
    //Note arc can be found using the following formula y = (x-xFocus)^2/(2(yFocus-ySweep)) + 0.5*(yfocus + ySweep)
    //same starting point (point on the arc at the given x for the previous arcs focus point the current sweep line y)
    double sharedx = v.x;
    double sharedy = (sharedx - above->arc.focus.x)*(sharedx - above->arc.focus.x)/(2*(above->arc.focus.y - sweepLine)) + 0.5*(above->arc.focus.y + sweepLine);
    Vertex shared(sharedx, sharedy);
    newEdgeLeft->edge.start = shared;
    newEdgeRight->edge.start = shared;

    //calculate a the left intersection after 5 (arbitrary) units 
    //derived this formula on paper and then implemented it here
    double sweepApprox = sweepLine - 1;
    double leftX;
    double rightX;
    getParabolaSides(above->arc.focus.x, v.x, above->arc.focus.y, v.y, sweepApprox, &leftX, &rightX);
    double leftY = getParabolaYAtX(above->arc.focus.x, above->arc.focus.y, sweepApprox, leftX);
    double rightY = getParabolaYAtX(above->arc.focus.x, above->arc.focus.y, sweepApprox, rightX);
    newEdgeLeft->edge.end = Vertex(leftX, leftY);  
    //Debug write the edge
    if(DEBUG) std::cout << "Edge start: (" << newEdgeLeft->edge.start.x << ", " << newEdgeLeft->edge.start.y << ") end: (" << newEdgeLeft->edge.end.x << ", " << newEdgeLeft->edge.end.y << ")" << "quadtuple: (" << newEdgeLeft->edge.start.x << ", " << newEdgeLeft->edge.start.y << ", " << newEdgeLeft->edge.end.x << ", " << newEdgeLeft->edge.end.y << ")" << std::endl;
    newEdgeRight->edge.end = Vertex(rightX, rightY);
    //Debug write the edge
    if(DEBUG) std::cout << "Edge start: (" << newEdgeRight->edge.start.x << ", " << newEdgeRight->edge.start.y << ") end: (" << newEdgeRight->edge.end.x << ", " << newEdgeRight->edge.end.y << ")" << "quadtuple: (" << newEdgeRight->edge.start.x << ", " << newEdgeRight->edge.start.y << ", " << newEdgeRight->edge.end.x << ", " << newEdgeRight->edge.end.y << ")" << std::endl;
    
    //test if either edge points up 
    if(newEdgeLeft->edge.start.y < newEdgeLeft->edge.end.y){
        if(DEBUG) std::cout << "Edge points up: start: (" << newEdgeLeft->edge.start.x << ", " << newEdgeLeft->edge.start.y << ") end: (" << newEdgeLeft->edge.end.x << ", " << newEdgeLeft->edge.end.y << ")" << std::endl;
        newEdgeLeft->edge.pointsUp = true;
    }
    if(newEdgeRight->edge.start.y < newEdgeRight->edge.end.y){
        if(DEBUG) std::cout << "Edge points up: start: (" << newEdgeRight->edge.start.x << ", " << newEdgeRight->edge.start.y << ") end: (" << newEdgeRight->edge.end.x << ", " << newEdgeRight->edge.end.y << ")" << std::endl;
        newEdgeRight->edge.pointsUp = true;
    }
    if(DEBUG) std::cout << "Edge start: (" << newEdgeLeft->edge.start.x << ", " << newEdgeLeft->edge.start.y << ") end: (" << newEdgeLeft->edge.end.x << ", " << newEdgeLeft->edge.end.y << ")" << std::endl;
    


    //if node being replace is left of its parent
    // place this tree [rightEdge [leftEdge newArcLeft newArcCenter] newArcRight]
    if(above->parent == nullptr && above != root){ throw "found node with null parent that is not the root, during insert";}
    else if(above->parent == nullptr){
        //this implies that the above node is the root, and therefore we don't need to worry about the parent
        root = newEdgeRight;

        newEdgeRight->SetLeft(newEdgeLeft);
        newEdgeRight->SetRight(newArcRight);
        newEdgeRight->color = RED;
        
        //left
        newEdgeLeft->SetLeft(newArcLeft);
        newEdgeLeft->SetRight(newArcCenter);
        newEdgeLeft->SetParent(newEdgeRight);
        newEdgeLeft->color = BLACK;

        //right
        newArcRight->SetParent(newEdgeRight);
        newArcRight->color = BLACK;

        //left left
        newArcLeft->SetParent(newEdgeLeft);
        newArcLeft->color = RED;

        //left right
        newArcCenter->SetParent(newEdgeLeft);      
        newArcCenter->color = RED;  

    }
    else if(above->isOnLeft()){
        Node *parent = above->parent;
        parent->SetLeft(newEdgeRight);

        //top
        newEdgeRight->SetLeft(newEdgeLeft);
        newEdgeRight->SetRight(newArcRight);
        newEdgeRight->SetParent(parent);
        newEdgeRight->color = RED;
        
        //left
        newEdgeLeft->SetLeft(newArcLeft);
        newEdgeLeft->SetRight(newArcCenter);
        newEdgeLeft->SetParent(newEdgeRight);
        newEdgeLeft->color = BLACK;

        //right
        newArcRight->SetParent(newEdgeRight);
        newArcRight->color = BLACK;

        //left left
        newArcLeft->SetParent(newEdgeLeft);
        newArcLeft->color = RED;

        //left right
        newArcCenter->SetParent(newEdgeLeft);      
        newArcCenter->color = RED;  

        fixRedRed(newEdgeRight);
    }
    else{ //place this tree [leftEdge newArcLeft [rightEdge  newArcCenter newArcRight]]
        Node *parent = above->parent;
        parent->SetRight(newEdgeLeft);

        //top
        newEdgeLeft->SetRight(newEdgeRight);
        newEdgeLeft->SetLeft(newArcLeft);
        newEdgeLeft->SetParent(parent);
        newEdgeLeft->color = RED;

        //left
        newArcLeft->SetParent(newEdgeLeft);
        newArcLeft->color = BLACK;

        //right
        newEdgeRight->SetLeft(newArcCenter);
        newEdgeRight->SetRight(newArcRight);
        newEdgeRight->SetParent(newEdgeLeft);
        newEdgeRight->color = BLACK;

        //right left
        newArcCenter->SetParent(newEdgeRight);
        newArcCenter->color = RED;

        //right right
        newArcRight->SetParent(newEdgeRight);
        newArcRight->color = RED;

        fixRedRed(newEdgeLeft);
    }

    //remove any circle events associated with the above node from the event queue
    for(int i = 0; i < 3; i++){
        if(above->arc.associatedCircleEvents[i].getPoint() != nullptr){
            //remove the event from the event queue
            for(std::vector<Event>::iterator it = eventQueue->begin(); it != eventQueue->end(); ++it){
                if(it->getPoint() == above->arc.associatedCircleEvents[i].getPoint()){
                    eventQueue->erase(it);
                    break;
                }
            }
        }
    }
    //heapify the event queue
    //TODO: check if this is necessary
    std::make_heap(eventQueue->begin(), eventQueue->end(), Compare());

    //delete the above node
    delete above;
    size+=4;

    //check for circle events
    checkCircleEvent(newArcLeft, eventQueue);
    checkCircleEvent(newArcRight, eventQueue);
    checkCircleEvent(newArcCenter, eventQueue);

}


void BeachLineRedBlackTree::checkCircleEvent(Node *x, std::vector<Event> *eventQueue){
    //check if the node x has a left and right arcs

    if(x->parent == nullptr){
        return;
    }

    Node *leftArc = x;
    Node *rightArc = x;
    Node * leftEdge;
    Node * rightEdge;
    //find the left and right arcs //if at any point we discover we cannot get either of these we return, since there would be no circle event
    //if left of parent
    if(x->isOnLeft()){ //parent is up to the right of x
        //left
        //find the first parent that is right of its parent
        while(leftArc->parent != nullptr && leftArc->isOnLeft()){
            leftArc = leftArc->parent;
        }
        if(leftArc->parent == nullptr){
            return; //no circle event
        }
        leftArc = leftArc->parent;
        leftEdge = leftArc;
        leftArc = leftArc->left;
        if(leftArc == nullptr){
            return; //no circle event //this generally shouldn't happen since the tree should be complete
        }
        //get the right most child of the left arc
        while(leftArc->right != nullptr){
            leftArc = leftArc->right;
        }
        if(!leftArc->isArc){
            return; //no circle event //this generally shouldn't happen since a leaf should be an arc
        }

        //right
        rightArc = x->parent;
        if(rightArc == nullptr){
            return; //no circle event
        }
        rightEdge = rightArc;
        rightArc = rightArc->right;
        if(rightArc == nullptr){
            return; //no circle event //this generally shouldn't happen since the tree should be complete
        }
        //get the left most child of the right arc
        while(rightArc->left != nullptr){
            rightArc = rightArc->left;
        }
        if(!rightArc->isArc){
            return; //no circle event //this generally shouldn't happen since a leaf should be an arc
        }

        
    }
    else{ //parent is up to the left of x
        //left
        leftArc = x->parent;
        if(leftArc == nullptr){
            return; //no circle event
        }
        leftEdge = leftArc;
        leftArc = leftArc->left;
        if(leftArc == nullptr){
            return; //no circle event //this generally shouldn't happen since the tree should be complete
        }
        //get the right most child of the left arc
        while(leftArc->right != nullptr){
            leftArc = leftArc->right;
        }
        if(!leftArc->isArc){
            return; //no circle event //this generally shouldn't happen since a leaf should be an arc
        }

        //right
        //find the first parent that is left of its parent
        while(rightArc->parent != nullptr && !rightArc->isOnLeft()){
            rightArc = rightArc->parent;
        }
        if(rightArc->parent == nullptr){
            return; //no circle event
        }
        rightArc = rightArc->parent;
        rightEdge = rightArc;
        rightArc = rightArc->right;
        if(rightArc == nullptr){
            return; //no circle event //this generally shouldn't happen since the tree should be complete
        }
        //get the left most child of the right arc
        while(rightArc->left != nullptr){
            rightArc = rightArc->left;
        }
        if(!rightArc->isArc){
            return; //no circle event //this generally shouldn't happen since a leaf should be an arc
        }
    }
    //if we made it this far, we have the left and right arcs

    //let Apt, Bpt, Cpt be the points defining the arcs left, x, and right respectively
    Vertex Apt = leftArc->arc.focus;
    Vertex Bpt = x->arc.focus;
    Vertex Cpt = rightArc->arc.focus;

    //apt and cpt should not be the same check for this
    if(Apt.x == Cpt.x && Apt.y == Cpt.y){
        return;
    }

    //find the circumcenter of the circle defined by these 3 points

    //find the slope of Apt to Bpt
    double mAB = (Apt.y - Bpt.y) / (Apt.x - Bpt.x);
    //find the center point of the line between Apt and Bpt
    Vertex midAB = Vertex((Apt.x + Bpt.x) / 2, (Apt.y + Bpt.y) / 2);
    double mPerpAB = -1.0 / mAB;
    //find the y intercept of a line perpendicular to AB that goes through midAB
    double bPerpAB = midAB.y - mPerpAB * midAB.x;

    //find the slope of Bpt to Cpt
    double mBC = (Bpt.y - Cpt.y) / (Bpt.x - Cpt.x);
    //find the center point of the line between Bpt and Cpt
    Vertex midBC = Vertex((Bpt.x + Cpt.x) / 2, (Bpt.y + Cpt.y) / 2);
    double mPerpBC = -1.0 / mBC;
    //find the y intercept of a line perpendicular to BC that goes through midBC
    double bPerpBC = midBC.y - mPerpBC * midBC.x;

    //find the intersection of the two lines 
    double circumcenterX = (bPerpBC - bPerpAB) / (mPerpAB - mPerpBC);
    double circumcenterY = mPerpAB * circumcenterX + bPerpAB;

    //find the distance between the circumcenter and any of the points //its the same for all 3 points
    double radius = sqrt((Apt.x - circumcenterX)*(Apt.x - circumcenterX) + (Apt.y - circumcenterY)*(Apt.y - circumcenterY));

    //if event already exists return
    for(int i = 0; i < 3; i++){
        if(x->arc.associatedCircleEvents[i].getPoint() != nullptr && x->arc.associatedCircleEvents[i].getPoint()->x == circumcenterX && x->arc.associatedCircleEvents[i].getPoint()->y == circumcenterY){
            return;
        }
    }

    //check if the bottom of the circle is below the sweep line 
    if(circumcenterY - radius > sweepLine){ //note using - since we are sweeping from top to bottom
        return;
    } //TODO check if its an edge case where the circle touches the sweep line
    else{
        //add the circle event to the event queue
        Vertex *circleCenter = new Vertex(circumcenterX, circumcenterY-radius);
        Event circleEvent = Event(circleCenter, leftArc, leftEdge, x, rightEdge, rightArc);
        eventQueue->push_back(circleEvent);
        leftArc->arc.associatedCircleEvents[2] = circleEvent;
        x->arc.associatedCircleEvents[1] = circleEvent;
        rightArc->arc.associatedCircleEvents[0] = circleEvent;
        std::push_heap(eventQueue->begin(), eventQueue->end(), Compare());

        if(DEBUG) std::cout << "Circle event added: (" << circumcenterX << ", " << circumcenterY << ")" << " on points: (" << Apt.x << ", " << Apt.y << ") (" << Bpt.x << ", " << Bpt.y << ") (" << Cpt.x << ", " << Cpt.y << ")" << std::endl;
    }

    return;
}

void BeachLineRedBlackTree::handleCircleEvent(Event *e, std::vector<Event> *eventQueue){
    //sanity check that the event is a circle event
    if(e->getType() != 1){
        throw "Error: Event is not a circle event";
    }

    CircleEvent *ce = e->getCircleEvent();

    if(ce == nullptr){
        throw "Error: Circle event is null";
    }
    Node* leftArc = ce->leftArc;
    Node* leftEdge = ce->leftEdge;
    Node* centerArc = ce->pinchingArc;
    Node* rightEdge = ce->rightEdge;
    Node* rightArc = ce->rightArc;


    //calculate a new edge from the left arc to the right arc
    
    //get the parabola intersections
    double startLeftX = 0.0;
    double startRightX = 0.0;
    getParabolaSides(leftArc->arc.focus.x, rightArc->arc.focus.x, leftArc->arc.focus.y, rightArc->arc.focus.y, sweepLine, &startLeftX, &startRightX);

    //select the proper intersection
    double startX = 0.0;
    if(leftArc->arc.focus.y > rightArc->arc.focus.y){
        startX = startRightX;
    }
    else{
        startX = startLeftX;
    }

    double startY = getParabolaYAtX(leftArc->arc.focus.x, leftArc->arc.focus.y, sweepLine, startX);

    double endLeftX = 0.0;
    double endRightX = 0.0;
    getParabolaSides(leftArc->arc.focus.x, rightArc->arc.focus.x, leftArc->arc.focus.y, rightArc->arc.focus.y, sweepLine+5, &endLeftX, &endRightX);

    //select the proper intersection
    double endX = 0.0;
    if(leftArc->arc.focus.y < rightArc->arc.focus.y){
        endX = endRightX;
    }
    else{
        endX = endLeftX;
    }

    double endY = getParabolaYAtX(leftArc->arc.focus.x, leftArc->arc.focus.y, sweepLine+5, endX);

    //LOG the 2 side arcs and log the sweep line height
    // std::cout << "Left arc:" << leftArc->arc.focus.x << " " << leftArc->arc.focus.y << std::endl;
    // std::cout << "Right arc:" << rightArc->arc.focus.x << " " << rightArc->arc.focus.y << std::endl;
    std::cout << "Sweep line: " << sweepLine << std::endl;
    std::cout << "Start: (" << startX << ", " << startY << ")" << std::endl;
    std::cout << "arcs: " << leftArc->arc.focus.x << " " << leftArc->arc.focus.y << " " << rightArc->arc.focus.x << " " << rightArc->arc.focus.y << std::endl;

    //test if it points up
    bool pointsUp = endY > startY; //this really shouldn't happen

    //create edge 
    Node *newEdge = new Node();
    newEdge->isArc = false;
    newEdge->edge.start = Vertex(startX, startY);
    newEdge->edge.end = Vertex(endX, endY);
    newEdge->edge.leftArc = &leftArc->arc;
    newEdge->edge.rightArc = &rightArc->arc;
    newEdge->edge.pointsUp = pointsUp;


    //TODO ADD the edges to the DCEL
    
    //discover which edge should be replaced, 
    Node *edgeToReplace = centerArc;
    while(edgeToReplace != leftEdge && edgeToReplace != rightEdge && edgeToReplace != nullptr){
        edgeToReplace = edgeToReplace->parent;
    } 
    if(edgeToReplace == nullptr){
        throw "Error: Edge to replace is null";
    }

    //delete the center arc
    deleteNode(centerArc);

    if(PRINTEDGE){
            std::cout << std::endl;
            std::cout << "Edge End: start: (" << leftEdge->edge.start.x << ", " << leftEdge->edge.start.y << ", " << getParabolaYAtX(leftEdge->edge.leftArc->focus.x, leftEdge->edge.leftArc->focus.y, sweepLine, leftEdge->getEdgeValue()) << ", " << leftEdge->getEdgeValue() << ")" << std::endl;
            std::cout << "Edge End: start: (" << rightEdge->edge.start.x << ", " << rightEdge->edge.start.y << ", " << getParabolaYAtX(rightEdge->edge.leftArc->focus.x, rightEdge->edge.leftArc->focus.y, sweepLine, rightEdge->getEdgeValue()) << ", " << rightEdge->getEdgeValue() << ")" << std::endl;
            std::cout << std::endl;
    }


    if(edgeToReplace == leftEdge){
        //replace right edge // sounds weird but we want the edge is not connected to the center to be replaced
        deleteNode(leftEdge);
         edgeToReplace = rightEdge;
    }
    else{
        //replace left edge
        deleteNode(rightEdge);
        edgeToReplace = leftEdge;
    }

    Node * edgeToReplaceLeft = edgeToReplace->left;
    Node * edgeToReplaceRight = edgeToReplace->right;
    COLOR edgeColor = edgeToReplace->color;

    if(root == edgeToReplace){
        root = newEdge;
    }
    else{
        newEdge->parent = edgeToReplace->parent;
        if(edgeToReplace->isOnLeft()){
            edgeToReplace->parent->SetLeft(newEdge);
        }
        else{
            edgeToReplace->parent->SetRight(newEdge);
        }

    }
    newEdge->SetLeft(edgeToReplaceLeft);
    newEdge->SetRight(edgeToReplaceRight);

    //set the parent of the children
    if(edgeToReplaceLeft != nullptr){
        edgeToReplaceLeft->SetParent(newEdge);
    }
    if(edgeToReplaceRight != nullptr){
        edgeToReplaceRight->SetParent(newEdge);
    }

    newEdge->color = edgeColor;

    //TODO remove the circle events associated with the center arc
    for(int i = 0; i < 3; i++){
        if(centerArc->arc.associatedCircleEvents[i].getPoint() != nullptr){
            //remove the event from the event queue
            for(std::vector<Event>::iterator it = eventQueue->begin(); it != eventQueue->end(); ++it){
                // Should not compare points directly, since the points could be the same but have different addresses
                // if(it->getPoint() == centerArc->arc.associatedCircleEvents[i].getPoint()){
                //     eventQueue->erase(it);
                //     break;
                // }
                if(it->getPoint()->x == centerArc->arc.associatedCircleEvents[i].getPoint()->x && it->getPoint()->y == centerArc->arc.associatedCircleEvents[i].getPoint()->y && it->getType() == 1){
                    eventQueue->erase(it);
                    break;
                }
            }
        }
    }


    //test for new circle events and add them to the event queue
    checkCircleEvent(edgeToReplaceLeft, eventQueue);
    checkCircleEvent(edgeToReplaceRight, eventQueue);
}


void BeachLineRedBlackTree::printTreeForest(Node *root){
    if(root == nullptr){
        return;
    }
    if(root->isArc){
        std::cout << "[\\textbf{Arc: " << root->arc.focus.x << ", " << root->arc.focus.y << "}" << std::endl;
    }
    else{
        std::cout << "[\\textbf{Edge: start: " << root->edge.start.x << ", " << root->edge.start.y << " end: " << root->edge.end.x << ", " << root->edge.end.y << "}" << std::endl;
    }
    printTreeForest(root->left);
    printTreeForest(root->right);
    std::cout << "]" << std::endl;
}