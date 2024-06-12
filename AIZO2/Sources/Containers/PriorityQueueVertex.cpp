#include "PriorityQueueVertex.h"

PriorityQueueVertex::PriorityQueueVertex(int size) {
    Heap = new Vertex[size];
    position = -1;
}

PriorityQueueVertex::~PriorityQueueVertex() {
    delete [] Heap;
}

void PriorityQueueVertex::push(Vertex vertex) {
    position++;
    Heap[position] = vertex;
    PriorityQueueVertex::heapifyUp(position);
}

void PriorityQueueVertex::heapifyDown(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int smallest = i;
    if(left < position && Heap[left].distance < Heap[right].distance) smallest = left;
    if(right < position && Heap[right].distance < Heap[smallest].distance) smallest = right;
    if(smallest!=i){
        PriorityQueueVertex::swap(&Heap[i], &Heap[smallest]);
        heapifyDown(smallest);
    }
}

void PriorityQueueVertex::pop() {
    Heap[0] = Heap[position];
    position--;
    heapifyDown(0);
}

Vertex PriorityQueueVertex::front() {
    Vertex vertex{-1,-1,-1};
    if(position==-1) return vertex;
    return Heap[0];
}

void PriorityQueueVertex::swap(Vertex *x, Vertex *y) {
    Vertex temp = *x;
    *x = *y;
    *y = temp;
}

void PriorityQueueVertex::heapifyUp(int i) {
    while(i>0 && Heap[(i-1)/2].distance > Heap[i].distance){
        swap(&Heap[((i-1)/2)],&Heap[i]);
        i = (i-1)/2;
    }
}

