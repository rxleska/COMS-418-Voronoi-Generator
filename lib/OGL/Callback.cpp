

#include <GL/glut.h>
#include "headers/Callback.hpp"
#include "headers/DrawObjects.hpp"
#include "../BeachLine/headers/BeachLine.hpp"
#include "../DCEL/headers/PseudoEdge.hpp"

//include ostream
#include <iostream>
#include <fstream>

std::vector<PseudoEdge> pseudoEdges;
DCEL *dcelDelaunay;


bool isPaused;
bool drawAllArcs;
bool hasEnded;
bool drawAllHalfEdges;
bool displayDCEL;
bool displayDelaunay;
double ASLspeed;
// BeachLine *beachLine;




// bool isPaused{ true }; // Whether the simulation is paused
namespace OGLcallbacks{
    bool rayIntersectsSegment(double x, double y, double theta, double x1, double y1, double x2, double y2, double *ix, double *iy){
    // Calculate the direction of the line segment
    double dx = x2 - x1;
    double dy = y2 - y1;
    
    // Calculate the direction of the ray
    double rayDx = cos(theta);
    double rayDy = sin(theta);

    // Determinant of the coefficient matrix
    double determinant = -dx * rayDy + dy * rayDx;

    if (fabs(determinant) < 1e-10) {
        // Lines are parallel or coincident
        return false;
    }

    // solve for t and u
    double t = (dx * (y - y1) - dy * (x - x1)) / determinant;
    double u = (-rayDy * (x - x1) + rayDx * (y - y1)) / determinant;

    // Check if the intersection point is on the ray and within the line segment
    if (t >= 0 && u >= 0 && u <= 1) {
        if (ix != nullptr && iy != nullptr) {
            *ix = x + t * rayDx; // x-coordinate of intersection
            *iy = y + t * rayDy; // y-coordinate of intersection
        }
        return true;
    }

    return false;
}


    void initOpenGL() {
        glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
        isPaused = true;
        drawAllArcs = false;
        drawAllHalfEdges = true;
        hasEnded = false;
        displayDCEL = false;
        ASLspeed = 0.15;
    }

    void update(int value) {
        if (!isPaused) {
            SweepAnimationHeight -= ASLspeed;
            glutPostRedisplay(); // Redraw the window
        }
        glutTimerFunc(16, update, 0); // Schedule next update
    }

    void handleKeypress(unsigned char key, int x, int y) {
        double saveBeachLine;
        switch (key) {
            case 'p': // Pause or unpause the simulation
            case 'P':
                isPaused = !isPaused;
                break;
            case '{':
            case '[':
                ASLspeed /= 1.5;
                break;
            case '}':
            case ']':
                ASLspeed *= 1.5;
                break;
            // case 'w':
            //     if(isPaused){
            //         SweepAnimationHeight += 0.1;
            //         // beachLine->printTree(beachLine->getRoot(), SweepAnimationHeight);
            //         glutPostRedisplay(); // Redraw the scene immediately
            //     }
            //     break;
            case 's': // Step through the simulation one frame at a time
            case 'S':
                if (isPaused) {
                    SweepAnimationHeight -= 0.1;
                    // beachLine->printTree(beachLine->getRoot(), SweepAnimationHeight);
                    glutPostRedisplay(); // Redraw the scene immediately
                }
                break;
            case 'a': // Draw all arcs
            case 'A':
                drawAllArcs = !drawAllArcs;
                break;
            case 'e': // Draw all half edges
            case 'E':
                drawAllHalfEdges = !drawAllHalfEdges;
                break;
            case 'l':
            case 'L':
                saveBeachLine = beachLine->getSweepLine();
                beachLine->setSweepLine(SweepAnimationHeight);
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "Printing Beach Line" << std::endl;
                std::cout << "y: " << beachLine->getSweepLine() << std::endl;
                beachLine->printEdgesInOrder(beachLine->getRoot());
                beachLine->setSweepLine(saveBeachLine);
                break;
            case 'q':
            case 'Q':
                eventQueue->printQueue();
                break;
            case 'f':
            case 'F':
                isPaused = false;
                SweepAnimationHeight = -1.25 * windowHeight/heightScale;
                // beachLine->printTree(beachLine->getRoot(), SweepAnimationHeight);
                glutPostRedisplay(); // Redraw the scene immediately
                break;
            case 'd':
            case 'D':
                if(hasEnded){
                    dcel->printDCEL();
                }
                break;
            case 'x':
            case 'X':
                if(hasEnded){
                    dcelDelaunay->printDCEL();
                }
                break;
            case 'v':
            case 'V':
                if(hasEnded){
                    displayDCEL = !displayDCEL;
                    displayDelaunay = false;
                }
                break;
            case 'c':
            case 'C':
                if(hasEnded){
                    displayDelaunay = !displayDelaunay;
                    displayDCEL = false;
                }
                break;
            case 'n':
            case 'N':
                if(!hasEnded && eventQueue->peek() != nullptr){
                    SweepAnimationHeight = eventQueue->peek()->getY() - 0.1;

                    glutPostRedisplay(); // Redraw the scene immediately
                }
                break;
            default:
                break;
        }

        if(displayDCEL){
            glutSetWindowTitle("Voronoi Diagram");
        }
        else if(displayDelaunay){
            glutSetWindowTitle("Delaunay Triangulation");
        }
        else if(!displayDCEL && !displayDelaunay){
            glutSetWindowTitle("Fortune's Algorithm");
        }


        glutPostRedisplay(); // Redraw the scene immediately
    }

    void display() {
        //check if the Animated sweep line has passed the top event
        Event * topEvent = eventQueue->peek();
        if(!hasEnded){
            if(topEvent != nullptr && SweepAnimationHeight < topEvent->getY()){
                eventQueue->pop();
                topEvent->handleEvent();
            }
        }

        //if Animated sweep line is below the height of the bounding box
        if(!hasEnded && SweepAnimationHeight < -1.25 * windowHeight/heightScale + EPSILON){
            isPaused = true;

            //run the rest of the queue
            while(!eventQueue->isEmpty()){
                topEvent = eventQueue->peek();
                eventQueue->pop();
                topEvent->handleEvent();
            }

            //define the bounding box segments
            double xs[] = {-windowWidth/widthScale, windowWidth/widthScale};
            double ys[] = {-windowHeight/heightScale, windowHeight/heightScale};
            std::vector<Vertex> bounds;

            //empty the beachline, creating pseudo edges
            while(beachLine->getRoot() != nullptr){
                //convert the unbounded edge to a pseudo edge

                //get the edge
                EdgeNode * edge = beachLine->getRoot();
                double sx = edge->getX();
                double sy = edge->getY();
                double theta = edge->getAngle();
                Arc * arc = edge->getLeftArc();
                Arc * arc2 = edge->getRightArc();

                
                double ix, iy;
                double ix2, iy2;
                //intersects both top and bottom segments
                if(rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[1], ys[0], &ix, &iy) && rayIntersectsSegment(sx, sy, theta, xs[0], ys[1], xs[1], ys[1], &ix2, &iy2)){
                    PseudoEdge pe = PseudoEdge(
                        new Vertex(ix2, iy2, -1), 
                        new Vertex(ix, iy, -1), 
                        false, 
                        new Vertex(arc->getX(), arc->getY(), -1),
                        new Vertex(arc2->getX(), arc2->getY(), -1)
                    );
                    pseudoEdges.push_back(pe);
                    bounds.push_back(Vertex(ix, iy, -1));
                }
                //bottom segment
                else if(rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[1], ys[0], &ix, &iy)){
                    PseudoEdge pe = PseudoEdge(
                        new Vertex(sx, sy, -1), 
                        new Vertex(ix, iy, -1), 
                        false, 
                        new Vertex(arc->getX(), arc->getY(), -1),
                        new Vertex(arc2->getX(), arc2->getY(), -1)
                    );
                    pseudoEdges.push_back(pe);
                    bounds.push_back(Vertex(ix, iy, -1));
                }
                //left segment
                else if(rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[0], ys[1], &ix, &iy)){
                    PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                        false, 
                        new Vertex(arc->getX(), arc->getY(), -1),
                        new Vertex(arc2->getX(), arc2->getY(), -1)
                    );
                    pseudoEdges.push_back(pe);
                    bounds.push_back(Vertex(ix, iy, -1));
                }
                //top segment 
                else if(rayIntersectsSegment(sx, sy, theta, xs[0], ys[1], xs[1], ys[1], &ix, &iy)){
                    PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                        false, 
                        new Vertex(arc->getX(), arc->getY(), -1),
                        new Vertex(arc2->getX(), arc2->getY(), -1)
                    );
                    pseudoEdges.push_back(pe);
                    bounds.push_back(Vertex(ix, iy, -1));
                }
                //right segment
                else if(rayIntersectsSegment(sx, sy, theta, xs[1], ys[1], xs[1], ys[0], &ix, &iy)){
                    PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                        false, 
                        new Vertex(arc->getX(), arc->getY(), -1),
                        new Vertex(arc2->getX(), arc2->getY(), -1)
                    );
                    pseudoEdges.push_back(pe);
                    bounds.push_back(Vertex(ix, iy, -1));
                }
                else{
                    //ray starts outside of the bounding box (but not above)
                    if(fabs(sy - ys[1]) > EPSILON){
                        bounds.push_back(Vertex(sx, sy, -1)); 
                    }
                }

                beachLine->remove(beachLine->getRoot());
            }
            bounds.push_back(Vertex(xs[0], ys[0],-1));
            bounds.push_back(Vertex(xs[0], ys[1],-1));
            bounds.push_back(Vertex(xs[1], ys[1],-1));
            bounds.push_back(Vertex(xs[1], ys[0],-1));

            
                
                //combine edges that have the same angle and share the same origin vertex
                // Sort pseudoEdges based on their start Vertex (x then y)
                std::sort(pseudoEdges.begin(), pseudoEdges.end(), [](const PseudoEdge& edge1, const PseudoEdge& edge2) {
                    Vertex *start1 = edge1.start;
                    Vertex *start2 = edge2.start;
                    if (fabs(start1->getX() - start2->getX()) > EPSILON) {
                        return start1->getX() < start2->getX();
                    }
                    return start1->getY() < start2->getY();
                });

                // Combine edges with the same start and angle
                for (size_t i = 0; i < pseudoEdges.size() - 1; i++) {
                    Vertex *start1 = pseudoEdges[i].start;
                    Vertex *start2 = pseudoEdges[i + 1].start;
                    double angle1 = pseudoEdges[i].getAngle();
                    double angle2 = pseudoEdges[i + 1].getAngle();
                    if (start1->getX() - start2->getX() < EPSILON && start1->getY() - start2->getY() < EPSILON && fabs(angle1 - angle2) - PI < EPSILON && fabs(angle1 - angle2) - PI > -EPSILON) {
                        Vertex* end1 = pseudoEdges[i].end;
                        Vertex* end2 = pseudoEdges[i + 1].end;
                        pseudoEdges[i] = PseudoEdge(end1, end2, false, pseudoEdges[i].arc1, pseudoEdges[i].arc2);
                        pseudoEdges.erase(pseudoEdges.begin() + i + 1);
                        i--;
                    }

                    //if the edge is on the top edge of the bounding box, add the end point to the bounds
                    if(fabs(start1->getY()- ys[1]) < EPSILON){
                        bounds.push_back(*start1);
                    }
                    if(fabs(start2->getY()- ys[1]) < EPSILON){
                        bounds.push_back(*start2);
                    }

                }


                //sort bounds by angle with respect to the center of the bounding box
                std::sort(bounds.begin(), bounds.end(), [](Vertex v1, Vertex v2) {
                    double angle1 = atan2(v1.getY(), v1.getX());
                    double angle2 = atan2(v2.getY(), v2.getX());
                    if (angle1 < 0) {
                        angle1 += 2 * PI;
                    }
                    if (angle2 < 0) {
                        angle2 += 2 * PI;
                    }
                    return angle1 < angle2;
                });

                // Create the bounding box edges
                for (size_t i = 0; i < bounds.size(); i++) {
                    // std::cout << bounds[i].getX() << " " << bounds[i].getY() << std::endl;
                    Vertex *start = &bounds[i];
                    Vertex *end = &bounds[(i + 1) % bounds.size()];
                    //if start and end are the same, skip
                    if(fabs(start->getX() - end->getX()) < EPSILON && fabs(start->getY() - end->getY()) < EPSILON){
                        continue;
                    }
                    PseudoEdge pe = PseudoEdge(start, end, true);
                    pseudoEdges.push_back(pe);
                }

            

            //calculate the dcel 
            dcel->constructDCEL(pseudoEdges);
            dcelDelaunay = dcel->toDelaunayTriangulation();

            writeDCELStoFile();

            hasEnded = true;
            displayDCEL = true;
            glutSetWindowTitle("Voronoi Diagram");
        }


        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
        glLoadIdentity(); // Load the identity matrix to reset transformations

        // Draw the scene here
        
        if(!displayDCEL && !displayDelaunay){
            //switch color to blue and draw the points
            glColor3f(0.0, 0.0, 1.0);
            DrawObjects::drawSites();

            //swithc color to red and draw the sweepline
            glColor3f(1.0, 0.0, 0.0);
            DrawObjects::drawSweepLine(SweepAnimationHeight);
        }

        //switch color to orange 
        // glColor3f(1.0, 0.5, 0.0);
        // DrawObjects::drawVerticalLine(0);
        // DrawObjects::drawHorizontalLine(0.333333);

        //switch color to green and draw the beachline
        if(!hasEnded){
            glColor3f(0.0, 1.0, 0.0);
            DrawObjects::drawBeachLine();
        }

        if(drawAllArcs){
            //switch color to yellow and draw all the arcs
            glColor3f(1.0, 1.0, 0.0);
            DrawObjects::drawAllArcs();
        }

        if(drawAllHalfEdges){
            //switch color to white and draw all the half edges
            glColor3f(1.0, 1.0, 1.0);
            DrawObjects::drawAllHalfEdges();
        }

        if(!hasEnded){
            //set color to blue and draw finished edges
            glColor3f(0.0, 0.0, 1.0);
            DrawObjects::drawFinishedEdges();
        }

        if(displayDCEL){
            //set color to white and draw the DCEL
            glColor3f(1.0, 1.0, 1.0);
            DrawObjects::drawDCEL(dcel);

            // glColor3f(0.0, 0.0, 1.0);
            // DrawObjects::drawSites();
        }
        else if(displayDelaunay){
            //set color to white and draw the DCEL
            glColor3f(1.0, 1.0, 1.0);
            DrawObjects::drawDCEL(dcelDelaunay);
        }


        glutSwapBuffers(); // Swap the front and back buffers
    }

    void writeDCELStoFile(){
        std::string voronoi = dcel->dcelToString();
        std::string delaunay = dcelDelaunay->dcelToString();

        //write to voronoi.txt
        std::ofstream voronoiFile;
        voronoiFile.open("voronoi.txt");
        voronoiFile << "****** Voronoi diagram ******" << std::endl;
        voronoiFile << voronoi;
        voronoiFile << std::endl;
        voronoiFile << "****** Delaunay triangulation ******" << std::endl;
        voronoiFile << delaunay;
        voronoiFile.close();

        std::cout << "DCELs written to voronoi.txt" << std::endl;
    }
}

