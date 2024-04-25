

#include "../CONST.hpp"
#include "headers/DrawObjects.hpp"
#include "../BeachLine/headers/BeachLine.hpp"
#include "../BeachLine/headers/ParabolaMath.hpp"



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

    void drawSweepLine(double y)
    {
        //draw a horizontal line at y
        glBegin(GL_LINES);
        glVertex2f(-1, y/windowHeight);
        glVertex2f(1, y/windowHeight);
        glEnd();
    }

    void drawBeachLine(){
        double y; 
        EdgeNode *edge;
        Arc *arc;

        glBegin(GL_LINE_STRIP);
        for(double i = -1; i <= 1; i += 0.01){
            edge = beachLine->search(i);

            if(ParabolaMath::areSameDouble(i, 0.0)){
                y = 0.0;
            }

            if(edge != nullptr){
                if(i*windowWidth < edge->getValue(SweepAnimationHeight)){
                    arc = edge->getLeftArc();
                }
                else{
                    arc = edge->getRightArc();
                }
                

                y = ParabolaMath::getParabolaYatX(i*windowWidth, arc->getX(), arc->getY(), SweepAnimationHeight);     

            }
            //place the point 
            glVertex2f(i, y/windowHeight);
        }
        glEnd();
    }
} // namespace DrawObjects
