// header file for ProjectCalculations class (lib/ProjectCalculations.cpp)
// the ProjectCalculations class will contain all of the functions that are used to calculate the voronoi diagram and delaunay triangulation of the voronoi diagram
#ifndef PROJECTCALCULATIONS_HPP
#define PROJECTCALCULATIONS_HPP

#include "headers/DCEL.hpp"

namespace ProjectCalculations{
    //function to calculate the voronoi diagram
    DCEL calculateVoronoiDiagram();
    //function to calculate the delaunay triangulation of the voronoi diagram
    DCEL calculateDelaunayTriangulation();
}


#endif