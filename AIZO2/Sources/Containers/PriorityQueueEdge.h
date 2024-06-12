#ifndef AIZO2_PRIORITYQUEUEEDGE_H
#define AIZO2_PRIORITYQUEUEEDGE_H

#include "Structures.cpp"

class PriorityQueueEdge {
private:
    Edge* Heap;
    int position;
    void heapifyDown(int i);
    void heapifyUp(int i);
    static void swap (Edge* x, Edge* y);
public:
    PriorityQueueEdge(int size);
    ~PriorityQueueEdge();
    void push(Edge edge);
    void pop();
    Edge front();
};


#endif
