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
        *ex1 = (x2*x2 - x1*x1)/(2.0 * (x2 - x1));
        *ex2 = *ex1;
        *ey1 = getParabolaYatX(*ex1, x1, y1, swpln);
        *ey2 = *ey1;
        //set left edge pointed down and right edge pointed up
        *er2 = PI/2.0;
        *er1 = 3*PI/2.0;
        return;

        // throw "Not implemented yet (need to handle 2 sites with the same y coordinate)";
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
        double unit = xdiff / cos(re);
        *y = ye - unit * sin(re);

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


bool ParabolaMath::doRaysIntersectAtEvent(double x1, double y1, double r1, double x2, double y2, double r2, double x, double y){
    //handle vertical rays (degenerate case) (this is needed to prevent division by 0)
    if(areSameDouble(x1, x2) && areSameDouble(x1, x)){
        if(areSameDouble(r1, 3*PI/2) && areSameDouble(r2, 3*PI/2)){//y1 down and y2 down
            if(VDEBUG) std::cout << "both y down" << std::endl;
            return isLessThanOrEqualDouble(y, fmin(y1, y2));
        } 
        else if(areSameDouble(r1, PI/2) && areSameDouble(r2, PI/2)){//y1 up and y2 up
            if(VDEBUG) std::cout << "both y up" << std::endl;
            return isGreaterThanOrEqualDouble(y, fmax(y1, y2));
        }
        else if(areSameDouble(r1, PI/2) && areSameDouble(r2, 3*PI/2)){//y1 up and y2 down
            if(VDEBUG) std::cout << "y1 up y2 down" << std::endl;
            return isLessThanOrEqualDouble(y, y2) && isGreaterThanOrEqualDouble(y, y1);
        }
        else if(areSameDouble(r1, 3*PI/2) && areSameDouble(r2, PI/2)){//y1 down and y2 up
            if(VDEBUG) std::cout << "y1 down y2 up" << std::endl;
            return isLessThanOrEqualDouble(y, y1) && isGreaterThanOrEqualDouble(y, y2);
        }
    }
    else if((areSameDouble(r1, PI/2) || areSameDouble(r1, 3*PI/2)) && (areSameDouble(r2, PI/2) || areSameDouble(r2, 3*PI/2))){
        if(VDEBUG) std::cout << "[r2d] t2 is less than 0" << std::endl;
        return false; //catch the case where both rays are vertical but not at the same x value
    }
    else if(areSameDouble(r1, PI/2)){
        //ray 1 points up 
        double t1 = (x1 - x2)/cos(r2);
        if(isLessThanDouble(t1, 0.0)){
            if(VDEBUG) std::cout << "[r1u] t2 is less than 0" << std::endl;
            return false;
        }
        double yint = y2 + t1 * sin(r2);
        if(DEBUG) std::cout << "[ray interception: r1 up] yint: " << yint << " y1: " << y1 << " y: " << y << std::endl;
        //debug log edges values
        if(DEBUG) std::cout << "x1: " << x1 << " y1: " << y1 << " r1: " << r1 << " x2: " << x2 << " y2: " << y2 << " r2: " << r2 << " x: " << x << " y: " << y << std::endl;
        return isGreaterThanOrEqualDouble(yint, y1) && areSameDouble(yint, y);
    
    }
    else if(areSameDouble(r1, 3*PI/2)){
        //ray 1 points down
        double t1 = (x1 - x2)/cos(r2);
        if(isLessThanDouble(t1, 0.0)){
            if(VDEBUG) std::cout << "[r1d] t2 is less than 0" << std::endl;
            return false;
        }
        double yint = y2 + t1 * sin(r2);
        if(DEBUG) std::cout << "[ray interception: r1 down] yint: " << yint << " y1: " << y1 << " y: " << y << std::endl;
        if(DEBUG) std::cout << "x1: " << x1 << " y1: " << y1 << " r1: " << r1 << " x2: " << x2 << " y2: " << y2 << " r2: " << r2 << " x: " << x << " y: " << y << std::endl;
        return isLessThanOrEqualDouble(yint, y1) && areSameDouble(yint, y);
    }
    else if(areSameDouble(r2, PI/2)){
        //ray 2 points up
        double t2 = (x2 - x1)/cos(r1);
        if(isLessThanDouble(t2, 0.0)){
            if(VDEBUG) std::cout << "[r2u] t2 is less than 0" << std::endl;
            return false;
        }
        double yint = y1 + t2 * sin(r1);
        if(DEBUG) std::cout << "[ray interception: r2 up] yint: " << yint << " y2: " << y2 << " y: " << y << std::endl;
        if(DEBUG) std::cout << "x1: " << x1 << " y1: " << y1 << " r1: " << r1 << " x2: " << x2 << " y2: " << y2 << " r2: " << r2 << " x: " << x << " y: " << y << std::endl;
        return isGreaterThanOrEqualDouble(yint, y2) && areSameDouble(yint, y);
    }
    else if(areSameDouble(r2, 3*PI/2)){
        //ray 2 points down
        double t2 = (x2 - x1)/cos(r1);
        if(isLessThanDouble(t2, 0.0)){
            if(VDEBUG) std::cout << "[r2d] t2 is less than 0" << std::endl;
            return false;
        }
        double yint = y1 + t2 * sin(r1);
        if(DEBUG) std::cout << "[ray interception: r2 down] yint: " << yint << " y2: " << y2 << " y: " << y << std::endl;
        if(DEBUG) std::cout << "x1: " << x1 << " y1: " << y1 << " r1: " << r1 << " x2: " << x2 << " y2: " << y2 << " r2: " << r2 << " x: " << x << " y: " << y << std::endl;
        return isLessThanOrEqualDouble(yint, y2) && areSameDouble(yint, y);    
    }


    //handle the horizontal ray case (degenerate case)
    if(areSameDouble(sin(r1), 0.0) || areSameDouble(sin(r2), 0.0)){
        if(areSameDouble(sin(r1), sin(r2))){
            if(!areSameDouble(y1, y2)){
                return false;
            }
            if(!areSameDouble(y1, y)){
                return false;
            }
            //4 cases to check both left, both right, one left one right, one right one left
            if(areSameDouble(cos(r1), 1.0) && areSameDouble(cos(r2), 1.0)){ //both right
                return isGreaterThanOrEqualDouble(x, fmin(x1, x2));
            }
            else if(areSameDouble(cos(r1), -1.0) && areSameDouble(cos(r2), -1.0)){ //both left
                return isLessThanOrEqualDouble(x, fmax(x1, x2));
            }
            else if(areSameDouble(cos(r1), 1.0) && areSameDouble(cos(r2), -1.0)){ //(right, left)
                return isGreaterThanOrEqualDouble(x, x1) && isLessThanOrEqualDouble(x, x2);
            }
            else if(areSameDouble(cos(r1), -1.0) && areSameDouble(cos(r2), 1.0)){ //(left, right)
                return isGreaterThanOrEqualDouble(x, x2) && isLessThanOrEqualDouble(x, x1);
            }

        }
        else{
            //only 1 is horizontal
            if(areSameDouble(sin(r1), 0.0)){ //r1 is horizontal
                if(DEBUG) std::cout << "r1 is horizontal" << std::endl;
                if(!areSameDouble(y1, y)){
                    return false;
                }
                double t2 = (y1 - y2)/sin(r2);
                double xint = x2 + t2 * cos(r2);
                if(areSameDouble(cos(r1), 1)){ //r1 is pointed right
                    return areSameDouble(xint, x) && isGreaterThanOrEqualDouble(t2, 0.0) && isGreaterThanOrEqualDouble(xint, x1);
                }else{ //r1 is pointed left 
                    return areSameDouble(xint, x) && isGreaterThanOrEqualDouble(t2, 0.0) && isLessThanOrEqualDouble(xint, x1);
                }
                
            }
            else{ //r2 is horizontal
                if(DEBUG) std::cout << "r2 is horizontal" << std::endl;
                if(!areSameDouble(y2, y)){
                    return false;
                }
                double t1 = (y2 - y1)/sin(r1);
                double xint = x1 + t1 * cos(r1);
                if(areSameDouble(cos(r2), 1)){ //r2 is pointed right
                    return areSameDouble(xint, x) && isGreaterThanOrEqualDouble(t1, 0.0) && isGreaterThanOrEqualDouble(xint, x2);
                }
                else{ //r2 is pointed left
                    return areSameDouble(xint, x) && isGreaterThanOrEqualDouble(t1, 0.0) && isLessThanOrEqualDouble(xint, x2);
                }
            }
        }
    }


    double t1a = (x - x1)/cos(r1);
    double t1b = (y - y1)/sin(r1);
    double t2a = (x - x2)/cos(r2);
    double t2b = (y - y2)/sin(r2); 


    if(areSameDouble(t1a, t1b) && areSameDouble(t2a, t2b)){
        return isGreaterThanOrEqualDouble(t1a, 0.0) && isGreaterThanOrEqualDouble(t2a, 0.0);
    }
    return false;
}


bool ParabolaMath::doEdgesIntersectAtEvent(EdgeNode *a, EdgeNode *b, double x, double y){
    return doRaysIntersectAtEvent(a->getX(), a->getY(), a->getAngle(), b->getX(), b->getY(), b->getAngle(), x, y);
}


bool ParabolaMath::doEdgesIntersect(EdgeNode *a, EdgeNode *b, double *x, double *y){
    //check horizontal ray case (degenerate case)
    if(areSameDouble(a->getAngle(), 0.0) || areSameDouble(a->getAngle(), 2*PI)){ //a points right horizontally
        *y = a->getY();
        // get x from the other edge using the y value
        *x = b->getX() + (*y - b->getY())/tan(b->getAngle());
        if(isLessThanDouble(*x, a->getX())){
            return false;
        }
        return true;
    }
    else if(areSameDouble(a->getAngle(), PI)){ //a points left horizontally
        *y = a->getY();
        // get x from the other edge using the y value
        *x = b->getX() + (*y - b->getY())/tan(b->getAngle());
        if(isLessThanOrEqualDouble(*x, a->getX())){
            return true;
        }
        return false;
    }    
    else if(areSameDouble(a->getAngle(), 0.0) || areSameDouble(a->getAngle(), 2*PI)){ //b points right horizontally
        *y = b->getY();
        // get x from the other edge using the y value
        *x = a->getX() + (*y - a->getY())/tan(a->getAngle());
        if(isLessThanDouble(*x, b->getX())){
            return false;
        }
        return true;
    }
    else if(areSameDouble(a->getAngle(), PI)){ //b points left horizontally
        *y = b->getY();
        // get x from the other edge using the y value
        *x = a->getX() + (*y - a->getY())/tan(a->getAngle());
        if(isLessThanOrEqualDouble(*x, b->getX())){
            return true;
        }

    }


    //degenerate case, one edge is vertical
    if(areSameDouble(a->getAngle(), PI/2)){ //a points up vertically
        *x = a->getX();
        // get y from the other edge using the x value
        *y = b->getY() + tan(b->getAngle()) * (*x - b->getX());
        if(isLessThanDouble(*y, a->getY())){
            return false;
        }
        return true;

    }
    else if(areSameDouble(a->getAngle(), 3*PI/2)){ // a points down vertically
        *x = a->getX();
        // get y from the other edge using the x value
        *y = b->getY() + tan(b->getAngle()) * (*x - b->getX());
        if(isLessThanOrEqualDouble(*y, a->getY())){
            return true;
        }
        return false;

    }
    else if(areSameDouble(b->getAngle(), PI/2)){ //b points up vertically
        *x = b->getX();
        // get y from the other edge using the x value
        *y = a->getY() + tan(a->getAngle()) * (*x - a->getX());
        if(isLessThanDouble(*y, b->getY())){
            return false;
        }
        return true;
    }
    else if(areSameDouble(b->getAngle(), 3*PI/2)){ //b points down vertically
        *x = b->getX();
        // get y from the other edge using the x value
        *y = a->getY() + tan(a->getAngle()) * (*x - a->getX());
        if(isLessThanOrEqualDouble(*y, b->getY())){
            return true;
        }
        return false;

    }



    double leftslope = tan(a->getAngle());
    double leftInt = a->getY() - leftslope * a->getX();
    double rightslope = tan(b->getAngle());
    double rightInt = b->getY() - rightslope * b->getX();
    if(areSameDouble(leftslope, rightslope)){
        //TODO handle this case (parallel lines) (they might intersect at some point)
        if(!areSameDouble(rightInt, leftInt)){
            return false;
        }
        if(isGreaterThanOrEqualDouble(a->getX(), b->getX())){ //a on right
            //return t if b points right (0,pi/2) || (3pi/2, 2pi), or a points left (pi/2, 3pi/2)
            return (
                // b (0, pi/2)
                (isGreaterThanDouble(b->getAngle(), 0.0) && isLessThanDouble(b->getAngle(), PI/2)) ||
                // b (3pi/2, 2pi)
                (isGreaterThanDouble(b->getAngle(), 3*PI/2) && isLessThanDouble(b->getAngle(), 2*PI)) ||
                // a (pi/2, 3pi/2) 
                (isGreaterThanDouble(a->getAngle(), PI/2) && isLessThanDouble(a->getAngle(), 3*PI/2) )
            );
        }
        else{ //b on right
            //return t if a points right (0,pi/2) || (3pi/2, 2pi), or b points left (pi/2, 3pi/2)
            return (
                // a (0, pi/2)
                (isGreaterThanDouble(a->getAngle(), 0.0) && isLessThanDouble(a->getAngle(), PI/2)) ||
                // a (3pi/2, 2pi)
                (isGreaterThanDouble(a->getAngle(), 3*PI/2) && isLessThanDouble(a->getAngle(), 2*PI)) ||
                // b (pi/2, 3pi/2) 
                (isGreaterThanDouble(b->getAngle(), PI/2) && isLessThanDouble(b->getAngle(), 3*PI/2) )
            );
        }


        throw "Not implemented yet (need to handle 2 parallel lines)";
    }
    double xa = (rightInt - leftInt) / (leftslope - rightslope);
    double ya = leftslope * xa + leftInt;
    *x = xa;
    *y = ya;
    return doEdgesIntersectAtEvent(a, b, xa, ya);
    
}