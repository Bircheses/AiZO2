#include "Kruskal.h"
#include "StaticFunctions.cpp"
#include "Containers/PriorityQueueEdge.h"
#include "Containers/Set.h"

Kruskal::Kruskal(int** incidenceMatrix, int vertices, int edges, const int* weight):adjacencyList{nullptr}{
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

Kruskal::Kruskal(Edge **adjacencyList, int vertices, int edges, const int* weight):incidenceMatrix{nullptr}{
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

Kruskal::~Kruskal() {
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] answer;
}

void Kruskal::mst_im() {
    PriorityQueueEdge queue(edges);
    Set set(edges);

    for(int i=0; i<edges; i++){
        set.MakeSet(i);
        int counter = 0;
        Edge edge{};
        for(int j=0; j<vertices; j++){
            if(incidenceMatrix[j][i]==0){
                counter++;
                continue;
            }else if(counter == j) {
                edge.predecessor = counter;
                continue;
            }else{
                edge.successor = j;
                edge.weight = weight[i];
                break;
            }
        }
        queue.push(edge);
    }
    Edge edge;
    for(int i=0; i<vertices-1; i++){
        do{
            edge = queue.front();
            queue.pop();
        }while(set.FindSet(edge.predecessor) == set.FindSet(edge.successor));
        answer[i]=edge;
        set.Union(edge);
    }
}

void Kruskal::mst_al() {
    PriorityQueueEdge queue(2*edges);
    Set set(edges);

    for(int i=0; i<edges; i++) set.MakeSet(i);

    for(int i=0; i<vertices-1; i++){
        for(int j=0; j<weight[i]; j++){
            if(adjacencyList[i][j].successor>i) queue.push(adjacencyList[i][j]);
        }
    }

    Edge edge;
    for(int i=0; i<vertices-1; i++){
        do{
            edge = queue.front();
            queue.pop();
        }while(set.FindSet(edge.predecessor) == set.FindSet(edge.successor));
        answer[i]=edge;
        set.Union(edge);
    }
}

void Kruskal::printAnswer() {
    showAnswer(vertices, answer);
}
