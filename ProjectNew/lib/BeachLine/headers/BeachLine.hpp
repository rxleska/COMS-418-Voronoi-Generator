

#ifndef BEACH_LINE_HPP
#define BEACH_LINE_HPP

#include "EdgeNode.hpp"
#include "../../CONST.hpp"
#include "../../DCEL/headers/Vertex.hpp"

class EdgeNode; //forward declaration

class BeachLine {
    private:
        EdgeNode *root;
        double sweepLine;
    public:
        //constructors
        BeachLine();
        BeachLine(double sweepLine);

        //getters and setters
        EdgeNode *getRoot();
        void setRoot(EdgeNode *root);
        double getSweepLine();
        void setSweepLine(double sweepLine);

        //tree functions
        void rightRotate(EdgeNode *node);
        void leftRotate(EdgeNode *node);
        void splay(EdgeNode *node);
        EdgeNode *search(double searchX);
        EdgeNode *search(double searchX, double altSweepline);
        void insert(EdgeNode *node);
        void remove(EdgeNode *node);

        //beach line specific functions
        void checkCircleEvent(EdgeNode *leftedge, EdgeNode *rightedge);
        bool circleIntersectsBeachLine(Vertex Apt, Vertex Bpt, Vertex Cpt, double *x, double *y, double *r);
        EdgeNode * getNextLeftEdge(EdgeNode *node);
        EdgeNode * getNextRightEdge(EdgeNode *node);

        void printTree(EdgeNode * node);
        void printTree(EdgeNode * node, double altSweepline);
};
    


#endif // BEACH_LINE_HPP