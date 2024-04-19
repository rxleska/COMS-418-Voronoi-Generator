//header file for a balanced binary search tree (BBST) (lib/Beach_Line_BBST.cpp))
    // The BBST will be implemented as a RED-BLACK tree for simplicity and since we are focused on insertion and deletion not just searching (which would be better suited for AVL trees)
#ifndef BEACH_LINE_BBST_HPP
#define BEACH_LINE_BBST_HPP

#include "Beach_Line_Item.hpp"

class Beach_line_BBST{
    private: 
        Beach_Line_Item *root;
    public:
        Beach_line_BBST();
        Beach_line_BBST(Beach_Line_Item *root);
        Beach_Line_Item* getRoot();
        void setRoot(Beach_Line_Item *root);
        void insert(Beach_Line_Item *item);
        void remove(Beach_Line_Item *item);
        Beach_Line_Item* search(Beach_Line_Item *item);
        Beach_Line_Item* search(double x);
        void printForestViewLatex(Beach_Line_Item *item); //gives the tree as an output readable by latex forest package
        
};

#endif // BEACH_LINE_BBST_HPP