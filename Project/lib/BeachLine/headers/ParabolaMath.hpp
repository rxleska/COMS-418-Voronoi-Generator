
#ifndef PARABOLA_MATH_HPP
#define PARABOLA_MATH_HPP

#include "../../CONST.hpp"
#include "EdgeNode.hpp"
#include "Arc.hpp"

namespace ParabolaMath{
    void getParabolaEdges(double x1, double y1, double x2, double y2, double swpln, double *ex1, double * ey1, double * er1, double * ex2, double * ey2, double * er2);

    void getParabolaEdges(Arc a, Arc b, double swpln, EdgeNode *left, EdgeNode *right);

    bool doesLineIntersectParabolaDO(double xf, double yf, double directrix, double xe, double ye, double re, double *x, double *y); //double oriented

    bool doesLineIntersectParabolaOO(Arc *arc, double directrix, EdgeNode *edge, double *x, double *y); //object oriented

    double getParabolaYatX(double x, double xf, double yf, double swpln); // get the y coordinate of the parabola at x

    bool areSameDouble(double a, double b); //a == b

    bool isLessThanDouble(double a, double b); //a < b

    bool isGreaterThanDouble(double a, double b); //a > b

    bool isLessThanOrEqualDouble(double a, double b); //a <= b

    bool isGreaterThanOrEqualDouble(double a, double b); //a >= b

    bool doRaysIntersectAtEvent(double x1, double y1, double r1, double x2, double y2, double r2, double x, double y); //checks if two rays intersect

    bool doEdgesIntersectAtEvent(EdgeNode *a, EdgeNode *b, double x, double y); //checks if two edges intersect

    bool doEdgesIntersect(EdgeNode *a, EdgeNode *b, double *x, double *y); //checks if two edges intersect


}

#endif // PARABOLA_MATH_HPP