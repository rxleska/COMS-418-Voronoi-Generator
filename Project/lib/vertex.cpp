// Vertex Class Definition (just 2 ints with some functions and naming conventions)

#include "headers/Vertex.hpp"

Vertex::Vertex(){
    x = 0;
    y = 0;
}
Vertex::Vertex(int x, int y){
    this->x = x;
    this->y = y;
}
//overload the + operator
Vertex Vertex::operator+(const Vertex& v){
    Vertex result;
    result.x = this->x + v.x;
    result.y = this->y + v.y;
    return result;
}
//overload the - operator
Vertex Vertex::operator-(const Vertex& v){
    Vertex result;
    result.x = this->x - v.x;
    result.y = this->y - v.y;
    return result;

}
//overload the * operator
Vertex Vertex::operator*(const int& i){
    Vertex result;
    result.x = this->x * i;
    result.y = this->y * i;
    return result;
}
//overload the / operator
Vertex Vertex::operator/(const int& i){
    Vertex result;
    result.x = this->x / i;
    result.y = this->y / i;
    return result;
}
Vertex Vertex::dot (const Vertex& v){
    Vertex result;
    result.x = this->x * v.x;
    result.y = this->y * v.y;
    return result;
}
int Vertex::cross (const Vertex& v){
    return (this->x * v.y) - (this->y * v.x);
}
