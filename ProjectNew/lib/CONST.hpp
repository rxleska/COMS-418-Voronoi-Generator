
#include "BeachLine/headers/BeachLine.hpp"
#include "DCEL/headers/Vertex.hpp"


#ifndef CONST_HPP
#define CONST_HPP

class BeachLine;
class Vertex;

#define PI 3.14159265358979323846
#define DEBUG 1
#define EPSILON 0.0000001

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

extern BeachLine *beachLine;
extern std::vector<Vertex> vertices;
extern bool isPaused; // Whether the simulation is paused
extern double windowWidth;
extern double windowHeight;


#endif