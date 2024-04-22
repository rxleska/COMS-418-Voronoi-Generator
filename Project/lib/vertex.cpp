// Vertex Class Definition (just 2 ints with some functions and naming conventions)

#include "headers/Vertex.hpp"

//initialize the id counter
int Vertex::idCounter = 0;

Vertex::Vertex(){
    x = 0;
    y = 0;
    id = idCounter;
    idCounter++;
}
Vertex::Vertex(double x, double y){
    this->x = x;
    this->y = y;
    id = idCounter;
    idCounter++;
}
Vertex::Vertex(double x, double y, int id){
    this->x = x;
    this->y = y;
    this->id = id;
}

//copy constructor
Vertex::Vertex(const Vertex& v){
    this->x = v.x;
    this->y = v.y;
    this->id = v.id;
}

//overload the = operator
Vertex& Vertex::operator=(const Vertex& v){
    this->x = v.x;
    this->y = v.y;
    this->id = v.id;
    return *this;
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
double Vertex::cross (const Vertex& v){
    return (this->x * v.y) - (this->y * v.x);
}
