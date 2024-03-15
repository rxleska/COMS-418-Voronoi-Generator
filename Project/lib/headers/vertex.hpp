// Vertex class header file (lib/vertex.cpp)
#ifndef VERTEX_HPP
#define VERTEX_HPP


class Vertex{
    public:
        int x;
        int y;
        Vertex();
        Vertex(int x, int y);
        //overload the + operator
        Vertex operator+(const Vertex& v);
        //overload the - operator
        Vertex operator-(const Vertex& v);
        //overload the * operator
        Vertex operator*(const int& i);
        //overload the / operator
        Vertex operator/(const int& i);
        Vertex dot (const Vertex& v);
        int cross (const Vertex& v);
};

#endif