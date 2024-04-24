#include "headers/ParabolaMath.hpp"



/**
 * Calculates the edges created by the parabolas intersecting
 * @param x1 x coordinate of the first arcs focus point
 * @param y1 y coordinate of the first arcs focus point
 * @param x2 x coordinate of the second arcs focus point
 * @param y2 y coordinate of the second arcs focus point
 * #uses double pointers to return the values since I don't want to create a struct for this
 * @param ex1 x coordinate of the first edge
 * @param ey1 y coordinate of the first edge
 * @param er1 angle of the first edge
 * @param ex2 x coordinate of the second edge
 * @param ey2 y coordinate of the second edge
 * @param er2 angle of the second edge
*/
void ParabolaMath::getParabolaEdges(double x1, double y1, double x2, double y2, double *ex1, double * ey1, double * er1, double * ex2, double * ey2, double * er2){

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
    return false;
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
    return false;
}



bool ParabolaMath::areSameDouble(double a, double b){
    return fabs(a - b) < EPSILON;
}


