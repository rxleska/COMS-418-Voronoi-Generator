

#include <GL/glut.h>
#include "headers/Callback.hpp"
#include "headers/DrawObjects.hpp"
#include "../BeachLine/headers/BeachLine.hpp"

bool isPaused;
bool drawAllArcs;
bool drawAllHalfEdges;
// BeachLine *beachLine;

// bool isPaused{ true }; // Whether the simulation is paused
namespace OGLcallbacks{
    void initOpenGL() {
        glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
        isPaused = true;
        drawAllArcs = false;
        drawAllHalfEdges = true;
    }

    void update(int value) {
        if (!isPaused) {
            SweepAnimationHeight -= 0.05;
            glutPostRedisplay(); // Redraw the window
        }
        glutTimerFunc(16, update, 0); // Schedule next update
    }

    void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
            case 'p': // Pause or unpause the simulation
                isPaused = !isPaused;
                break;
            case 'w':
                if(isPaused){
                    SweepAnimationHeight += 0.1;
                    // beachLine->printTree(beachLine->getRoot(), SweepAnimationHeight);
                    glutPostRedisplay(); // Redraw the scene immediately
                }
                break;
            case 's': // Step through the simulation one frame at a time
                if (isPaused) {
                    SweepAnimationHeight -= 0.1;
                    // beachLine->printTree(beachLine->getRoot(), SweepAnimationHeight);
                    glutPostRedisplay(); // Redraw the scene immediately
                }
                break;
            case 'a': // Draw all arcs
                drawAllArcs = !drawAllArcs;
                break;
            case 'e': // Draw all half edges
                drawAllHalfEdges = !drawAllHalfEdges;
                break;
            case 'l':
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << "Printing Beach Line" << std::endl;
                std::cout << "y: " << beachLine->getSweepLine() << std::endl;
                beachLine->printEdgesInOrder(beachLine->getRoot());
                break;
            default:
                break;
        }
        glutPostRedisplay(); // Redraw the scene immediately
    }

    void display() {
        //check if the Animated sweep line has passed the top event
        Event * topEvent = eventQueue->peek();
        if(topEvent != nullptr && SweepAnimationHeight < topEvent->getY()){
            eventQueue->pop();
            topEvent->handleEvent();
        }
        else if(topEvent == nullptr){
            isPaused = true;
        }

        //if Animated sweep line is below the height of the bounding box
        if(SweepAnimationHeight < -1.25 * windowHeight/heightScale){
            isPaused = true;

            //run the rest of the queue
            while(!eventQueue->isEmpty()){
                topEvent = eventQueue->peek();
                eventQueue->pop();
                topEvent->handleEvent();
            }
        }


        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
        glLoadIdentity(); // Load the identity matrix to reset transformations

        // Draw the scene here
        
        //switch color to blue and draw the points
        glColor3f(0.0, 0.0, 1.0);
        DrawObjects::drawSites();

        //swithc color to red and draw the sweepline
        glColor3f(1.0, 0.0, 0.0);
        DrawObjects::drawSweepLine(SweepAnimationHeight);

        //switch color to green and draw the beachline
        glColor3f(0.0, 1.0, 0.0);
        DrawObjects::drawBeachLine();

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

        
        //set color to blue and draw finished edges
        glColor3f(0.0, 0.0, 1.0);
        DrawObjects::drawFinishedEdges();


        glutSwapBuffers(); // Swap the front and back buffers
    }
}

