#ifndef AIZO2_PRIORITYQUEUEVERTEX_H
#define AIZO2_PRIORITYQUEUEVERTEX_H

#include "Structures.cpp"

class PriorityQueueVertex {
private:
    Vertex* Heap;
    int position;
    void heapifyDown(int i);
    void heapifyUp(int i);
    static void swap (Vertex* x, Vertex* y);
public:
    PriorityQueueVertex(int size);
    ~PriorityQueueVertex();
    void push(Vertex vertex);
    void pop();
    Vertex front();
};


#endif
