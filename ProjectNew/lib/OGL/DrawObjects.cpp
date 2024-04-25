

#include "../CONST.hpp"
#include "headers/DrawObjects.hpp"


namespace DrawObjects
{
    void drawSites()
    {
        glPointSize(5);
        glBegin(GL_POINTS);
        for (Vertex v : vertices)
        {
            glVertex2f(v.getX()/windowWidth, v.getY()/windowHeight);
        }
        glEnd();
    }
} // namespace DrawObjects
