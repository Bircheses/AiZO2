#include <iostream>
#include <iomanip>
#include "Containers/Structures.cpp"

using namespace std;

static void showIncidenceMatrix(int** incidenceMatrix, int vertices, int edges, const int* weight){
    std::cout << "Incidence Matrix:" << std::endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            std::cout << std::setw(2) << std::right << incidenceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Wage:" << std::endl;
    for(int i=0; i<edges; i++){
        std::cout << std::setw(2) << std::right << weight[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

static void showAdjacencyList(Edge** adjacencyList, int vertices, const int* weight){
    std::cout << "Adjacency List:" << std::endl;
    for (int i = 0; i < vertices; i++) {
        std::cout << i << ":";
        for (int j = 0; j < weight[i]; j++) {
            std::cout << std::setw(2) << std::right << adjacencyList[i][j].successor << "(" << adjacencyList[i][j].weight << ")";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

static void deallocate(int** incidenceMatrix, int size){
    if(incidenceMatrix!= nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] incidenceMatrix[i];
        }
        delete[] incidenceMatrix;
    }
}

static void deallocate(Edge** adjacencyList, int size){
    if(adjacencyList!= nullptr) {
        for (int i = 0; i < size; i++) {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
    }
}

static void showAnswer(int vertices, Edge* answer){
    for(int i=0; i<vertices-1; i++) {
        printf("%d-%d:%d\n", answer[i].predecessor, answer[i].successor, answer[i].weight);
    }
    std::cout << std::endl;
}

static void showAnswer(int vertices, Vertex* answer){
    for(int i=0; i<vertices; i++) {
        printf("%d:%d(%d)\n", i , answer[i].predecessor, answer[i].distance);
    }
    std::cout << std::endl;
}