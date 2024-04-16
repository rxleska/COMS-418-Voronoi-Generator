//header file for Event (lib/Event.cpp), which represents a beach line event used in the Event_Queue

#include "Vertex.hpp"

#ifndef EVENT_HPP
#define EVENT_HPP


class Event{
    private:
        int type; // 0 if site event, 1 if circle event
        Vertex *point; // the point of the event
    public:
        Event();
        Event(int type, Vertex *point);
        int getType();
        Vertex* getPoint();
        void setType(int type);
        void setPoint(Vertex *point);
};


#endif // EVENT_HPP