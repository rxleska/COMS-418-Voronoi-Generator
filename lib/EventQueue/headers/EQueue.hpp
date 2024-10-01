

// Summary: This header file contains the EventQueue class which is used to store the events in the system. Plan to implement a tree based heap as a priority queue to store the events.
#ifndef EQUEUE_HPP
#define EQUEUE_HPP

#include "../../CONST.hpp"
#include "Event.hpp"

class EventQueue{
    private:
        int size;
        int capacity;
        Event **events; //dynamically scaling array of events
        void resize(); //reallocates the array to double the capacity

        // node methods
        int parent(int i);
        int left(int i);
        int right(int i);
        // heap methods
        void shiftUp(int i);
        void shiftDown(int i);
        void heapify(int i);
        void swap(int i, int j);
        bool compare(Event *a, Event *b);
    public:
        EventQueue();
        EventQueue(int capacity);
        ~EventQueue();

        //add data to the queue
        void insert(Event *event);

        //get top of the queue
        Event *peek();

        //remove top of the queue
        Event *pop();

        //remove a specific event from the queue
        void remove(Event *event);

        //get the size of the queue
        int getSize();

        //check if the queue is empty
        bool isEmpty();

        //print the queue
        void printQueue();
};



#endif