#include "headers/ProjectCalculations.hpp"
#include "headers/DCEL.hpp"
#include "Beach_Line_RedBlackTree.cpp"
#include "headers/Event_Queue.hpp"
#include "headers/Event.hpp"
#include <algorithm>
#include "headers/DEBUG.hpp"


// static float sweepLine = 0;

bool comparePoints(Vertex a, Vertex b){
    return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); // y bottom to top, x left to right
}


DCEL ProjectCalculations::calculateVoronoiDiagram(std::vector<Vertex> *points){
    DCEL dcel = DCEL();

    // Initialize the beach line (BST of parabolas)
    RBTree beachline = RBTree();

    // Initialize the event queue (PQ of points)
    // Im just going to use a vector (then use modifications to the vector to maintain the PQ property)
    // i.e. on circle events
    std::vector<Event> eventQueue = std::vector<Event>();

    //get min x and max x, min y and max y
    float minX = points->at(0).x;
    float maxX = points->at(0).x;
    float minY = points->at(0).y;
    float maxY = points->at(0).y;
    for (std::vector<Vertex>::iterator it = points->begin(); it != points->end(); ++it){
        if (it->x < minX){
            minX = it->x;
        }
        if (it->x > maxX){
            maxX = it->x;
        }
        if (it->y < minY){
            minY = it->y;
        }
        if (it->y > maxY){
            maxY = it->y;
        }
    }

    //define a bounding box 
    float boundingBoxWidth = maxX - minX;
    float boundingBoxHeight = maxY - minY;
    //make bounding box 10% larger 
    float boundingBoxMinX = minX - boundingBoxWidth * 0.1;
    float boundingBoxMaxX = maxX + boundingBoxWidth * 0.1;
    float boundingBoxMinY = minY - boundingBoxHeight * 0.1;
    float boundingBoxMaxY = maxY + boundingBoxHeight * 0.1;
    //reset the bounding box width and height
    boundingBoxWidth = boundingBoxMaxX - boundingBoxMinX;
    boundingBoxHeight = boundingBoxMaxY - boundingBoxMinY;


    // Sort the points by y-coordinate
    std::sort(points->begin(), points->end(), comparePoints);



    // Fill Event Queue with starting points (sites) // given the feed in it becomes top to bottom right to left
    for (std::vector<Vertex>::iterator it = points->begin(); it != points->end(); ++it){ 
        eventQueue.push_back(Event(0, &(*it)));
    }

    while(!eventQueue.empty()){
        Event e = eventQueue.back();
        eventQueue.pop_back();
        std::cout << e.getPoint()->x << " " << e.getPoint()->y << std::endl; 
        if (e.getType() == 0){
            // Site event
            // Insert the site into the beach line


            // beachline.insert(e.getPoint());
        }else{
            // Circle event
            // Remove the circle event from the event queue
            // beachline.remove(e.getPoint());
            // Check for new circle events
            // Insert new circle events into the event queue
        }
    }





    return dcel;
}

DCEL ProjectCalculations::calculateDelaunayTriangulation(){
    DCEL dcel;
    return dcel;
}