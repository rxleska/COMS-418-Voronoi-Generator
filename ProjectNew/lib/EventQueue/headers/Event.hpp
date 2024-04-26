


#include "../../CONST.hpp"
#include "../../BeachLine/headers/EdgeNode.hpp"

// Summary: This is a header file for the Event class, stores circle events and site events
#ifndef EVENT_HPP
#define EVENT_HPP


class Event{
    private:
        static int count; //number of events created
        double x;
        double y;
        bool isCircle;
        bool isSite;
        bool isDeleted;
        int index;
    public:
        Event();
        Event(double x, double y, bool isCircle, bool isSite);
        Event(double x, double y, bool isCircle, bool isSite, int index);
        ~Event();
        double getX();
        double getY();
        bool getIsCircle();
        bool getIsSite();
        bool getIsDeleted();
        int getIndex();
        void setX(double x);
        void setY(double y);
        void setIsCircle(bool isCircle);
        void setIsSite(bool isSite);
        void setIsDeleted(bool isDeleted);
        void setIndex(int index);
        //overload the = operator
        Event& operator=(const Event &e);
        //copy constructor
        Event(const Event &e);

        // virtual function to handle the event
        virtual void handleEvent() = 0;
};

// child class for circle events
class CircleEvent : public Event{
    private:
        EdgeNode *leftEdge; 
        EdgeNode *rightEdge;
        double intersectionY;
    public: 
        CircleEvent();
        CircleEvent(double x, double y, double isy, EdgeNode *leftEdge, EdgeNode *rightEdge);
        ~CircleEvent();
        EdgeNode *getLeftEdge();
        EdgeNode *getRightEdge();
        double getIntersectionY();
        void setLeftEdge(EdgeNode *leftEdge);
        void setRightEdge(EdgeNode *rightEdge);
        void setIntersectionY(double intersectionY);
        void handleEvent();
};

// child class for site events
class SiteEvent : public Event{
    //no extra vars needed
    public: 
        SiteEvent();
        SiteEvent(double x, double y);
        ~SiteEvent();
        void handleEvent();
};
        

#endif
