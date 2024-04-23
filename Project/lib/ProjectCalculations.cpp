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
    // std::priority_queue<Event, std::vector<Event>, Compare> eventQueue = std::priority_queue<Event, std::vector<Event>, Compare>();
    // SWTICHING FROM PRIORITY QUEUE TO VECTOR with HEAP OPERATIONS so I can remove circle events when one of their arcs is removed
    std::vector<Event> eventQueue = std::vector<Event>();
    std::make_heap(eventQueue.begin(), eventQueue.end(), Compare());

    // Fill Event Queue with starting points (sites) // given the feed in it becomes top to bottom right to left
    for (std::vector<Vertex>::iterator it = points->begin(); it != points->end(); ++it){ 
        eventQueue.push_back(Event(&(*it)));
        std::push_heap(eventQueue.begin(), eventQueue.end(), Compare());
    }

    beachline.sweepLine = points->front().y;

    while(!eventQueue.empty()){
        // Get the next event
        Event e = eventQueue.front();
        eventQueue.erase(eventQueue.begin());        
        std::pop_heap(eventQueue.begin(), eventQueue.end(), Compare());

        std::cout << e.getPoint()->x << " " << e.getPoint()->y << std::endl; 
        
        beachline.sweepLine = e.getPoint()->y;

        if (e.getType() == 0){
            // Site event
            // Insert the site into the beach line
            beachline.insert(*e.getPoint(), &eventQueue);
            // beachline.printTreeForest(beachline.getRoot());
        }else{
            // Circle event
            //temp print out circle event reached for now
            std::cout << "Circle Event at: " << e.getPoint()->x << " " << e.getPoint()->y << std::endl;
            // beachline.printTreeForest(beachline.getRoot());
            beachline.handleCircleEvent(&e, &eventQueue);
            // beachline.printTreeForest(beachline.getRoot());


            // Remove the circle event from the event queue
            // beachline.remove(e.getPoint());
            // Check for new circle events
            // Insert new circle events into the event queue
        }
    }

    // beachline.printTreeForest(beachline.getRoot());





    return dcel;
}

DCEL ProjectCalculations::calculateDelaunayTriangulation(){
    DCEL dcel;
    return dcel;
}