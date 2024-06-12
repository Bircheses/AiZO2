#include "PriorityQueueEdge.h"
#include <iostream>

PriorityQueueEdge::PriorityQueueEdge(int size) {
    Heap = new Edge[size];
    position = -1;
}

PriorityQueueEdge::~PriorityQueueEdge() {
    delete [] Heap;
}

void PriorityQueueEdge::push(Edge edge) {
    position++;
    Heap[position] = edge;
    PriorityQueueEdge::heapifyUp(position);
}

void PriorityQueueEdge::heapifyDown(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int smallest = i;
    if(left < position && Heap[left].weight < Heap[right].weight) smallest = left;
    if(right < position && Heap[right].weight < Heap[smallest].weight) smallest = right;
    if(smallest!=i){
        PriorityQueueEdge::swap(&Heap[i], &Heap[smallest]);
        heapifyDown(smallest);
    }
}

void PriorityQueueEdge::pop() {
    Heap[0] = Heap[position];
    position--;
    heapifyDown(0);
}

Edge PriorityQueueEdge::front() {
    return Heap[0];
}

void PriorityQueueEdge::swap(Edge *x, Edge *y) {
    Edge temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueueEdge::heapifyUp(int i) {
    while(i>0 && Heap[(i-1)/2].weight > Heap[i].weight){
        swap(&Heap[((i-1)/2)],&Heap[i]);
        i = (i-1)/2;
    }
}
