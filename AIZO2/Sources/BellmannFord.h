#ifndef AIZO2_BELLMANNFORD_H
#define AIZO2_BELLMANNFORD_H

#include "Containers/Structures.cpp"

class BellmannFord {
private:
    Vertex* answer;
    Edge** adjacencyList;
    int** incidenceMatrix;
    int* weight;
    int vertices;
    int edges;
public:
    BellmannFord(int** incidenceMatrix, int vertices, int edges, const int* weight);
    BellmannFord(Edge** adjacencyList, int vertices, int edges, const int* weight);
    ~BellmannFord();
    void sp_im(int vertex);
    void sp_al(int vertex);
    void printAnswer(int begin, int end);
};


#endif
