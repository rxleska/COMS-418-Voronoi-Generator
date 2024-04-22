//Header file for Event_Queue (lib/Event_Queue.cpp), which is a priority queue of beach line events


#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include "Event.hpp"

class Compare {
    public:
    bool operator()(Event below, Event above)
    {
        
        return ((below.getPoint()->y == above.getPoint()->y) ? (below.getPoint()->x < above.getPoint()->x) : (below.getPoint()->y < above.getPoint()->y));
    }
};

#endif