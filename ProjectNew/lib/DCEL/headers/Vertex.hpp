
#include "../../CONST.hpp"

#ifndef VERTEX_HPP
#define VERTEX_HPP

class Vertex {
    private:
        static int idCounter;
        double x;
        double y;
        int id;
    public:
        //constructors
        Vertex();
        Vertex(double x, double y);
        Vertex(double x, double y, int id);

        //getters and setters
        double getX();
        double getY();
        int getId();
        void setX(double x);
        void setY(double y);
        void setId(int id);
        void set(double x, double y);
        //overload the = operator
        Vertex& operator=(const Vertex &v);
        //copy constructor
        Vertex(const Vertex &v);
};

#endif // VERTEX_HPP