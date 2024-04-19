#include "headers/Beach_Line_RedBlackTree.hpp"


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
            if(temp->getEdgeValue() == x){
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


void BeachLineRedBlackTree::insert(Vertex v){
    //this is a specialized insert for the beach line
    //this will insert an arc into the beach line, edge creation will be handled in this function as well

    //if root is null, create a new node and insert it as root
    if(root == nullptr){
        Node *newNode = new Node();
        newNode->isArc = true;
        newNode->arc = Arc(v, v.id);
        newNode->color = BLACK;
        root = newNode;
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
    COLOR arcColor = above->color;

    //Assign left and right to use the same vertex as the arc above
    newArcLeft->isArc = true;
    newArcLeft->arc = Arc(above->arc.focus, above->arc.id);
    newArcRight->isArc = true;
    newArcRight->arc = Arc(above->arc.focus, above->arc.id);

    //Assign newArcCenter to the new vertex
    newArcCenter->isArc = true;
    newArcCenter->arc = Arc(v, v.id);   








}

