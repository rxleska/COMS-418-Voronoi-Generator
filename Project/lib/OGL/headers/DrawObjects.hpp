#include "../../BeachLine/headers/BeachLine.hpp"
#include "../../DCEL/headers/Vertex.hpp"
#include <GL/glut.h>


#ifndef DRAW_OBJECTS_HPP
#define DRAW_OBJECTS_HPP

#include "../../CONST.hpp"


// BeachLine *beachLine;
// std::vector<Vertex> vertices;

namespace DrawObjects
{
    void drawSites();
    void drawSweepLine(double y);
    void drawBeachLine();

    void drawVerticalLine(double x);
    void drawHorizontalLine(double y);

    void drawArc(Arc *arc);
    void drawAllArcs();

    void drawHalfEdge(EdgeNode *edge);
    void drawAllHalfEdges();
    void drawAllHalfEdgesRec(EdgeNode *edge);

    void drawFinishedEdges();

    void drawDCEL(DCEL * thisDCEL);
    
} // namespace DrawObjects




#endif // DRAW_OBJECTS_HPP
