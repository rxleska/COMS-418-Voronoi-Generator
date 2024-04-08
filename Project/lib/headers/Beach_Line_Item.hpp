// header file for a beach line item (lib/Beach_Line_Item.cpp)
#ifndef BEACH_LINE_ITEM_HPP
#define BEACH_LINE_ITEM_HPP

#include "vertex.hpp"

class Beach_Line_Item{
    private:
        int isLeaf; // 1 if leaf, 0 if internal node (isSite) 
        Vertex *point; // used if isLeaf is 1 (could combine with leftarc into one pointer but this is more readable)
        Vertex *leftarc; // used if isLeaf is 0
        Vertex *rightarc; // used if isLeaf is 0
        double x; // x-coordinate of the breakpoint
        Beach_Line_Item *left; // left child (used if isLeaf is 0)
        Beach_Line_Item *right; // right child (used if isLeaf is 0)
        Beach_Line_Item *parent; // parent of the node
        int isRed; // 1 if red, 0 if black (used for red-black tree balancing)
    public:
        Beach_Line_Item();
        Beach_Line_Item(Vertex *point);
        Beach_Line_Item(Vertex *point, Beach_Line_Item *parent);
        Beach_Line_Item(Vertex *leftarc, Vertex *rightarc);
        Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x);
        Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x, Beach_Line_Item *left, Beach_Line_Item *right);
        Beach_Line_Item(Vertex *leftarc, Vertex *rightarc, double x, Beach_Line_Item *left, Beach_Line_Item *right, Beach_Line_Item *parent);
        int getIsLeaf();
        Vertex* getPoint();
        Vertex* getLeftArc();
        Vertex* getRightArc();
        double getX();
        Beach_Line_Item* getLeft();
        Beach_Line_Item* getRight();
        Beach_Line_Item* getParent();
        int getIsRed();
        Beach_Line_Item* getUncle();
        void setIsLeaf(int isLeaf);
        void setPoint(Vertex *point);
        void setLeftArc(Vertex *leftarc);
        void setRightArc(Vertex *rightarc);
        void setX(double x);
        void setLeft(Beach_Line_Item *left);
        void setRight(Beach_Line_Item *right);
        void setParent(Beach_Line_Item *parent);
        void setIsRed(int isRed);
};

#endif // BEACH_LINE_ITEM_HPP