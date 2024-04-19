// Header file for the BeachLineRedBlackTree class (lib/Beach_Line_RedBlackTree.cpp)
#include "Vertex.hpp"

#ifndef BEACH_LINE_RBT
#define BEACH_LINE_RBT

static double sweepLine = 0.0;

enum BeachLineNodeType
{
    None, //used to confirm the value has been set
    VERTEX,
    HALF_LINE
};

enum COLOR
{
    RED,
    BLACK
};

class Arc{
    public:
    Vertex focus;
    int id;
    Arc();
    Arc(Vertex f, int i);
};

class HalfLine{
    public:
    Vertex start;
    Vertex end; //this is not to imply that this is a line segment, it is a half line but defined by a start and end point
    bool pointsUp;
    Arc *leftArc;
    Arc *rightArc;
    HalfLine();
    HalfLine(Vertex s, Vertex e, bool ex, Arc *l, Arc *r);
};


class Node{
    public:
    union {
        Arc arc;
        HalfLine edge;
    };
    bool isArc;
    COLOR color;
    Node *left, *right, *parent;
    Node();
    void SetLeft(Node *n);
    void SetRight(Node *n);
    void SetParent(Node *n);
    Node *uncle();
    bool isOnLeft();
    Node *sibling();
    void moveDown(Node *nParent);
    bool hasRedChild();
    double getEdgeValue();
};


class BeachLineRedBlackTree{
    private:
        Node *root;
    public:
        int size;
        BeachLineRedBlackTree();
        Node *getRoot();
        void setRoot(Node *n);
        void rotateLeft(Node *x);
        void rotateRight(Node *x);
        void swapColors(Node *x1, Node *x2);
        void swapValues(Node *u, Node *v);
        void fixRedRed(Node *x);
        Node *successor(Node *x);
        Node *BSTreplace(Node *x);
        void deleteNode(Node *v);
        void fixDoubleBlack(Node *x);
        Node *search(double x); //returns an edge
        void insert(Vertex v); //this is a specialized insert for the beach line
};

#endif 