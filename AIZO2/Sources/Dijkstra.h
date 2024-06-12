#ifndef AIZO2_DIJKSTRA_H
#define AIZO2_DIJKSTRA_H

#include "Containers/Structures.cpp"

class Dijkstra {
private:
    Vertex* answer;
    Edge** adjacencyList;
    int** incidenceMatrix;
    int* weight;
    int vertices;
    int edges;
public:
    Dijkstra(int** incidenceMatrix, int vertices, int edges, const int* weight);
    Dijkstra(Edge** adjacencyList, int vertices, int edges, const int* weight);
    ~Dijkstra();
    void sp_im(int vertex);
    void sp_al(int vertex);
    void printAnswer(int begin, int end);
};


#endif
