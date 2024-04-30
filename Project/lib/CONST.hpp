#ifndef CONST_HPP
#define CONST_HPP


#include "BeachLine/headers/BeachLine.hpp"
#include "EventQueue/headers/EQueue.hpp"
#include "EventQueue/headers/Event.hpp"
#include "DCEL/headers/Vertex.hpp"
#include "DCEL/headers/Edge.hpp"
#include "DCEL/headers/DCEL.hpp"
#include "DCEL/headers/PseudoEdge.hpp"

// Forward declarations
class BeachLine;
class EventQueue;
class Vertex;
class Edge;
class DCEL;
class PsuedoEdge;

#define PI 3.14159265358979323846
#define CRITICALDEBUG 1
#define DEBUG 0 // Debug
#define VDEBUG 0 //Verbose Debug
#define DENOTEHANDLE 0
#define EPSILON 0.00001

#define boundingScale 0.1

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>



extern DCEL *dcel;
extern DCEL *dcelDelaunay;
extern BeachLine *beachLine;
extern std::vector<Vertex> vertices;
extern std::vector<Edge *> finishedEdges; //will be replaced with extern DCEL
extern std::vector<CircleEvent *> circleEvents; //used for removing circle events that are no longer valid
extern EventQueue *eventQueue;
extern bool isPaused; // Whether the simulation is paused
extern double SweepAnimationHeight;
extern double windowWidth;
extern double windowHeight;
extern double widthScale;   
extern double heightScale;
extern bool drawAllArcs;
extern bool drawAllHalfEdges;
extern bool hasEnded;

extern std::vector<PseudoEdge> pseudoEdges;


#endif