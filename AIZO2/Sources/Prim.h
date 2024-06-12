#ifndef AIZO2_PRIM_H
#define AIZO2_PRIM_H

#include "Containers/Structures.cpp"

class Prim {
private:
    Edge* answer;
    Edge** adjacencyList;
    int** incidenceMatrix;
    int* weight;
    int vertices;
    int edges;
public:
    Prim(int** incidenceMatrix, int vertices, int edges, const int* weight);
    Prim(Edge** adjacencyList, int vertices, int edges, const int* weight);
    ~Prim();
    void mst_im();
    void mst_al();
    void printAnswer();
};


#endif //AIZO2_PRIM_H
