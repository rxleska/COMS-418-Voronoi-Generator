#ifndef DVERTEX_HPP
#define DVERTEX_HPP

#include "DEdge.hpp"

//forward declaration
class DEdge;

class DVertex {
    private:
        double x;
        double y;
        int id;
        static int idCounter;
    public:
        DVertex();
        DVertex(double x, double y);
        DVertex(double x, double y, int id);
        double getX();
        double getY();
        int getId();
        void setX(double x);
        void setY(double y);
        void setId(int id);
};

#endif // DVERTEX_HPP