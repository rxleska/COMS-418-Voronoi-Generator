#include "headers/Beach_Line_RedBlackTree.hpp"
#include <iostream>


// ------------------------------------------------------------
// -------------------------- Arc -----------------------------
// ------------------------------------------------------------

Arc::Arc(){
    focus = Vertex();
    id = -1;
}

Arc::Arc(Vertex f, int i){
    focus = f;
    id = i;
}

// ------------------------------------------------------------
// ----------------------- HalfLine ---------------------------
// ------------------------------------------------------------

HalfLine::HalfLine(){
    start = Vertex();
    end = Vertex();
    pointsUp = false;
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
    else if(this->edge.pointsUp){
        throw "Edge is not downwards, cannot get edge value";
    }
    else{
        //calculate where the line intersects the sweep line 
        double slToStart = sweepLine - this->edge.start.y;
        double scaling = slToStart / (this->edge.end.y - this->edge.start.y);
        double xValue = this->edge.start.x + (scaling * (this->edge.end.x - this->edge.start.x));
        return xValue;
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

    // initialize parent, grandparent, uncle
    Node *parent = x->parent, *grandparent = parent->parent,
            *uncle = x->uncle();

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
                if(temp->edge.pointsUp){
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
                            temp = temp->parent->right;
                        }
                        else{
                            temp = temp->parent->left;
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

void BeachLineRedBlackTree::insert(Vertex v, std::priority_queue<Event, std::vector<Event>, Compare> *eventQueue){
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
    newEdgeRight->isArc = false;

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
    newEdgeRight->edge.end = Vertex(rightX, rightY);
    
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

    //delete the above node
    delete above;
    size+=4;

    //check for circle events
    checkCircleEvent(newArcLeft, eventQueue);
    checkCircleEvent(newArcRight, eventQueue);
    checkCircleEvent(newArcCenter, eventQueue);
}


void BeachLineRedBlackTree::checkCircleEvent(Node *x, std::priority_queue<Event, std::vector<Event>, Compare> *eventQueue){
    return;
}