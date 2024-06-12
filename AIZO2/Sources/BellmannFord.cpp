#include "BellmannFord.h"
#include "StaticFunctions.cpp"

BellmannFord::BellmannFord(int** incidenceMatrix, int vertices, int edges, const int* weight):adjacencyList{nullptr}{
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

    answer = new Vertex[vertices];
}

BellmannFord::BellmannFord(Edge **adjacencyList, int vertices, int edges, const int* weight):incidenceMatrix{nullptr}{
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

    answer = new Vertex[vertices];
}

BellmannFord::~BellmannFord() {
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] answer;
}

void BellmannFord::sp_im(int vertex) {
    Vertex* vertexlist = new Vertex[vertices];

    for(int i=0; i<vertices; i++){
        vertexlist[i].distance = 200000;
        vertexlist[i].number = i;
    }
    vertexlist[vertex].predecessor = -1;
    vertexlist[vertex].distance = 0;

    for(int i=0; i<vertices-1; i++){
        int change = 0;
        for(int j=0; j<vertices; j++){
            for(int k=0; k<edges; k++){
                if(incidenceMatrix[j][k] == 1){
                    for(int l=0; l<vertices; l++){
                        if(incidenceMatrix[l][k] == -1) {
                            if (vertexlist[l].distance > weight[k] + vertexlist[j].distance) {
                                vertexlist[l].predecessor = j;
                                vertexlist[l].distance = weight[k] + vertexlist[j].distance;
                                change++;
                            }
                        }
                    }
                }
            }
        }
        if(change==0) break;
    }

    for(int i=0; i<vertices; i++){
        answer[i] = vertexlist[i];
    }

    delete [] vertexlist;
}

void BellmannFord::sp_al(int vertex) {
    Vertex* vertexlist = new Vertex[vertices];

    for(int i=0; i<vertices; i++){
        vertexlist[i].distance = 200000;
        vertexlist[i].number = i;
    }
    vertexlist[vertex].predecessor = -1;
    vertexlist[vertex].distance = 0;

    for(int i=0; i<vertices-1; i++){
        int change = 0;
        for(int j=0; j<vertices; j++){
            for(int k=0; k<weight[j]; k++){
                if (vertexlist[adjacencyList[j][k].successor].distance > adjacencyList[j][k].weight + vertexlist[j].distance){
                    vertexlist[adjacencyList[j][k].successor].predecessor = j;
                    vertexlist[adjacencyList[j][k].successor].distance = adjacencyList[j][k].weight + vertexlist[j].distance;
                    change++;
                }
            }
        }
        if(change==0) break;
    }

    for(int i=0; i<vertices; i++){
        answer[i] = vertexlist[i];
    }

    delete [] vertexlist;
}

void BellmannFord::printAnswer(int begin, int end) {
    if(answer[end].distance == 200000) cout << "Nie ma drogi do szukanego wierzcholka" << endl;
    else {
        while(answer[end].predecessor != begin){
            printf("%d:%d(%d)\n", answer[end].predecessor, answer[end].number, answer[end].distance);
            end = answer[end].predecessor;
        }
        printf("%d:%d(%d)\n", answer[end].predecessor, answer[end].number, answer[end].distance);
    }
}
