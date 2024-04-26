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

    swpln = swpln - 0.5; //move the directrix down a bit to calculate the edge angles
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
    *er1 = atan2((*ey2) - rightY, (*ex2) - rightX); //note had x and y swappped at one point
    *er2 = atan2((*ey1) - leftY, (*ex1) - leftX); 


    if(DEBUG){
        //er1 is nan or -nan 
        if(std::isnan(*er1)){
            std::cout << "er1 is nan" << std::endl;
            std::cout << "x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << " swpln: " << swpln << std::endl;
            std::cout << "ex1: " << *ex1 << " ey1: " << *ey1 << " er1: " << *er1 << " ex2: " << *ex2 << " ey2: " << *ey2 << " er2: " << *er2 << std::endl;
            std::cout << "a: " << a << " b: " << b << " c: " << c << " discriminant: " << discriminant << std::endl;
            std::cout << "xminus: " << xminus << " xplus: " << xplus << std::endl;
            std::cout << "leftX: " << leftX << " leftY: " << leftY << " rightX: " << rightX << " rightY: " << rightY << std::endl;
        }
    }
    


    return;
}

void ParabolaMath::getParabolaEdges(Arc a, Arc b, double swpln, EdgeNode *left, EdgeNode *right){
    double x1 = a.getX();
    double y1 = a.getY();
    double x2 = b.getX();
    double y2 = b.getY();
    double ex1;
    double ey1;
    double er1;
    double ex2;
    double ey2;
    double er2;
    getParabolaEdges(x1, y1, x2, y2, swpln, &ex1, &ey1, &er1, &ex2, &ey2, &er2);
    left->setX(ex1);
    left->setY(ey1);
    left->setAngle(er1);
    right->setX(ex2);
    right->setY(ey2);
    right->setAngle(er2);
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

    //handle line parabola (degenerate case) //xf = directrix
    if(areSameDouble(yf, directrix)){
        *x = xf;
        //use the line to get the y value
        double xdiff = xe - xf;
        double unit = xdiff / cosf(re);
        *y = ye - unit * sinf(re);

        // if(DEBUG) std::cout << "vertical parabola" << " x: " << *x << " y: " << *y << std::endl;


        return true;
    }

    //handle vertical line degenerate case
    if(areSameDouble(cos(re), 0.0)){
        if(areSameDouble(sin(re), 1.0)){
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
    double slope = sin(re) / cos(re);
    double yint = ye - slope * xe;

    double a = 1.0 / (2.0* (yf - directrix));
    double b = -1.0 * xf / (yf - directrix) - slope;
    double c = xf * xf / (2.0 * (yf - directrix)) + (yf + directrix) / 2 - yint;


    double discriminant = b * b - 4 * a * c;
    if(areSameDouble(discriminant, 0.0)){
        discriminant = 0.0;
    }

    if(isLessThanDouble(discriminant, 0.0)){
        return false;
    }

    double x1 = (-b + (discriminant == 0.0 ? 0.0 : sqrt(discriminant))) / (2.0 * a);
    double x2 = (-b - (discriminant == 0.0 ? 0.0 : sqrt(discriminant))) / (2.0 * a);

    //if the edge angle is to the right get the max x
    if(isGreaterThanDouble(re, PI/2) && isLessThanDouble(re, 3*PI/2)){ //left
        *x = fmin(x1, x2);
    }
    else{
        *x = fmax(x1, x2);

    }

    //if x is nan or -nan return false
    if(std::isnan(*x)){
        //print out method parameters
        std::cout << "xf: " << xf << " yf: " << yf << " directrix: " << directrix << " xe: " << xe << " ye: " << ye << " re: " << re << std::endl;

        //print out a,b,c 
        std::cout << x1 << " " << x2 << std::endl;
        std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
        throw "here";
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