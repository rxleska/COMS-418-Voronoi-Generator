#include "headers/ParabolaMath.hpp"


/**
 * Calculates the edges created by the parabolas intersecting
 * @param x1 x coordinate of the first arcs focus point
 * @param y1 y coordinate of the first arcs focus point
 * @param x2 x coordinate of the second arcs focus point
 * @param y2 y coordinate of the second arcs focus point
 * @param swpln the directrix of the parabolas
 * #uses double pointers to return the values since I don't want to create a struct for this
 * @param ex1 x coordinate of the first edge
 * @param ey1 y coordinate of the first edge
 * @param er1 angle of the first edge
 * @param ex2 x coordinate of the second edge
 * @param ey2 y coordinate of the second edge
 * @param er2 angle of the second edge
*/
void ParabolaMath::getParabolaEdges(double x1, double y1, double x2, double y2, double swpln, double *ex1, double * ey1, double * er1, double * ex2, double * ey2, double * er2){
    double a;
    double b;
    double c;
    double xminus;
    double xplus;
    double discriminant;\
    
    //check if points have the same y coordinate 
    if(areSameDouble(y1, y2)){
        //TODO handle this case (1 intersection)
        //basically it becomes a line intersection instead of a parabola intersection
        throw "Not implemented yet (need to handle 2 sites with the same y coordinate)";
    }

    //if one point it touching the directrix
    if(areSameDouble(y2, swpln)){
        *ex1 = x2;
        *ex2 = x2;
        *ey1 = getParabolaYatX(x2, x1, y1, swpln);
        *ey2 = getParabolaYatX(x2, x1, y1, swpln);
    }
    else if(areSameDouble(y1, swpln)){
        *ex1 = x1;
        *ex2 = x1;
        *ey1 = getParabolaYatX(x1, x2, y2, swpln);
        *ey2 = getParabolaYatX(x1, x2, y2, swpln);
    }
    else{
        a = 1.0 / (y1-swpln) - 1.0 / (y2-swpln);
        b  = -2.0 * x1/(y1-swpln) + 2.0 * x2/(y2-swpln);
        c = x1*x1/(y1-swpln) - x2*x2/(y2-swpln) + y1 - y2;

        //check the discriminant
        discriminant = b*b - 4*a*c;
        if(isLessThanDouble(discriminant, 0.0)){
            //TODO handle this case (0 intersections)
            throw "Not implemented yet (need to handle 2 parabolas that don't intersect)";
        }

        xminus = (-b - sqrt(discriminant)) / (2.0 * a);
        xplus = (-b + sqrt(discriminant)) / (2.0 * a);
        *ex1 = fmin(xminus, xplus);
        *ex2 = fmax(xminus, xplus);
        *ey1 = getParabolaYatX(*ex1, x1, y1, swpln);
        *ey2 = getParabolaYatX(*ex2, x1, y1, swpln);
    }

    swpln = swpln - 5; //move the directrix down a bit to calculate the edge angles
    a = 1.0 / (y1-swpln) - 1.0 / (y2-swpln);
    b  = -2.0 * x1/(y1-swpln) + 2.0 * x2/(y2-swpln);
    c = x1*x1/(y1-swpln) - x2*x2/(y2-swpln) + y1 - y2;

    //check the discriminant
    discriminant = b*b - 4*a*c;
    if(isLessThanDouble(discriminant, 0.0)){
        //TODO handle this case (0 intersections)
        throw "Not implemented yet (need to handle 2 parabolas that don't intersect)";
    }
    xminus = (-b - sqrt(discriminant)) / (2.0 * a);
    xplus = (-b + sqrt(discriminant)) / (2.0 * a);
    double leftX = fmin(xminus, xplus);
    double rightX = fmax(xminus, xplus);
    double leftY = getParabolaYatX(leftX, x1, y1, swpln);
    double rightY = getParabolaYatX(rightX, x1, y1, swpln);
    *er1 = atan2((*ex1) - leftX, (*ey1) - leftY);
    *er2 = atan2((*ex2) - rightX, (*ey2) - rightY);

    return;
}


/**
 * Checks if a line intersects a parabola, returns true if it does and the point of intersection
 * @param xf x coordinate of the focus point of the parabola
 * @param yf y coordinate of the focus point of the parabola
 * @param directrix the directrix of the parabola (sweepline)
 * @param xe x coordinate of the half edge 
 * @param ye y coordinate of the half edge
 * @param re angle of the half edge
 * @param x pointer to the x coordinate of the intersection point
 * @param y pointer to the y coordinate of the intersection point
*/
bool ParabolaMath::doesLineIntersectParabolaDO(double xf, double yf, double directrix, double xe, double ye, double re, double *x, double *y){
    //handle vertical line degenerate case
    if(areSameDouble(sin(re), 0.0)){
        if(areSameDouble(cos(re), 1.0)){
            return false;
        }
        else{
            *x = xe;
            *y = (xe - xf) * (xe - xf) / (2.0 * (yf - directrix)) + (yf + directrix) / 2;
            
            //sanity check 
            if(isLessThanDouble(ye, *y)){
                return false;
            } 
            return true;
        }
    }
    double slope = cos(re) / sin(re);
    double yint = ye - slope * xe;

    double a = 1.0 / (2.0* (yf - directrix));
    double b = -1.0 * xf / (yf - directrix) - slope;
    double c = xf * xf / (2.0 * (yf - directrix)) + (yf + directrix) / 2 - yint;

    double discriminant = b * b - 4 * a * c;
    if(isLessThanDouble(discriminant, 0.0)){
        return false;
    }

    double x1 = (-b + sqrt(discriminant)) / (2.0 * a);
    double x2 = (-b - sqrt(discriminant)) / (2.0 * a);

    //if the edge angle is to the right get the max x
    if((isLessThanDouble(re, PI/2) && isGreaterThanDouble(re,0)) || (isGreaterThanDouble(re, 3*PI/2) && isLessThanDouble(re, 2*PI))){
        *x = fmax(x1, x2);
    }
    else{
        *x = fmin(x1, x2);

    }

    *y = slope * (*x) + yint;
    return true;
}

/**
 * Checks if a line intersects a parabola, returns true if it does and the point of intersection
 * @param arc the arc that represents the parabola
 * @param directrix the directrix of the parabola (sweepline)
 * @param edge the edge that represents the line
 * @param x pointer to the x coordinate of the intersection point
 * @param y pointer to the y coordinate of the intersection point
*/
bool ParabolaMath::doesLineIntersectParabolaOO(Arc *arc, double directrix, EdgeNode *edge, double *x, double *y){
    return doesLineIntersectParabolaDO(arc->getX(), arc->getY(), directrix, edge->getX(), edge->getY(), edge->getAngle(), x, y);
}


double ParabolaMath::getParabolaYatX(double x, double xf, double yf, double swpln){
    return (x - xf) * (x - xf) / (2.0 * (yf - swpln)) + (yf + swpln) / 2;
}


bool ParabolaMath::areSameDouble(double a, double b){
    return fabs(a - b) < EPSILON;
}

bool ParabolaMath::isLessThanDouble(double a, double b){
    if(areSameDouble(a, b))
        return false;
    return a < b;
}

bool ParabolaMath::isGreaterThanDouble(double a, double b){
    if(areSameDouble(a, b))
        return false;
    return a > b;
}

bool ParabolaMath::isLessThanOrEqualDouble(double a, double b){
    return a < b + EPSILON;
}

bool ParabolaMath::isGreaterThanOrEqualDouble(double a, double b){
    return a > b - EPSILON;
}