
#ifndef PARABOLA_MATH_HPP
#define PARABOLA_MATH_HPP

#include "../../CONST.hpp"
#include "EdgeNode.hpp"
#include "Arc.hpp"

namespace ParabolaMath{
    void getParabolaEdges(double x1, double y1, double x2, double y2, double *ex1, double * ey1, double * er1, double * ex2, double * ey2, double * er2);

    bool doesLineIntersectParabolaDO(double xf, double yf, double directrix, double xe, double ye, double re, double *x, double *y); //double oriented

    bool doesLineIntersectParabolaOO(Arc *arc, double directrix, EdgeNode *edge, double *x, double *y); //object oriented

    bool areSameDouble(double a, double b);


}

#endif // PARABOLA_MATH_HPP