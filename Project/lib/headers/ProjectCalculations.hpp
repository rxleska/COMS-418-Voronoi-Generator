// header file for ProjectCalculations class (lib/ProjectCalculations.cpp)
// the ProjectCalculations class will contain all of the functions that are used to calculate the voronoi diagram and delaunay triangulation of the voronoi diagram
#ifndef PROJECTCALCULATIONS_HPP
#define PROJECTCALCULATIONS_HPP

#include "DCEL.hpp"
#include "Vertex.hpp"
#include <vector>
#include <queue>
#include "Event.hpp"
#include "Event_Queue.hpp"

bool comparePoints(Vertex a, Vertex b);

namespace ProjectCalculations{
    //function to order two points by y-coordinate used when implementing sorting the points in the event queue
    
    //function to calculate the voronoi diagram
    DCEL calculateVoronoiDiagram(std::vector<Vertex> *points);
    //function to calculate the delaunay triangulation of the voronoi diagram
    DCEL calculateDelaunayTriangulation();
}


#endif