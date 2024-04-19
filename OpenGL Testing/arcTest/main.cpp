#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Constants for the window size
const int windowWidth = 800;
const int windowHeight = 600;

// Variables to control the directrix line
float directrixY = 1.0;
float speed = 0.005;

// Function to initialize OpenGL
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
}

// Function to update the position of the directrix
void update(int value) {
    directrixY -= speed; // Move the line down
    if (directrixY < -1.0) {
        directrixY = 1.0; // Reset the line to the top
    }

    glutPostRedisplay(); // Redraw the window
    glutTimerFunc(16, update, 0); // Schedule next update
}

// Function to draw an arc based on the directrix and focus point
void drawArc(float focusX, float focusY) {
    // float focusX = 0.0, focusY = 0.0; // Focus at the center
    //draw focus point 
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_POINTS); 
    glVertex2f(focusX, focusY);
    glEnd();

    //set color to green
    glColor3f(0.0, 1.0, 0.0); // Green color
    

    glBegin(GL_LINE_STRIP);
    for (float i = -1.0; i <= 1; i+=0.005) { 
        float y = (1/(2*(focusY-directrixY)))*(i - focusX)*(i-focusX) + (focusY+directrixY)/2;

        glVertex2f(i, y);
    }
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations

    // Set up the view
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Draw the directrix
    glColor3f(1.0, 0.0, 0.0); // Red color
    glBegin(GL_LINES);
    glVertex2f(-1.0, directrixY);
    glVertex2f(1.0, directrixY);
    glEnd();

    // Draw the arc
    glColor3f(0.0, 1.0, 0.0); // Green color
    drawArc(0.0,0.0);
    drawArc(0.3,0.5);

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Set the display mode
    glutInitWindowSize(windowWidth, windowHeight); // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("Arc and Moving Directrix"); // Create the window

    initOpenGL(); // Initialize OpenGL

    glutDisplayFunc(display); // Register display callback
    glutTimerFunc(0, update, 0); // Register timer callback

    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
}
