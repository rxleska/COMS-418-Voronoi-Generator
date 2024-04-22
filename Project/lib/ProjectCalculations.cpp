#include "headers/ProjectCalculations.hpp"
#include "headers/DCEL.hpp"
#include "headers/Beach_Line_RedBlackTree.hpp"
#include "headers/Event_Queue.hpp"
#include "headers/Event.hpp"
#include <algorithm>
#include <iostream>


bool comparePoints(Vertex a, Vertex b){
    return ((a.y == b.y) ? (a.x < b.x) : (a.y < b.y)); // y bottom to top, x left to right
}


DCEL ProjectCalculations::calculateVoronoiDiagram(std::vector<Vertex> *points){
    DCEL dcel = DCEL();

    // Initialize the beach line (BST of parabolas)
    BeachLineRedBlackTree beachline = BeachLineRedBlackTree();

    // Initialize the event queue (PQ of points)
    std::priority_queue<Event, std::vector<Event>, Compare> eventQueue = std::priority_queue<Event, std::vector<Event>, Compare>();

    // Sort the points by y-coordinate
    std::sort(points->begin(), points->end(), comparePoints);

    // Fill Event Queue with starting points (sites) // given the feed in it becomes top to bottom right to left
    for (std::vector<Vertex>::iterator it = points->begin(); it != points->end(); ++it){ 
        eventQueue.push(Event(0, &(*it)));
    }

    beachline.sweepLine = points->front().y;

    while(!eventQueue.empty()){
        Event e = eventQueue.top();
        eventQueue.pop();

        std::cout << e.getPoint()->x << " " << e.getPoint()->y << std::endl; 
        
        beachline.sweepLine = e.getPoint()->y;
        beachline.insert(*e.getPoint(), &eventQueue);

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