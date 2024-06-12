#include "Dijkstra.h"
#include "StaticFunctions.cpp"
#include "Containers/PriorityQueueVertex.h"

Dijkstra::Dijkstra(int** incidenceMatrix, int vertices, int edges, const int* weight):adjacencyList{nullptr}{
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

Dijkstra::Dijkstra(Edge **adjacencyList, int vertices, int edges, const int* weight):incidenceMatrix{nullptr}{
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

Dijkstra::~Dijkstra() {
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] answer;
}

void Dijkstra::sp_im(int vertex) {
    PriorityQueueVertex queue = PriorityQueueVertex(edges);
    Vertex* vertexlist = new Vertex[vertices];
    bool* visited = new bool[vertices];

    for(int i=0; i<vertices; i++){
        vertexlist[i].distance = 200000;
        vertexlist[i].number = i;
        visited[i] = false;
    }

    vertexlist[vertex].predecessor = -1;
    vertexlist[vertex].distance = 0;
    queue.push(vertexlist[vertex]);

    while(queue.front().distance!=-1){
        int current = queue.front().number;
        queue.pop();
        if(visited[current]) continue;
        for (int j=0; j<edges; j++) {
            if (incidenceMatrix[current][j] == 1) {
                for (int k = 0; k < vertices; k++) {
                    if (current != k && incidenceMatrix[k][j] == -1){
                        //queue.push(k);
                        //Relaksacja
                        if (vertexlist[k].distance > weight[j] + vertexlist[current].distance) {
                            vertexlist[k].predecessor = current;
                            vertexlist[k].distance = weight[j] + vertexlist[current].distance;
                            Vertex v = {k,current,vertexlist[k].distance};
                            queue.push(v);
                        }
                    }
                }
            }
        }
        visited[current] = true;
    }

    for(int i=0; i<vertices; i++){
        answer[i] = vertexlist[i];
    }

    delete [] vertexlist;
}

void Dijkstra::sp_al(int vertex) {
    PriorityQueueVertex queue = PriorityQueueVertex(edges);
    Vertex* vertexlist = new Vertex[vertices];
    bool* visited = new bool[vertices];

    for(int i=0; i<vertices; i++){
        vertexlist[i].distance = 200000;
        vertexlist[i].number = i;
        visited[i] = false;
    }

    vertexlist[vertex].predecessor = -1;
    vertexlist[vertex].distance = 0;
    queue.push(vertexlist[vertex]);

    while(queue.front().distance!=-1){
        int current = queue.front().number;
        queue.pop();
        if(visited[current]) continue;
        for(int i=0; i<weight[current]; i++){
            //queue.push(adjacencyList[current][i].successor);
            //Relaksacja
            if (vertexlist[adjacencyList[current][i].successor].distance > adjacencyList[current][i].weight + vertexlist[current].distance){
                vertexlist[adjacencyList[current][i].successor].predecessor = current;
                vertexlist[adjacencyList[current][i].successor].distance = adjacencyList[current][i].weight + vertexlist[current].distance;
                Vertex v = {adjacencyList[current][i].successor,current,vertexlist[adjacencyList[current][i].successor].distance};
                queue.push(v);
            }
        }
        visited[current] = true;
    }

    for(int i=0; i<vertices; i++){
        answer[i] = vertexlist[i];
    }

    delete [] vertexlist;
}

void Dijkstra::printAnswer(int begin, int end) {
    if(answer[end].distance == 200000) cout << "Nie ma drogi do szukanego wierzcholka" << endl;
    else {
        while(answer[end].predecessor != begin){
            printf("%d:%d(%d)\n", answer[end].predecessor, answer[end].number, answer[end].distance);
            end = answer[end].predecessor;
        }
        printf("%d:%d(%d)\n", answer[end].predecessor, answer[end].number, answer[end].distance);
    }
}
