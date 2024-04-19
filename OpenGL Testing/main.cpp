#include <GL/glut.h> 
#include <math.h>


#define WINDOW_WIDTH  500
#define WINDOW_HEIGHT 500


void display(){
    glClear(GL_COLOR_BUFFER_BIT);//clear the screen

    //set the color to red
    glColor3f(1.0, 0.0, 0.0);


    // Begin drawing lines 
    glBegin(GL_LINES);
        glVertex2f(-0.5, 0.0); //start point
        glVertex2f(0.5, 0.0); //end point

        glVertex2f(0.0, -0.5); //start point
        glVertex2f(0.0, 0.5); //end point
    glEnd();

    // set the color to green
    glColor3f(0.0, 1.0, 0.0);

    // draw a parabola
    glBegin(GL_LINE_STRIP);
        for (float x = -1.0; x <= 1.0; x += 0.01){
            glVertex2f(x, x*x);
        }
    glEnd();

    // set the color to blue
    glColor3f(0.0, 0.0, 1.0);

    // draw a circle
    glBegin(GL_LINE_LOOP);
        for (float angle = 0; angle <= 2*3.14159; angle += 0.01){
            glVertex2f(cos(angle), sin(angle));
        }
    glEnd();


    glFlush(); //Ensure all commands are executed before continuing
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutCreateWindow("OpenGL Line Drawing Example"); // Create a window with a title
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Set the window's initial width & height
    glutDisplayFunc(display); // Register display callback function
    glutMainLoop(); // Enter the GLUT event loop

    return 0;
}