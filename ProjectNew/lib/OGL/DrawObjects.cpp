

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
            glVertex2f(v.getX()*widthScale/windowWidth, v.getY()*heightScale/windowHeight);
        }
        glEnd();
    }

    void drawSweepLine(double y)
    {
        //draw a horizontal line at y
        glBegin(GL_LINES);
        glVertex2f(-1, y*heightScale/windowHeight);
        glVertex2f(1, y*heightScale/windowHeight);
        glEnd();


        //draw a vertical line at -4.79231
        // glBegin(GL_LINES);
        // glVertex2f(5*widthScale/windowWidth, -1);
        // glVertex2f(5*widthScale/windowWidth, 1);
        // glEnd();

        //draw horizontal line at 4.50263
        // glBegin(GL_LINES);
        // glVertex2f(-1, -6.84987*heightScale/windowHeight);
        // glVertex2f(1, -6.84987*heightScale/windowHeight);
        // glEnd();
    }

    void drawVerticalLine(double x){
        //draw a vertical line at x
        glBegin(GL_LINES);
        glVertex2f(x*widthScale/windowWidth, -1);
        glVertex2f(x*widthScale/windowWidth, 1);
        glEnd();
    }

    void drawHorizontalLine(double y){
        //draw a horizontal line at y
        glBegin(GL_LINES);
        glVertex2f(-1, y*heightScale/windowHeight);
        glVertex2f(1, y*heightScale/windowHeight);
        glEnd();
    }

    void drawBeachLine(){
        double y; 
        EdgeNode *edge;
        Arc *arc;

        glBegin(GL_LINE_STRIP);
        for(double i = -1; i <= 1; i += 0.01){
            edge = beachLine->search(i*windowWidth/widthScale, SweepAnimationHeight);

            //DEBUG LOG edge choice at i
            //if(DEBUG) std::cout << "i: " << i << " edge: x:" << edge->getX() << " y:" << edge->getY() << " value: " << edge->getValue(SweepAnimationHeight) << " scaled i: " << i*windowWidth/widthScale << std::endl;

            //fix floating point error
            if(ParabolaMath::areSameDouble(i, 0.0)){
                i = 0.0;
            }

            if(edge != nullptr){
                if(i*windowWidth/widthScale < edge->getValue(SweepAnimationHeight)){
                    arc = edge->getLeftArc();
                    //if(DEBUG) std::cout << arc->getX() << std::endl;
                }
                else{
                    // if(DEBUG) std::cout << "right arc" << std::endl;
                    arc = edge->getRightArc();
                    //if(DEBUG) std::cout << arc->getX() << std::endl;

                }
                

                y = ParabolaMath::getParabolaYatX(i*windowWidth/widthScale, arc->getX(), arc->getY(), SweepAnimationHeight);     

            }
            //place the point 
            glVertex2f(i, y*heightScale/windowHeight);
        }
        glEnd();
    }

    void drawArc(Arc* arc){
        double y;
        glBegin(GL_LINE_STRIP);
        for(double i = -1; i <= 1; i += 0.01){
            y = ParabolaMath::getParabolaYatX(i*windowWidth/widthScale, arc->getX(), arc->getY(), SweepAnimationHeight); 
            //place the point 
            glVertex2f(i, y*heightScale/windowHeight);
        }
        glEnd();
    }

    void drawAllArcs(){
        for(Vertex v : vertices){
            Arc * arc = new Arc(v.getX(), v.getY());
            drawArc(arc);
            delete arc;
        }
    }

    void drawHalfEdge(EdgeNode *edge){
        glBegin(GL_LINES);
        glVertex2f(edge->getX()*widthScale/windowWidth, edge->getY()*heightScale/windowHeight);
        glVertex2f((edge->getX() + cos(edge->getAngle())*100)*widthScale/windowWidth, (edge->getY() + sin(edge->getAngle())*100)*heightScale/windowHeight);
        glEnd();
    }

    void drawAllHalfEdges(){
        drawAllHalfEdgesRec(beachLine->getRoot());
    }

    void drawAllHalfEdgesRec(EdgeNode *edge){
        if(edge == nullptr){
            return;
        }


        drawHalfEdge(edge);
        drawAllHalfEdgesRec(edge->getLeft());
        drawAllHalfEdgesRec(edge->getRight());
    }

    void drawFinishedEdges(){
        for(Edge * edge : finishedEdges){
            glBegin(GL_LINES);
            glVertex2f(edge->getOrigin()->getX()*widthScale/windowWidth, edge->getOrigin()->getY()*heightScale/windowHeight);
            glVertex2f(edge->getTwin()->getOrigin()->getX()*widthScale/windowWidth, edge->getTwin()->getOrigin()->getY()*heightScale/windowHeight);
            glEnd();
        }
    }

} // namespace DrawObjects
