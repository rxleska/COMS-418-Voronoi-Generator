#include "lib/CONST.hpp"
#include "lib/BeachLine/headers/BeachLine.hpp"
#include "lib/BeachLine/headers/ParabolaMath.hpp"
#include "lib/EventQueue/headers/EQueue.hpp"
#include "lib/BeachLine/headers/EdgeNode.hpp"
#include "lib/BeachLine/headers/Arc.hpp"
#include "lib/DCEL/headers/Vertex.hpp"
#include <fstream>
#include <GL/glut.h>
#include "lib/OGL/headers/DrawObjects.hpp"
#include "lib/OGL/headers/Callback.hpp"


// Global variables (extern in CONST.hpp)
std::vector<Vertex> vertices;
BeachLine *beachLine;
EventQueue *eventQueue;
double windowWidth;
double windowHeight;
double SweepAnimationHeight;
    
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

void readSites(std::vector<Vertex> *vertices){
    // Read in the data from sites.txt
    //open file for reading
    std::ifstream file("sites.txt");
    if (!file.is_open()){
        std::cerr << "Error: could not open file" << std::endl;
        throw std::runtime_error("Error: could not open file");
    }
    bool isLeft = true;

    while(!file.eof()){ //while not end of file marker
        //if the next character is a number, read it in 
        if(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
            std::string num = "";
            while(('0' <= file.peek() && file.peek() <= '9') || file.peek() == '-'){
                num += file.get();
            }
            if(isLeft){
                vertices->push_back(Vertex(stringToInt(num), 0));
                isLeft = false;
            }else{
                (*vertices)[vertices->size() - 1].setY(stringToInt(num));
                isLeft = true;
            }
        }
        //if the next character is not a number, skip it
        else{
            file.get();
        }
    }

    
    // Close the file
    file.close();
}

int main(int argc, char *argv[]) {
    //init beach line 
    beachLine = new BeachLine();


    //read in the sites from the file
    try{
        readSites(&vertices);
    }
    catch(std::runtime_error &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

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

    if(DEBUG){
        //read the heap
        std::cout << "Heap: " << std::endl;
        while(!eventQueue->isEmpty()){
            Event *e = eventQueue->pop();
            std::cout << "Event: " << e->getX() << " " << e->getY() << std::endl;
        }
    }

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
    minX -= dx * 0.05;
    maxX += dx * 0.05;
    minY -= dy * 0.05;
    maxY += dy * 0.05;

    if(dx < 100){
        dx = 100;
    }
    if(dy < 100){
        dy = 100;
    }

    //set the window width and height
    windowWidth = dx;
    windowHeight = dy;

    //initialize the sweep line height
    SweepAnimationHeight = maxY;


    //proc the first 2 sites 
    SiteEvent *site1 = (SiteEvent *) eventQueue->pop();
    Arc *arc1 = new Arc(site1->getX(), site1->getY());
    SiteEvent *site2 = (SiteEvent *) eventQueue->pop();
    Arc *arc2 = new Arc(site2->getX(), site2->getY());
    beachLine->setSweepLine(site2->getY());
    EdgeNode *leftEdge = new EdgeNode();
    leftEdge->setLeftArc(arc1);
    leftEdge->setRightArc(arc2);
    EdgeNode *rightEdge = new EdgeNode();
    rightEdge->setLeftArc(arc2);
    rightEdge->setRightArc(arc1);
    ParabolaMath::getParabolaEdges(*arc1, *arc2, beachLine->getSweepLine(), leftEdge, rightEdge);
    //insert the edges into the beach line
    beachLine->insert(leftEdge);
    beachLine->insert(rightEdge);

    if(DEBUG){
        //write the edges to the console
        std::cout << "Left Edge: " << std::endl;
        std::cout << "X: " << leftEdge->getX() << " Y: " << leftEdge->getY() << " Angle: " << leftEdge->getAngle() << std::endl;
        std::cout << "Right Edge: " << std::endl;
        std::cout << "X: " << rightEdge->getX() << " Y: " << rightEdge->getY() << " Angle: " << rightEdge->getAngle() << std::endl;
    }

    //set animation sweepline to the second site
    SweepAnimationHeight = site2->getY();

    
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(dx*1.05, dy*1.05); // Set the window size
    glutCreateWindow("Fortune's Algorithm"); // Create the window

    OGLcallbacks::initOpenGL(); // Initialize OpenGL
    glutDisplayFunc(OGLcallbacks::display); // Set the display callback
    glutKeyboardFunc(OGLcallbacks::handleKeypress); // Set the keypress callback
    glutTimerFunc(0, OGLcallbacks::update, 0); // Set the update callback

    glutMainLoop(); // Start the main loop
    return 0;
}