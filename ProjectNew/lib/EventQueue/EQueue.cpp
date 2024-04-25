#include "headers/EQueue.hpp"
#include "../BeachLine/headers/ParabolaMath.hpp"

// private methods
void EventQueue::resize(){
    // double the capacity
    capacity *= 2;
    // create a new array
    Event **newEvents = new Event*[capacity];
    // copy the old array to the new array
    for(int i = 0; i < size; i++){
        newEvents[i] = events[i];
    }
    // delete the old array
    delete[] events;
    // set the new array to the old array
    events = newEvents;
}

int EventQueue::parent(int i){
    return (i-1)/2;
}

int EventQueue::left(int i){
    return 2*i + 1; //0s left child is 1, 1s left child is 3
}

int EventQueue::right(int i){
    return 2*i + 2; //0s right child is 2, 1s right child is 4
}

void EventQueue::shiftUp(int i){
    //if the node is not the root and the node is greater than its parent
    while(i > 0 && compare(events[i], events[parent(i)])){
        //swap the node with its parent
        swap(i, parent(i));
        //set the node to its parent
        shiftUp(parent(i));
    }
}

void EventQueue::shiftDown(int i){
    //if the node has a left child 
    if(left(i) < size){
        //if the node has a right child 
        if(right(i) < size){
            //if the left is greater than the right 
            if(compare(events[right(i)], events[left(i)])){
                //if the left is greater than the node
                if(compare(events[left(i)], events[i])){
                    //swap the left with the node
                    swap(i, left(i));
                    //set the node to the left
                    shiftDown(left(i));
                }
            }
            //if the right is greater than the left
            else{
                //if the right is greater than the node
                if(compare(events[right(i)], events[i])){
                    //swap the right with the node
                    swap(i, right(i));
                    //set the node to the right
                    shiftDown(right(i));
                }
            }
        }
        else{
            //if the left is greater than the node
            if(compare(events[left(i)], events[i])){
                //swap the left with the node
                swap(i, left(i));
                //set the node to the left
                shiftDown(left(i));
            }
        }
    }
}

void EventQueue::heapify(int i){
    //shift the node up
    shiftUp(i);
    //shift the node down
    shiftDown(i);
}

void EventQueue::swap(int i, int j){
    //swap the two nodes
    Event *temp = events[i];
    events[i] = events[j];
    events[j] = temp;
}

bool EventQueue::compare(Event *a, Event *b){
    //if y values are the same 
    if(ParabolaMath::areSameDouble(a->getY(), b->getY())){
        //return the smaller x value
        return ParabolaMath::isLessThanDouble(a->getX(), b->getX());
    }
    else if(ParabolaMath::isLessThanDouble(a->getY(), b->getY())){
        return true;
    }
    return false;
}

// public methods

// constructors
EventQueue::EventQueue(){
    //initialize the size and capacity
    size = 0;
    capacity = 20;
    //create the array
    events = new Event*[capacity];
}

EventQueue::EventQueue(int capacity){
    //initialize the size and capacity
    size = 0;
    this->capacity = capacity;
    //create the array
    events = new Event*[capacity];
}

// destructor
EventQueue::~EventQueue(){
    //delete the array
    delete[] events;
}

// add data to the queue
void EventQueue::insert(Event *event){
    //if the array is full
    if(size == capacity){
        //resize the array
        resize();
    }
    //add the event to the end of the array
    events[size] = event;
    //increment the size
    size++;
    //heapify the array
    heapify(size-1);
}

// get top of the queue
Event *EventQueue::peek(){
    //if the array is empty
    if(size == 0){
        //return null
        return nullptr;
    }
    //return the top of the array
    return events[0];
}

// remove top of the queue
Event *EventQueue::pop(){
    //if the array is empty
    if(size == 0){
        //return null
        return nullptr;
    }
    //get the top of the array
    Event *top = events[0];
    //set the top of the array to the end of the array
    events[0] = events[size-1];
    //decrement the size
    size--;
    //heapify the array
    heapify(0);
    //return the top of the array
    return top;
}

// remove a specific event from the queue
void EventQueue::remove(Event *event){
    //find the event in the array
    for(int i = 0; i < size; i++){
        //if the event is found
        if(events[i] == event){
            //set the event to the end of the array
            events[i] = events[size-1];
            //decrement the size
            size--;
            //heapify the array
            heapify(i);
            //break out of the loop
            break;
        }
    }
}

// get the size of the queue
int EventQueue::getSize(){
    return size;
}

// check if the queue is empty
bool EventQueue::isEmpty(){
    return size == 0;
}