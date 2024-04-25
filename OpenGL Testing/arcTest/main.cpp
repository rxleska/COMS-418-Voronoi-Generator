#include <GL/glut.h>
#include <cmath>
#include <iostream>
// ncurse
#include <ncurses.h>

// Constants for the window size
const int windowWidth = 256;
const int windowHeight = 144;

// Variables to control the directrix line
float directrixY = 1.0;
float speed = 0.005;

// Function to initialize OpenGL
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
}

// Function to update the position of the directrix
void update(int value) {
    // directrixY -= speed; // Move the line down (commented out to control via keyboard)
    if (directrixY < -1.0) {
        directrixY = 1.0w; // Reset the line to the top
    }

    glutPostRedisplay(); // Redraw the window
    glutTimerFunc(16, update, 0); // Schedule next update
}

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Move the directrix up
            directrixY += speed;
            break;
        case 's': // Move the directrix down
            directrixY -= speed;
            break;
        default:
            break;
    }
    glutPostRedisplay(); // Redraw the scene immediately
}

// Function to draw an arc based on the directrix and focus point
void drawArc(float focusX, float focusY) {
    glColor3f(1.0, 1.0, 1.0); // White color for focus point
    glBegin(GL_POINTS);
    glVertex2f(focusX, focusY);
    glEnd();

    glColor3f(0.0, 1.0, 0.0); // Green color for arc
    glBegin(GL_LINE_STRIP);
    for (float i = -1.0; i <= 1; i += 0.005) {
        float y = (1 / (2 * (focusY - directrixY))) * (i - focusX) * (i - focusX) + (focusY + directrixY) / 2;
        glVertex2f(i, y);
    }
    glEnd();
}

// Function to display the scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    glLoadIdentity(); // Reset transformations
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); // Red color for directrix
    glBegin(GL_LINES);
    glVertex2f(-1.0, directrixY);
    glVertex2f(1.0, directrixY);
    glEnd();

    drawArc(0.0, 0.0); // Draw arcs
    drawArc(0.3, 0.5);

    glutSwapBuffers(); // Double buffering
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Arc and Moving Directrix");

    initOpenGL();
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress); // Register keyboard callback
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
