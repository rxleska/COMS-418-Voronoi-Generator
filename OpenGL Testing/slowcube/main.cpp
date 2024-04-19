#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include "math.h"





static glm::vec3 center(0.0f, 0.0f, 0.0f);
static glm::vec3 rotationalAxis(0.0f, 0.0f, 0.0f);
static glm::movement = glm::vec3(0.1f, 0.2f, 0.3f);
static float width = 1920;
static float height = 1080;
static float cubesize = 200;

// define a function to rotate a point 
glm::vec3 rotate(glm::vec3 s, glm::vec3 rot){
    glm::mat3 rotateX = glm::mat3(
        1.0f, 0.0f, 0.0f,
        0.0f, cos(rot.x), -sin(rot.x),
        0.0f, sin(rot.x), cos(rot.x)
    );

    glm::mat3 rotateY = glm::mat3(
        cos(rot.y), 0.0f, sin(rot.y),
        0.0f, 1.0f, 0.0f,
        -sin(rot.y), 0.0f, cos(rot.y)
    );

    glm::mat3 rotateZ = glm::mat3(
        cos(rot.z), -sin(rot.z), 0.0f,
        sin(rot.z), cos(rot.z), 0.0f,
        0.0f, 0.0f, 1.0f
    );

    return rotateZ * rotateY * rotateX * s;

}

glm::vec3 scaleCube(glm::vec3 s){
    //scale the cube to fit the screen
    s.x = s.x * (cubesize / width);
    s.y = s.y * (cubesize / height);
    return s;

}


// Function to draw the cube
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    //set color to green
    glColor3f(0.0, 1.0, 0.0);
    //draw each of the line
    glm::vec3 p1(center.x - 0.5, center.y - 0.5, center.z - 0.5);
    glm::vec3 p2(center.x + 0.5, center.y - 0.5, center.z - 0.5);
    glm::vec3 p3(center.x + 0.5, center.y + 0.5, center.z - 0.5);
    glm::vec3 p4(center.x - 0.5, center.y + 0.5, center.z - 0.5);
    glm::vec3 p5(center.x - 0.5, center.y - 0.5, center.z + 0.5);
    glm::vec3 p6(center.x + 0.5, center.y - 0.5, center.z + 0.5);
    glm::vec3 p7(center.x + 0.5, center.y + 0.5, center.z + 0.5);
    glm::vec3 p8(center.x - 0.5, center.y + 0.5, center.z + 0.5);
    p1 = rotate(p1, rotationalAxis);
    p2 = rotate(p2, rotationalAxis);
    p3 = rotate(p3, rotationalAxis);
    p4 = rotate(p4, rotationalAxis);
    p5 = rotate(p5, rotationalAxis);
    p6 = rotate(p6, rotationalAxis);
    p7 = rotate(p7, rotationalAxis);
    p8 = rotate(p8, rotationalAxis);
    p1 = scaleCube(p1);
    p2 = scaleCube(p2);
    p3 = scaleCube(p3);
    p4 = scaleCube(p4);
    p5 = scaleCube(p5);
    p6 = scaleCube(p6);
    p7 = scaleCube(p7);
    p8 = scaleCube(p8);


    //front face
    glBegin(GL_LINES);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p4.x, p4.y, p4.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glEnd();

    //back face
    glBegin(GL_LINES);
    glVertex3f(p5.x, p5.y, p5.z);
    glVertex3f(p6.x, p6.y, p6.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p6.x, p6.y, p6.z);
    glVertex3f(p7.x, p7.y, p7.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p7.x, p7.y, p7.z);
    glVertex3f(p8.x, p8.y, p8.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p8.x, p8.y, p8.z);
    glVertex3f(p5.x, p5.y, p5.z);
    glEnd();

    //connecting lines
    glBegin(GL_LINES);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p5.x, p5.y, p5.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p6.x, p6.y, p6.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p7.x, p7.y, p7.z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(p4.x, p4.y, p4.z);
    glVertex3f(p8.x, p8.y, p8.z);
    glEnd();

    glFlush();
}

void update(int value){
    rotationalAxis.y += 0.01;
    rotationalAxis.x += 0.015;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutCreateWindow("Cube");
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;

}