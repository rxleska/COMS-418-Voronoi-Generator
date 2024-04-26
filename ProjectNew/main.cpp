#include "lib/CONST.hpp"
#include "lib/BeachLine/headers/BeachLine.hpp"
#include "lib/BeachLine/headers/ParabolaMath.hpp"
#include "lib/EventQueue/headers/EQueue.hpp"
#include "lib/BeachLine/headers/EdgeNode.hpp"
#include "lib/BeachLine/headers/Arc.hpp"
#include "lib/DCEL/headers/Vertex.hpp"
#include "lib/DCEL/headers/Edge.hpp"
#include <fstream>
#include <GL/glut.h>
#include "lib/OGL/headers/DrawObjects.hpp"
#include "lib/OGL/headers/Callback.hpp"


// Global variables (extern in CONST.hpp)
std::vector<Vertex> vertices;
std::vector<Edge *> finishedEdges;
BeachLine *beachLine;
EventQueue *eventQueue;
double windowWidth;
double windowHeight;
double widthScale;
double heightScale;
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
    minX -= dx * boundingScale;
    maxX += dx * boundingScale;
    minY -= dy * boundingScale;
    maxY += dy * boundingScale;


    //if width to height ratio is greater than 16x9, scale by width, else scale by height 
    //max width is 1280 and max height is 720
    if((maxX - minX) / (maxY - minY) > 16.0/9.0){
        windowWidth = 1280;
        windowHeight = 1280 * (maxY - minY) / (maxX - minX);
        widthScale = 1280 / (maxX - minX);
        heightScale = windowHeight / (maxY - minY);
    }else{
        windowHeight = 720;
        windowWidth = 720 * (maxX - minX) / (maxY - minY);
        widthScale = windowWidth / (maxX - minX);
        heightScale = 720 / (maxY - minY);
    }




    //proc the first 2 sites 
    SiteEvent *site1 = (SiteEvent *) eventQueue->pop();
    Arc *arc1 = new Arc(site1->getX(), site1->getY());
    if(DEBUG) std::cout << "Site 1: (" << site1->getX() << ", " << site1->getY() << ")" << std::endl;
    SiteEvent *site2 = (SiteEvent *) eventQueue->pop();
    Arc *arc2 = new Arc(site2->getX(), site2->getY());
    if(DEBUG) std::cout << "Site 2: (" << site2->getX() << ", " << site2->getY() << ")" << std::endl;
    beachLine->setSweepLine(site2->getY());
    EdgeNode *leftEdge = new EdgeNode();
    leftEdge->setLeftArc(arc1);
    leftEdge->setRightArc(arc2);
    EdgeNode *rightEdge = new EdgeNode();
    rightEdge->setLeftArc(arc2);
    rightEdge->setRightArc(arc1);
    ParabolaMath::getParabolaEdges(*arc1, *arc2, beachLine->getSweepLine(), leftEdge, rightEdge);

    // leftEdge->setAngle(3.97934);
    // rightEdge->setAngle(0.83775);

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

    beachLine->printTree(beachLine->getRoot());


    //set animation sweepline to the second site
    SweepAnimationHeight = site2->getY();

    
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(windowWidth, windowHeight); // Set the window size
    glutCreateWindow("Fortune's Algorithm"); // Create the window

    OGLcallbacks::initOpenGL(); // Initialize OpenGL
    glutDisplayFunc(OGLcallbacks::display); // Set the display callback
    glutKeyboardFunc(OGLcallbacks::handleKeypress); // Set the keypress callback
    glutTimerFunc(0, OGLcallbacks::update, 0); // Set the update callback

    glutMainLoop(); // Start the main loop
    return 0;
}