
#include "EdgeNode.hpp"

#ifndef BEACH_LINE_HPP
#define BEACH_LINE_HPP

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
        void insert(EdgeNode *node);
};
    


#endif // BEACH_LINE_HPP