#include "Prim.h"
#include "StaticFunctions.cpp"
#include "Containers/PriorityQueueEdge.h"

Prim::Prim(int** incidenceMatrix, int vertices, int edges, const int* weight):adjacencyList{nullptr}{
    this->vertices = vertices;
    this->edges = edges;

    this->incidenceMatrix = new int *[vertices];
    for (int i = 0; i < vertices; i++) {
        this->incidenceMatrix[i] = new int[edges];
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            this->incidenceMatrix[i][j] = incidenceMatrix[i][j];
        }
    }
    this->weight = new int[edges];
    for(int i=0; i<edges; i++){
        this->weight[i] = weight[i];
    }

    answer = new Edge[vertices-1];
}

Prim::Prim(Edge **adjacencyList, int vertices, int edges, const int* weight):incidenceMatrix{nullptr}{
    this->vertices = vertices;
    this->edges = edges;

    this->adjacencyList = new Edge *[vertices];
    for (int i = 0; i < vertices; i++) {
        this->adjacencyList[i] = new Edge[weight[i]];
    }
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < weight[i]; j++) {
            this->adjacencyList[i][j] = adjacencyList[i][j];
        }
    }
    this->weight = new int[vertices];
    for(int i=0; i<vertices; i++){
        this->weight[i] = weight[i];
    }

    answer = new Edge[vertices-1];
}

Prim::~Prim() {
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] answer;
}

void Prim::printAnswer() {
    showAnswer(vertices, answer);
}

/**
 * Function that uses incidence matrix to find minimum spanning tree
 */
void Prim::mst_im() {
    PriorityQueueEdge queue(edges * 2);
    bool* visited = new bool[vertices];
    for(int i=0; i<vertices; i++) visited[i] = false;

    visited[0] = true;
    int current = 0;

    for(int i=0; i<vertices-1; i++) {
        for(int j=0; j<edges; j++){
            if(incidenceMatrix[current][j]==1){
                Edge edge;
                for (int k = 0; k < vertices; k++){
                    if(k!=current && incidenceMatrix[k][j] == 1 && !visited[k]){
                        edge.predecessor = current;
                        edge.successor = k;
                        edge.weight = weight[j];
                        queue.push(edge);
                    }
                }
            }
        }
        for(int k=0; k<edges; k++){
            if(!visited[queue.front().successor]) {
                current = queue.front().successor;
                answer[i] = queue.front();
                visited[current] = true;
                queue.pop();
                break;
            }else{
                queue.pop();
            }
        }
    }

    delete [] visited;
}

/**
 * Function that uses adjacency list to find minimum spanning tree
 */
void Prim::mst_al() {
    PriorityQueueEdge queue(edges * 2);
    bool* visited = new bool[vertices];
    for(int i=0; i<vertices; i++) visited[i] = false;

    visited[0] = true;
    int current = 0;

    for(int i=0; i<vertices-1; i++) {
        for(int j=0; j<weight[current]; j++){
            if(!visited[adjacencyList[current][j].successor]) queue.push(adjacencyList[current][j]);
        }
        for(int k=0; k<edges; k++){
            if(!visited[queue.front().successor]) {
                current = queue.front().successor;
                answer[i] = queue.front();
                visited[current] = true;
                queue.pop();
                break;
            }else{
                queue.pop();
            }
        }
    }

    delete [] visited;
}

