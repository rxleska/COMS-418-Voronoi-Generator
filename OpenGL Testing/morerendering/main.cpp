#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include "math.h"

static glm::vec3 pos(0.0f, 0.0f, 0.0f);
static glm::vec3 rotationalAxis(0.0f, 0.0f, 0.0f);
static glm::vec3 movement = glm::vec3(0.01f, 0.02f, 0.03f);
static float width = 1920;
static float height = 1080;
static float cubesize = 1080;

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
    s.z = s.z * 0.5f;
    return s;

}

void display()
{
    int i;
    int j;
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset the model-view matrix
    glLoadIdentity();  

    //set color to green
    glColor3f(0.0, 1.0, 0.0);

    glm::vec3 bound[8] = {
        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, 0.5)
    };

    glm::vec3 vertices[8] = {
        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(-0.5, 0.5, 0.5)
    };


    for(i = 0; i < 8; i++){
        vertices[i] = pos + vertices[i];
        vertices[i] = rotate(vertices[i], rotationalAxis);
        vertices[i] = scaleCube(vertices[i]);
    }
    for(i = 0; i < 8; i++){
        for(j = i+1; j < 8; j++){
            if((bound[i].x == bound[j].x) + (bound[i].y == bound[j].y) + (bound[i].z == bound[j].z) == 2){
                glBegin(GL_LINES);
                glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
                glVertex3f(vertices[j].x, vertices[j].y, vertices[j].z);
                glEnd();
            }
        }
    }

    //color red
    glColor3f(1.0, 0.0, 0.0);

    //draw a box at the edges of the screen (-1 to 1)
    for(i = 0; i < 8; i++){
        bound[i] = 1.0f * bound[i];
    }
    for(i = 0; i < 8; i++){
        for(j = i+1; j < 8; j++){
            if((bound[i].x == bound[j].x) + (bound[i].y == bound[j].y) + (bound[i].z == bound[j].z) == 2){
                glBegin(GL_LINES);
                glVertex3f(bound[i].x, bound[i].y, bound[i].z);
                glVertex3f(bound[j].x, bound[j].y, bound[j].z);
                glEnd();
            }
        }
    }



    // Flush the pipeline
    glFlush();
}

void update(int value){
    pos += movement;
    if(pos.x > 0.5f || pos.x < -0.5f){
        movement.x *= -1;
    }
    if(pos.y > 0.5f || pos.y < -0.5f){
        movement.y *= -1;
    }
    if(pos.z > 0.5f || pos.z < -0.5f){
        movement.z *= -1;
    }
    rotationalAxis += glm::vec3(0.01f, 0.02f, 0.0f);
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Cube");
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}