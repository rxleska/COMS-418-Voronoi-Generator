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
    
} // namespace DrawObjects




#endif // DRAW_OBJECTS_HPP
