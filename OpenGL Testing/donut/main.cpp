#include <GL/glut.h>
#include <GL/gl.h>
#include <glm/gtx/transform.hpp>
#include "math.h"

static glm::vec3 offset(0.3f, 0.0f, 0.0f);
#define mainRadius 0.6f
#define circleRadius 0.15f
#define width 1920.0f
#define height 1080.0f
#define radiusPerSection 3.5f

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

glm::vec3 placeInFrame(glm::vec3 s){
    return glm::vec3(s.x / (width / height), s.y, s.z);
}

float toRadian(float x){
    return x * 3.14159f / 180.0f;
}
float toRadian(int x){
    return x * 3.14159f / 180.0f;
}


void display()
{
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset the model-view matrix
    glLoadIdentity();  

    //set color green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(float i = 0.0f; i < 360; i+=radiusPerSection){
        glm::vec3 circleCenter = glm::vec3(mainRadius * cos(toRadian(i)), 0.0f,  mainRadius * sin(toRadian(i)));      
        glm::vec3 rotatedCircleCenter = rotate(circleCenter, offset);
        rotatedCircleCenter = placeInFrame(rotatedCircleCenter);

        glVertex3f(rotatedCircleCenter.x, rotatedCircleCenter.y, rotatedCircleCenter.z);
    }
    glEnd();
    
    //place center point
    glBegin(GL_POINT);
        glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    // Set the color
    glColor3f(1.0, 0.0, 0.0);

    //draw a torus using a sequence of circles
    //vertical circles

    for(float i = 0.0f; i < 360; i+=radiusPerSection){
        glm::vec3 circleCenter = glm::vec3(mainRadius * cos(toRadian(i)), 0.0f, mainRadius * sin(toRadian(i)));   

        // for each centerpoint draw a circle tangent to the centerpoint
        glBegin(GL_LINE_LOOP);
        for(float j = 0.0f; j < 360; j+=radiusPerSection){
            //get circle point
            glm::vec3 subcirclePosition = glm::vec3(circleRadius * cos(toRadian(j)), circleRadius * sin(toRadian(j)), 0.0f);
            //rotate circle to normal of circleCenter on outer circle
            subcirclePosition = rotate(subcirclePosition, glm::vec3( 0.0f, toRadian(i), 0.0f));
            //translate to circleCenter
            subcirclePosition = subcirclePosition + circleCenter;
            //rotate to offset
            subcirclePosition = rotate(subcirclePosition, offset);

            //place in fraem 
            subcirclePosition = placeInFrame(subcirclePosition);

            //place point on line loop
            glVertex3f(subcirclePosition.x, subcirclePosition.y, subcirclePosition.z);
            

        }
        glEnd();
    }
    //horizontal circles
    //todo:
    for(float i = 0.0f; i < 360; i+=radiusPerSection){

        // for each centerpoint draw a circle tangent to the centerpoint
        glBegin(GL_LINE_LOOP);
        for(float j = 0.0f; j < 360; j+=radiusPerSection){
            glm::vec3 circleCenter = glm::vec3(mainRadius * cos(toRadian(j)), 0.0f, mainRadius * sin(toRadian(j)));   
            //get circle point
            glm::vec3 subcirclePosition = glm::vec3(circleRadius * cos(toRadian(i)), circleRadius * sin(toRadian(i)), 0.0f);
            //rotate circle to normal of circleCenter on outer circle
            subcirclePosition = rotate(subcirclePosition, glm::vec3( 0.0f, toRadian(j), 0.0f));
            //translate to circleCenter
            subcirclePosition = subcirclePosition + circleCenter;
            //rotate to offset
            subcirclePosition = rotate(subcirclePosition, offset);

            //place in fraem 
            subcirclePosition = placeInFrame(subcirclePosition);

            //place point on line loop
            glVertex3f(subcirclePosition.x, subcirclePosition.y, subcirclePosition.z);
            

        }
        glEnd();
    }

    // Flush the pipeline
    glFlush();
}

void update(int value){
    offset.x += 0.01f;
    offset.y += 0.02f;
    // offset.z += 0.00f;
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Torus");
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}