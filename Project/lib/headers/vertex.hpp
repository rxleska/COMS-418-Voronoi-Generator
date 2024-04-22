// Vertex class header file (lib/vertex.cpp)
#ifndef VERTEX_HPP
#define VERTEX_HPP


class Vertex{
    private:
        static int idCounter;
    public:
        double x;
        double y;
        int id; //unique id for each vertex
        Vertex();
        Vertex(double x, double y);
        Vertex(double x, double y, int id);
        //copy constructor
        Vertex(const Vertex& v);
        //overload the = operator
        Vertex& operator=(const Vertex& v);
        //overload the + operator
        Vertex operator+(const Vertex& v);
        //overload the - operator
        Vertex operator-(const Vertex& v);
        //overload the * operator
        Vertex operator*(const int& i);
        //overload the / operator
        Vertex operator/(const int& i);
        Vertex dot (const Vertex& v);
        double cross (const Vertex& v);
};

#endif