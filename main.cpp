#include "lib/CONST.hpp"
#include "lib/BeachLine/headers/BeachLine.hpp"
#include "lib/BeachLine/headers/ParabolaMath.hpp"
#include "lib/EventQueue/headers/EQueue.hpp"
#include "lib/BeachLine/headers/EdgeNode.hpp"
#include "lib/BeachLine/headers/Arc.hpp"
#include "lib/DCEL/headers/Vertex.hpp"
#include "lib/DCEL/headers/Edge.hpp"
#include "lib/DCEL/headers/DCEL.hpp"
#include <fstream>
#include <GL/glut.h>
#include "lib/OGL/headers/DrawObjects.hpp"
#include "lib/OGL/headers/Callback.hpp"


// Global variables (extern in CONST.hpp)
std::vector<Vertex> vertices;
std::vector<Edge *> finishedEdges;
DCEL *dcel;
BeachLine *beachLine;
EventQueue *eventQueue;
double windowWidth;
double windowHeight;
double widthScale;
double heightScale;
double SweepAnimationHeight;
    
double stringToDouble(const std::string& str) {
    try {
        return std::stod(str);  // Uses the C++ standard library to convert string to double
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        return 0.0;
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of range: " << oor.what() << '\n';
        return 0.0;
    }
}

//string to int function
int stringToInt(std::string str){
    int result = 0;
    int sign = 1;
    int startIndex = 0;
    if (str[0] == '-') {
        sign = -1;
        startIndex = 1;
    }
    for (int i = startIndex; i < (int) str.length(); i++){
        result *= 10;
        result += str[i] - '0';
    }
    return result * sign;
}

void readSites(std::vector<Vertex> *vertices, std::string src){
    // Read in the data from sites.txt
    //open file for reading
    std::ifstream file(src);
    if (!file.is_open()){
        std::cerr << "Error: could not open file" << std::endl;
        throw std::runtime_error("Error: could not open file");
    }
    bool isLeft = true;

    while (!file.eof()) { // While not end of file marker
        // If the next character is part of a number, read it in 
        if (('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-' || file.peek() == '.') {
            std::string num = "";
            while (('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-' || file.peek() == '.') {
                num += file.get();
            }
            if (isLeft) {
                vertices->push_back(Vertex(stringToDouble(num), 0.0, -1));
                isLeft = false;
            } else {
                (*vertices)[vertices->size() - 1].setY(stringToDouble(num));
                isLeft = true;
            }
        }
        // If the next character is not part of a number, skip it
        else {
            file.get();
        }
    }

    
    // Close the file
    file.close();
}

int main(int argc, char *argv[]) {
    //handle input flags
    /* no flags run animation with sites.txt as the src
     * -na or -noAnimation skip the animation part 
     * file input 
    */ 
   bool doAnimation = true;
   int numFlags = 0;

   if(argc > 3){
        std::cerr << "Error: too many arguments" << std::endl;
        std::cerr << "Usage: ./main [-na/-noAnimation] [srcFile]" << std::endl;
        return 1;
   }

    //if there are 2 arguments
    else if(argc == 3){
        std::string flag = argv[1];
        std::string flag2 = argv[2];
        numFlags = 2;
        if(flag == "-na" || flag == "-noAnimation"){
            doAnimation = false;
            try{
                readSites(&vertices, argv[2]);
            }
            catch(std::runtime_error &e){
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }else if(flag2 == "-na" || flag2 == "-noAnimation"){
            doAnimation = false;
            try{
                readSites(&vertices, flag);
            }
            catch(std::runtime_error &e){
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
        else{
            std::cerr << "Error: invalid flag" << std::endl;
            std::cerr << "Usage: ./main optional:[-na/-noAnimation] optional:[srcFile]" << std::endl;
            return 1;
        }
    }

    //if there is 1 argument
    else if(argc == 2){
        numFlags = 1;
        std::string flag = argv[1];
        if(flag == "-na" || flag == "-noAnimation"){
            doAnimation = false;
            try{
                std::string srcFile = "sites.txt";
                readSites(&vertices, srcFile);
            }
            catch(std::runtime_error &e){
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }else{
            try{
                readSites(&vertices, flag);
            }
            catch(std::runtime_error &e){
                std::cerr << e.what() << std::endl;
                return 1;
            }
        }
    }

    //if there are no arguments
    else if(argc == 1){
        try{
            std::string srcFile = "sites.txt";
            readSites(&vertices, srcFile);
        }
        catch(std::runtime_error &e){
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }



    //init beach line 
    beachLine = new BeachLine();


    //read in the sites from the file
    // try{
    //     std::string srcFile = "sites.txt";
    //     readSites(&vertices, srcFile);
    // }
    // catch(std::runtime_error &e){
    //     std::cerr << e.what() << std::endl;
    //     return 1;
    // }

    dcel = new DCEL(vertices.size());

    //print out the vertices
    if(DEBUG){
        std::cout << "Vertices: " << std::endl;
        for(int i = 0; i < (int) vertices.size(); i++){
            std::cout << "Vertex " << i << ": (" << vertices[i].getX() << ", " << vertices[i].getY() << ")" << std::endl;
        }
        std::cout << std::endl << std::endl;
    }

    //init event queue 
    eventQueue = new EventQueue(vertices.size()*2);

    //create site events for the event queue
    for(int i = 0; i < (int) vertices.size(); i++){
        eventQueue->insert(new SiteEvent(vertices[i].getX(), vertices[i].getY()));
    }


    //calculate the bounding box
    double minX = vertices[0].getX();
    double maxX = vertices[0].getX();
    double minY = vertices[0].getY();
    double maxY = vertices[0].getY();

    for(int i = 1; i < (int) vertices.size(); i++){
        if(vertices[i].getX() < minX){
            minX = vertices[i].getX();
        }
        if(vertices[i].getX() > maxX){
            maxX = vertices[i].getX();
        }
        if(vertices[i].getY() < minY){
            minY = vertices[i].getY();
        }
        if(vertices[i].getY() > maxY){
            maxY = vertices[i].getY();
        }
    }

    //add 5% to each side
    double dx = maxX - minX;
    double dy = maxY - minY;
    if(ParabolaMath::areSameDouble(0.0, dx)){
        dx = dy * 2;
    }
    if(ParabolaMath::areSameDouble(0.0, dy)){
        dy = dx * 2;
    }

    if(dx * 3 < dy){
        dx = dy;
    }
    else if(dy * 3 < dx){
        dy = dx;
    }

    minX -= dx * boundingScale;
    maxX += dx * boundingScale;
    minY -= dy * boundingScale;
    maxY += dy * boundingScale;


    //if width to height ratio is greater than 16x9, scale by width, else scale by height 
    //max width is 1280 and max height is 720
    if((maxX - minX) / (maxY - minY) > 16.0/9.0){
        windowWidth = 1280*1.5;
        windowHeight = 1280*1.5 * (maxY - minY) / (maxX - minX);
        widthScale = 1280*1.5 / (maxX - minX);
        heightScale = windowHeight / (maxY - minY);
    }else{
        windowHeight = 720*1.5;
        windowWidth = 720*1.5 * (maxX - minX) / (maxY - minY);
        widthScale = windowWidth / (maxX - minX);
        heightScale = 720*1.5 / (maxY - minY);
    }


    //proc the first 2 sites 
    SiteEvent *site1 = (SiteEvent *) eventQueue->pop();
    Arc *arc1 = new Arc(site1->getX(), site1->getY());
    // if(DEBUG) std::cout << "Site 1: (" << site1->getX() << ", " << site1->getY() << ")" << std::endl;
    SiteEvent *site2 = (SiteEvent *) eventQueue->pop();
    Arc *arc2 = new Arc(site2->getX(), site2->getY());

    //print the first two sites locations
    // if(1){
    //     std::cout << "Site 1: (" << site1->getX() << ", " << site1->getY() << ")" << std::endl;
    //     std::cout << "Site 2: (" << site2->getX() << ", " << site2->getY() << ")" << std::endl;
    // }

    //if the first two sites have the same y value
    if(site1->getY() == site2->getY()){
        //define the y value of the edge to be an arbirarly large number
        beachLine->setSweepLine(site2->getY());
        EdgeNode *onlyEdge = new EdgeNode();
        onlyEdge->setLeftArc(arc1);
        onlyEdge->setRightArc(arc2);
        onlyEdge->setX((arc1->getX() + arc2->getX()) / 2.0); // middle of the 2 arcs
        onlyEdge->setY(fabs(10000)); //arbitrarily large number
        onlyEdge->setAngle(3*PI/2.0);

        beachLine->insert(onlyEdge);        
    }
    //if the first two sites have the same x value or otherwise (its the same either way)
    else{
        beachLine->setSweepLine(site2->getY());
        EdgeNode *leftEdge = new EdgeNode();
        leftEdge->setLeftArc(arc1);
        leftEdge->setRightArc(arc2);
        EdgeNode *rightEdge = new EdgeNode();
        rightEdge->setLeftArc(arc2);
        rightEdge->setRightArc(arc1);
        ParabolaMath::getParabolaEdges(*arc1, *arc2, beachLine->getSweepLine(), leftEdge, rightEdge);

        // std::cout << "EDGE INSERTED" << " X: " << leftEdge->getX() << " Y: " << leftEdge->getY() << " Angle: " << leftEdge->getAngle() << std::endl;
        beachLine->insert(leftEdge);
        beachLine->insert(rightEdge);
        // std::cout << "EDGE INSERTED" << " X: " << rightEdge->getX() << " Y: " << rightEdge->getY() << " Angle: " << rightEdge->getAngle() << std::endl;
    }


    // beachLine->printTree(beachLine->getRoot());


    //set animation sweepline to the second site
    SweepAnimationHeight = site2->getY();

    if(doAnimation){
        int argc2 = 1;
        glutInit(&argc2, argv + numFlags); // Initialize GLUT
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the display mode
        glutInitWindowSize(windowWidth, windowHeight); // Set the window size
        glutCreateWindow("Fortune's Algorithm"); // Create the window

        OGLcallbacks::initOpenGL(); // Initialize OpenGL
        glutDisplayFunc(OGLcallbacks::display); // Set the display callback
        glutKeyboardFunc(OGLcallbacks::handleKeypress); // Set the keypress callback
        glutTimerFunc(0, OGLcallbacks::update, 0); // Set the update callback

        glutMainLoop(); // Start the main loop
    }
    else{
        Event * topEvent;

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
            if(OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[1], ys[0], &ix, &iy) && OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[0], ys[1], xs[1], ys[1], &ix2, &iy2)){
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
            else if(OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[1], ys[0], &ix, &iy)){
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
            else if(OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[0], ys[0], xs[0], ys[1], &ix, &iy)){
                PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                    false, 
                    new Vertex(arc->getX(), arc->getY(), -1),
                    new Vertex(arc2->getX(), arc2->getY(), -1)
                );
                pseudoEdges.push_back(pe);
                bounds.push_back(Vertex(ix, iy, -1));
            }
            //top segment 
            else if(OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[0], ys[1], xs[1], ys[1], &ix, &iy)){
                PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                    false, 
                    new Vertex(arc->getX(), arc->getY(), -1),
                    new Vertex(arc2->getX(), arc2->getY(), -1)
                );
                pseudoEdges.push_back(pe);
                bounds.push_back(Vertex(ix, iy, -1));
            }
            //right segment
            else if(OGLcallbacks::rayIntersectsSegment(sx, sy, theta, xs[1], ys[1], xs[1], ys[0], &ix, &iy)){
                PseudoEdge pe = PseudoEdge(new Vertex(sx, sy, -1), new Vertex(ix, iy, -1), 
                    false, 
                    new Vertex(arc->getX(), arc->getY(), -1),
                    new Vertex(arc2->getX(), arc2->getY(), -1)
                );
                pseudoEdges.push_back(pe);
                bounds.push_back(Vertex(ix, iy, -1));
            }
            else{
                //ray starts outside of the bounding box
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

        OGLcallbacks::writeDCELStoFile();
    }
    return 0;
}