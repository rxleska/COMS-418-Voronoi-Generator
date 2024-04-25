

#include <GL/glut.h>
#include "headers/Callback.hpp"
#include "headers/DrawObjects.hpp"

bool isPaused;

// bool isPaused{ true }; // Whether the simulation is paused
namespace OGLcallbacks{
    void initOpenGL() {
        glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
        isPaused = true;
    }

    void update(int value) {
        if (!isPaused) {
            glutPostRedisplay(); // Redraw the window
        }
        glutTimerFunc(16, update, 0); // Schedule next update
    }

    void handleKeypress(unsigned char key, int x, int y) {
        switch (key) {
            case 'p': // Pause or unpause the simulation
                isPaused = !isPaused;
                break;
            case 's': // Step through the simulation one frame at a time
                if (isPaused) {
                    glutPostRedisplay(); // Redraw the scene immediately
                }
                break;
            default:
                break;
        }
        glutPostRedisplay(); // Redraw the scene immediately
    }

    void display() {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
        glLoadIdentity(); // Load the identity matrix to reset transformations

        // Draw the scene here
        
        //switch color to blue and draw the points
        glColor3f(0.0, 0.0, 1.0);
        DrawObjects::drawSites();


        glutSwapBuffers(); // Swap the front and back buffers
    }
}

