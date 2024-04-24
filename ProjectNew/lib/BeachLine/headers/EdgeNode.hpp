

#ifndef EDGE_NODE_HPP
#define EDGE_NODE_HPP


class EdgeNode {
    private:
        double x;
        double y;
        double angle; //given in radians from 0 to 2pi
        EdgeNode *left, *right, *parent;
    public:
        //getters and setters
        EdgeNode *getLeft();
        EdgeNode *getRight();
        EdgeNode *getParent();
        double getX();
        double getY();
        double getAngle();
        void setLeft(EdgeNode *left);
        void setRight(EdgeNode *right);
        void setParent(EdgeNode *parent);
        void setX(double x);
        void setY(double y);
        void setAngle(double angle);
        
        //constructors
        EdgeNode();
        EdgeNode(double x, double y, double angle);
        EdgeNode(double x, double y, double angle, EdgeNode *left, EdgeNode *right);

        //copyers
        EdgeNode(const EdgeNode &e);
        EdgeNode& operator=(const EdgeNode &e);

        //value functions
        double getValue(double sweepline); //gets where the edge intersects the arcs
};


#endif // EDGE_NODE_HPP
