#include "headers/EQueue.hpp"
#include "../BeachLine/headers/ParabolaMath.hpp"

//forward declarations
// std::vector<CircleEvent *> circleEvents;

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
    while(i > 0 && compare(events[i], events[parent(i)])){
        swap(i, parent(i));
        i = parent(i);  // Move up to the next parent level
    }
}


void EventQueue::shiftDown(int i){
    while(left(i) < size){  // ensure loop continues until no left child
        int largest = left(i);
        int rightIndex = right(i);

        if(rightIndex < size && compare(events[rightIndex], events[largest])){
            largest = rightIndex;
        }
        if(compare(events[largest], events[i])){
            swap(i, largest);
            i = largest;  // Continue down the tree from the largest child
        } else {
            break;  // If no swap needed, the heap property is restored
        }
    }
}


void EventQueue::heapify(int i){
    if (i == 0) {
        // Only shift down if it's the root node, since there's no parent to compare.
        shiftDown(i);
    } else {
        int parentIdx = parent(i);
        // Decide to shift up or down based on comparison with the parent
        if (compare(events[i], events[parentIdx])) {
            // If current is greater than parent in a max heap, shift up
            shiftUp(i);
        } else {
            // Otherwise, potentially shift down
            shiftDown(i);
        }
    }
}

void EventQueue::swap(int i, int j){
    //swap the two nodes
    Event *temp = events[i];
    events[i] = events[j];
    events[j] = temp;
}

bool EventQueue::compare(Event *a, Event *b){
    // Prioritize by y value, larger y is better
    if (ParabolaMath::isGreaterThanDouble(a->getY(), b->getY())) {
        return true;
    } else if (ParabolaMath::areSameDouble(a->getY(), b->getY())) {
        // if y is teh same prioritize site events
        if (a->getIsCircle() && !b->getIsCircle()) {
            return true;
        } else if (!a->getIsCircle() && b->getIsCircle()) {
            return false;
        }
        // If y is the same, use x value, smaller x is better
        return ParabolaMath::isLessThanDouble(a->getX(), b->getX());
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

// print the queue
void EventQueue::printQueue(){
    //print the size and capacity
    std::cout << "Size: " << size << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    //print the events
    for(int i = 0; i < size; i++){
        std::cout << "Event " << i << ": " << (events[i]->getIsCircle() ? "CE" : "SE") <<" (" << events[i]->getX() << ", " << events[i]->getY() << ")" << std::endl;
    }
}