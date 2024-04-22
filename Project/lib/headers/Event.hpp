//header file for Event (lib/Event.cpp), which represents a beach line event used in the Event_Queue

#include "Vertex.hpp"
#include "Beach_Line_RedBlackTree.hpp"


#ifndef EVENT_HPP
#define EVENT_HPP

class CircleEvent{
    public:
        Node *leftEdge;
        Node *rightEdge;
        Node *pinchingArc;
        CircleEvent(Node *leftEdge, Node *rightEdge, Node *pinchingArc);
        ~CircleEvent();

};

class Event{
    private:
        int type; // 0 if site event, 1 if circle event
        Vertex *point; // the point of the event
        CircleEvent *circleEvent;
    public:
        Event();
        Event(Vertex *point);
        Event(CircleEvent *circleEvent);
        Event(Vertex *point, Node *leftEdge, Node *rightEdge, Node *pinchingArc);
        Event(Event const &event);
        ~Event();
        int getType();
        CircleEvent* getCircleEvent();
        Vertex* getPoint();
        void setType(int type);
        void setPoint(Vertex *point);
        void setCircleEvent(CircleEvent *circleEvent);
};


#endif // EVENT_HPP