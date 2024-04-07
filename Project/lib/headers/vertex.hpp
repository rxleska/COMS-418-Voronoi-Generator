// Vertex class header file (lib/vertex.cpp)
#ifndef VERTEX_HPP
#define VERTEX_HPP


class Vertex{
    private:
        static int idCounter;
    public:
        int x;
        int y;
        int id; //unique id for each vertex
        Vertex();
        Vertex(int x, int y);
        Vertex(int x, int y, int id);
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