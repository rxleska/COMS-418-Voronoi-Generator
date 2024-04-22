#include <cmath>
#include <iostream>

void getParabolaSides(double x1, double x2, double y1, double y2, double sweep, double *left, double *right){
    //Check if points are colinear parallel to the x axis and if so return no intersection
    if(y1 == y2){
        std::cout << "no intersection" << std::endl;
        left = nullptr;
        right = nullptr;
        return;
    }


    double a = 1.0 / (y1-sweep) - 1.0 / (y2-sweep);
    double b  = -2.0 * x1/(y1-sweep) + 2.0 * x2/(y2-sweep);
    double c = x1*x1/(y1-sweep) - x2*x2/(y2-sweep) + y1 - y2;

    std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;

    // test for no intersection
    if(b*b - 4*a*c < 0){
        std::cout << "no intersection" << std::endl;
        left = nullptr;
        right = nullptr;
        return;
    }

    //else calculate the intersections 
    double xIntersection1 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
    double xIntersection2 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
    if(xIntersection1 < xIntersection2){
        *left = xIntersection1;
        *right = xIntersection2;
    }else{
        *left = xIntersection2;
        *right = xIntersection1;
    }
    return;
}

void testLeftRight(double x1, double x2, double y1, double y2, double sweep, double left, double right){
    double newY1 = (left-x1)*(left-x1)/(2*(y1-sweep)) + (y1+sweep)/2.0;
    double newY2 = (left-x2)*(left-x2)/(2*(y2-sweep)) + (y2+sweep)/2.0;

    std::cout << "newY1: " << newY1 << " newY2: " << newY2 << std::endl;

    newY1 = (right-x1)*(right-x1)/(2*(y1-sweep)) + (y1+sweep)/2.0;
    newY2 = (right-x2)*(right-x2)/(2*(y2-sweep)) + (y2+sweep)/2.0;

    std::cout << "newY1: " << newY1 << " newY2: " << newY2 << std::endl;
}

int main(int argc, char *argv[]){
    double x1 = -10;
    double x2 = 0;
    double y1 = 9;
    double y2 = 0;
    double sweep = 1;
    double left;
    double right;
    getParabolaSides(x1, x2, y1, y2, sweep, &left, &right);
    std::cout << "left: " << left << " right: " << right << std::endl;
    
    testLeftRight(x1, x2, y1, y2, sweep, left, right);

    return 0;
}