#include "../../CONST.hpp"

#ifndef ARC_HPP
#define ARC_HPP

class Arc {
    private: //just stores the focal point of the parabola
        double x;
        double y;
    public:
        double getX();
        double getY();
        Arc(double x, double y);
        Arc();
        void setX(double x);
        void setY(double y);
        void set(double x, double y);
        //overload the = operator
        Arc& operator=(const Arc &a);
        //copy constructor
        Arc(const Arc &a);
};



#endif // ARC_HPP