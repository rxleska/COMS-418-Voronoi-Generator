#include "headers/ProjectCalculations.hpp"
#include "headers/DCEL.hpp"
#include "Beach_Line_RedBlackTree.cpp"
#include "headers/Event_Queue.hpp"
#include "headers/Event.hpp"
#include <algorithm>


bool comparePoints(Vertex a, Vertex b){
    return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); // y bottom to top, x left to right
}


DCEL ProjectCalculations::calculateVoronoiDiagram(std::vector<Vertex> *points){
    DCEL dcel = DCEL();

    // Initialize the beach line (BST of parabolas)
    // RBTree beachline = RBTree();

    // Initialize the event queue (PQ of points)
    // Im just going to use a vector (then use modifications to the vector to maintain the PQ property)
    // i.e. on circle events
    std::vector<Event> eventQueue = std::vector<Event>();

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