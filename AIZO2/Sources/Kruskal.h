#ifndef AIZO2_KRUSKAL_H
#define AIZO2_KRUSKAL_H

#include "Containers/Structures.cpp"

class Kruskal {
private:
    Edge* answer;
    Edge** adjacencyList;
    int** incidenceMatrix;
    int* weight;
    int vertices;
    int edges;
public:
    Kruskal(int** incidenceMatrix, int vertices, int edges, const int* weight);
    Kruskal(Edge** adjacencyList, int vertices, int edges, const int* weight);
    ~Kruskal();
    void mst_im();
    void mst_al();
    void printAnswer();
};


#endif //AIZO2_KRUSKAL_H
