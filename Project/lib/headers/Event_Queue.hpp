//Header file for Event_Queue (lib/Event_Queue.cpp), which is a priority queue of beach line events


#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"
#include <vector>

class Compare {
    public:
    bool operator()(Event below, Event above)
    {
        if(below.getPoint() == nullptr || above.getPoint() == nullptr)
        {
            return false; //return false if either of the points are null
        }        
        return ((below.getPoint()->y == above.getPoint()->y) ? (below.getPoint()->x < above.getPoint()->x) : (below.getPoint()->y < above.getPoint()->y));
    }
};

#endif