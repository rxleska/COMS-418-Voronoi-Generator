#ifndef CONST_HPP
#define CONST_HPP


#include "BeachLine/headers/BeachLine.hpp"
#include "EventQueue/headers/EQueue.hpp"
#include "DCEL/headers/Vertex.hpp"
#include "DCEL/headers/Edge.hpp"

// Forward declarations
class BeachLine;
class EventQueue;
class Vertex;
class Edge;

#define PI 3.14159265358979323846
#define DEBUG 1
#define DENOTEHANDLE 1
#define EPSILON 0.00001

#define boundingScale 0.1

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

extern BeachLine *beachLine;
extern std::vector<Vertex> vertices;
extern std::vector<Edge *> finishedEdges; //will be replaced with extern DCEL
extern EventQueue *eventQueue;
extern bool isPaused; // Whether the simulation is paused
extern double SweepAnimationHeight;
extern double windowWidth;
extern double windowHeight;
extern double widthScale;   
extern double heightScale;
extern bool drawAllArcs;
extern bool drawAllHalfEdges;
extern std::vector<CircleEvent *> circleEvents; //used for removing circle events that are no longer valid


#endif