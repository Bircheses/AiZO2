#include <iostream>
#include <algorithm>
#include <fstream>

#include "Sources/Counter.h"
#include "Sources/StaticFunctions.cpp"
#include "Sources/Prim.h"
#include "Sources/Kruskal.h"
#include "Sources/Dijkstra.h"
#include "Sources/BellmannFord.h"

using namespace std;

int** incidenceMatrix;
int* weight;
Edge** adjacencyList;
int* rowsize;
int V, E;

int undirectedgenerator(int vertices, int edges, float percent);
int directedgenerator(int vertices, int edges, float percent);
void read_from_file_undirected();
void read_from_file_directed();
void MainMenu();
void MSTMenu();
void PrimMenu();
void KruskalMenu();
void SPMenu();
void DijkstraMenu(int begin, int end);
void BellmanFordMenu(int begin, int end);

int main() {
    MainMenu();
    deallocate(incidenceMatrix,V);
    deallocate(adjacencyList,V);
    delete [] weight;
    delete [] rowsize;
    return 0;
}

void MainMenu(){
    bool resume = true;
    int n;
    while(resume){
        system("CLS");
        cout << "===========MAIN MENU===========" << endl;
        cout << "1-Minimalne drzewo rozpinajace" << endl;
        cout << "2-Najkrotsza sciezka w grafie" << endl;
        cout << "0-Wyjscie z programu" << endl;
        cin >> n;
        switch (n) {
            case 0:
                resume = false;
                break;
            case 1:
                system("CLS");
                MSTMenu();
                break;
            case 2:
                system("CLS");
                SPMenu();
                break;
            default:
                resume = false;
                break;
        }
    }
}

void MSTMenu(){
    bool resume = true;
    string url;
    int n;
    while(resume){
        cout << "==============MST MENU==============" << endl;
        cout << "1-Pobierz graf z pliku" << endl;
        cout << "2-Wygeneruj graf losowo" << endl;
        cout << "3-Wyswietl graf listowo i macierzowo" << endl;
        cout << "4-Algorytm Prima" << endl;
        cout << "5-Algorytm Kruskala" << endl;
        cout << "0-Powrot do menu glownego" << endl;
        cin >> n;
        switch (n) {
            case 0:
                resume = false;
                break;
            case 1:
                system("CLS");
                read_from_file_undirected();
                break;
            case 2:
                float Percent;
                system("CLS");
                cout << "Podaj liczbe wierzcholkow: " << endl;
                cin >> V;
                cout << "Podaj % wypelnienia: " << endl;
                cin >> Percent;
                E = undirectedgenerator(V,V*(V-1)/2,Percent/100);
                break;
            case 3:
                system("CLS");
                showIncidenceMatrix(incidenceMatrix,V,E,weight);
                showAdjacencyList(adjacencyList,V,rowsize);
                break;
            case 4:
                system("CLS");
                PrimMenu();
                break;
            case 5:
                system("CLS");
                KruskalMenu();
                break;
            default:
                resume = false;
                break;
        }
    }
}

void PrimMenu(){
    Prim prim1 = Prim(incidenceMatrix,V,E,weight);
    Prim prim2 = Prim(adjacencyList,V,E,rowsize);

    prim1.mst_im();
    prim2.mst_al();

    cout << "Macierz incydencji:" << endl;
    prim1.printAnswer();
    cout << "Lista sasiedztwa:" << endl;
    prim2.printAnswer();
}

void KruskalMenu(){
    Kruskal kruskal1 = Kruskal(incidenceMatrix,V,E,weight);
    Kruskal kruskal2 = Kruskal(adjacencyList,V,E,rowsize);

    kruskal1.mst_im();
    kruskal2.mst_al();

    cout << "Macierz incydencji:" << endl;
    kruskal1.printAnswer();
    cout << "Lista sasiedztwa:" << endl;
    kruskal2.printAnswer();
}

void SPMenu(){
    bool resume = true;
    string url;
    int n;
    int begin, end;
    while(resume){
        cout << "==============MST MENU==============" << endl;
        cout << "1-Pobierz graf z pliku" << endl;
        cout << "2-Wygeneruj graf losowo" << endl;
        cout << "3-Wyswietl graf listowo i macierzowo" << endl;
        cout << "4-Algorytm Dijkstry" << endl;
        cout << "5-Algorytm Bellmana-Forda" << endl;
        cout << "0-Powrot do menu glownego" << endl;
        cin >> n;
        switch (n) {
            case 0:
                resume = false;
                break;
            case 1:
                system("CLS");
                read_from_file_directed();
                break;
            case 2:
                float Percent;
                system("CLS");
                cout << "Podaj liczbe wierzcholkow: " << endl;
                cin >> V;
                cout << "Podaj % wypelnienia: " << endl;
                cin >> Percent;
                E = directedgenerator(V,V*(V-1),Percent/100);
                break;
            case 3:
                system("CLS");
                showIncidenceMatrix(incidenceMatrix,V,E,weight);
                showAdjacencyList(adjacencyList,V,rowsize);
                break;
            case 4:
                system("CLS");
                cout << "Podaj wierzcholek poczatkowy: " << endl;
                cin >> begin;
                cout << "Podaj wierzcholek koncowy: " << endl;
                cin >> end;
                system("CLS");
                DijkstraMenu(begin, end);
                break;
            case 5:
                system("CLS");
                cout << "Podaj wierzcholek poczatkowy: " << endl;
                cin >> begin;
                cout << "Podaj wierzcholek koncowy: " << endl;
                cin >> end;
                system("CLS");
                BellmanFordMenu(begin, end);
                break;
            default:
                resume = false;
                break;
        }
    }
}

void DijkstraMenu(int begin, int end){
    Dijkstra dijkstra1 = Dijkstra(incidenceMatrix,V,E,weight);
    Dijkstra dijkstra2 = Dijkstra(adjacencyList,V,E,rowsize);

    dijkstra1.sp_im(begin);
    dijkstra2.sp_al(begin);

    cout << "Macierz incydencji:" << endl;
    dijkstra1.printAnswer(begin, end);
    cout << "Lista sasiedztwa:" << endl;
    dijkstra2.printAnswer(begin, end);
}

void BellmanFordMenu(int begin, int end){
    BellmannFord bellmannFord1 = BellmannFord(incidenceMatrix,V,E,weight);
    BellmannFord bellmannFord2 = BellmannFord(adjacencyList,V,E,rowsize);

    bellmannFord1.sp_im(begin);
    bellmannFord2.sp_al(begin);

    cout << "Macierz incydencji:" << endl;
    bellmannFord1.printAnswer(begin, end);
    cout << "Lista sasiedztwa:" << endl;
    bellmannFord2.printAnswer(begin, end);
}

struct Generator{
    int predecessor;
    int successor;
};

void read_from_file_undirected(){
    string url;
    cout << "Podaj nazwe pliku tekstowego" << endl;
    cin >> url;
    ifstream file(url);
    if(file.is_open()){
        deallocate(incidenceMatrix,V);
        deallocate(adjacencyList,V);
        delete [] weight;
        delete [] rowsize;

        Edge* generator;
        string line;
        int i=-1;
        while(getline(file, line)) {
            stringstream ss(line);
            if (i == -1) {
                ss >> E >> V;
                generator = new Edge[E];
            } else {
                ss >> generator[i].predecessor >> generator[i].successor >> generator[i].weight;
            }
            i++;
        }
            weight = new int[E];
            rowsize = new int[V];
            //INCIDENCE MATRIX
            incidenceMatrix = new int*[V];
            for(int i=0; i<V; i++) incidenceMatrix[i] = new int[E];

            for(int i=0; i<V; i++){
                for(int j=0; j<E; j++){
                    incidenceMatrix[i][j]=0;
                }
            }

            for(int i=0; i<E; i++){
                incidenceMatrix[generator[i].predecessor][i] = 1;
                incidenceMatrix[generator[i].successor][i] = 1;
                weight[i] = generator[i].weight;
            }

            //ADJACENCY LIST
            int* counter2 = new int[E];

            adjacencyList = new Edge* [V];
            for (int i=0; i<V; i++){
                int counter = 0;
                for(int j=0; j<E; j++){
                    if(generator[j].predecessor == i || generator[j].successor == i) counter++;
                }
                adjacencyList[i] = new Edge[counter];
                rowsize[i] = counter;
                counter2[i]=0;
            }

            Edge edge;
            for(int i=0; i<V; i++){
                for(int k=0; k<E; k++) {
                    if (generator[k].predecessor == i){
                        edge.predecessor = i;
                        edge.successor = generator[k].successor;
                        edge.weight = generator[k].weight;
                        adjacencyList[i][counter2[i]] = edge;
                        counter2[i]++;
                    }else if (generator[k].successor == i){
                        edge.predecessor = i;
                        edge.successor = generator[k].predecessor;
                        edge.weight = generator[k].weight;
                        adjacencyList[i][counter2[i]] = edge;
                        counter2[i]++;
                    }
                }
            }
            delete [] counter2;
        delete [] generator;
    } else {
        cout << "Niepoprawna nazwa pliku!" << endl;
    }
}

void read_from_file_directed(){
    string url;
    cout << "Podaj nazwe pliku tekstowego" << endl;
    cin >> url;
    ifstream file(url);
    if(file.is_open()){
        deallocate(incidenceMatrix,V);
        deallocate(adjacencyList,V);
        delete [] weight;
        delete [] rowsize;

        Edge* generator;
        string line;
        int i=-1;
        while(getline(file, line)) {
            stringstream ss(line);
            if (i == -1) {
                ss >> E >> V;
                generator = new Edge[E];
            } else {
                ss >> generator[i].predecessor >> generator[i].successor >> generator[i].weight;
            }
            i++;
        }
        weight = new int[E];
        rowsize = new int[V];

        //INCIDENCE MATRIX
        incidenceMatrix = new int*[V];
        for(int i=0; i<V; i++) incidenceMatrix[i] = new int[E];
        for(int i=0; i<V; i++){
            for(int j=0; j<E; j++){
                incidenceMatrix[i][j]=0;
            }
        }
        for(int i=0; i<E; i++){
            incidenceMatrix[generator[i].predecessor][i] = 1;
            incidenceMatrix[generator[i].successor][i] = -1;
            weight[i] = generator[i].weight;
        }

        //ADJACENCY LIST
        int* counter2 = new int[E];

        adjacencyList = new Edge* [V];
        for (int i=0; i<V; i++){
            int counter = 0;
            for(int j=0; j<E; j++){
                if(generator[j].predecessor == i) counter++;
            }
            adjacencyList[i] = new Edge[counter];
            rowsize[i] = counter;
            counter2[i]=0;
        }

        Edge edge;
        for(int i=0; i<V; i++){
            for(int k=0; k<E; k++) {
                if(generator[k].predecessor==i){
                    edge.predecessor = i;
                    edge.successor = generator[k].successor;
                    edge.weight = generator[k].weight;
                    adjacencyList[i][counter2[i]] = edge;
                    counter2[i]++;
                }
            }
        }

        delete [] counter2;
        delete [] generator;
    } else {
        cout << "Niepoprawna nazwa pliku!" << endl;
    }
}

int undirectedgenerator(int vertices, int edges, float percent){
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] rowsize;

    int maxEdges = (int)(percent*edges);
    weight = new int[maxEdges];
    rowsize = new int[vertices];
    srand(time(NULL));

    int* vertex = new int[vertices];
    Generator* generator = new Generator[maxEdges];

    for(int i=0; i<vertices; i++){
        vertex[i] = i;
    }

    for(int i=0; i<vertices; i++){
        int j = rand()%vertices;
        swap(vertex[i], vertex[j]);
    }

    //MST generator
    for(int i=1; i<vertices; i++){
        generator[i-1].predecessor = vertex[rand()%i];
        generator[i-1].successor = vertex[i];
    }

    //Filler generator
    for(int i=vertices-1; i<maxEdges; i++){
        generator[i].predecessor = vertex[rand()%vertices];
        generator[i].successor = vertex[rand()%vertices];
        while(generator[i].predecessor == generator[i].successor) generator[i].successor = vertex[rand()%vertices];
        for(int j=0; j<i; j++){
            if((generator[i].predecessor == generator[j].predecessor && generator[i].successor == generator[j].successor)){
                i--;
                break;
            }else if(generator[i].predecessor == generator[j].successor && generator[i].successor == generator[j].predecessor){
                i--;
                break;
            }
        }
    }

    int* temp = new int[maxEdges];

    for(int i=0; i<maxEdges; i++){
        temp[i]=rand()%19+1;
    }

    //INCIDENCE MATRIX
    incidenceMatrix = new int*[vertices];
    for(int i=0; i<vertices; i++) incidenceMatrix[i] = new int[maxEdges];

    for(int i=0; i<vertices; i++){
        for(int j=0; j<maxEdges; j++){
            incidenceMatrix[i][j]=0;
        }
    }

    for(int i=0; i<maxEdges; i++){
        incidenceMatrix[generator[i].predecessor][i] = 1;
        incidenceMatrix[generator[i].successor][i] = 1;
        weight[i] = temp[i];
    }

    //ADJACENCY LIST
    int* counter2 = new int[maxEdges];

    adjacencyList = new Edge* [vertices];
    for (int i=0; i<vertices; i++){
        int counter = 0;
        for(int j=0; j<maxEdges; j++){
            if(generator[j].predecessor == i || generator[j].successor == i) counter++;
        }
        adjacencyList[i] = new Edge[counter];
        rowsize[i] = counter;
        counter2[i]=0;
    }

    Edge edge;
    for(int i=0; i<vertices; i++){
        for(int k=0; k<maxEdges; k++) {
            if (generator[k].predecessor == i){
                edge.predecessor = i;
                edge.successor = generator[k].successor;
                edge.weight = temp[k];
                adjacencyList[i][counter2[i]] = edge;
                counter2[i]++;
            }else if (generator[k].successor == i){
                edge.predecessor = i;
                edge.successor = generator[k].predecessor;
                edge.weight = temp[k];
                adjacencyList[i][counter2[i]] = edge;
                counter2[i]++;
            }
        }
    }

    delete [] generator;
    delete [] vertex;
    delete [] counter2;
    delete [] temp;
    return maxEdges;
}

int directedgenerator(int vertices, int edges, float percent){
    deallocate(incidenceMatrix, vertices);
    deallocate(adjacencyList, vertices);
    delete [] weight;
    delete [] rowsize;

    int maxEdges = (int)(percent*edges);
    weight = new int[maxEdges];
    rowsize = new int[vertices];
    srand(time(NULL));

    int* vertex = new int[vertices];
    Generator* generator = new Generator[maxEdges];

    for(int i=0; i<vertices; i++){
        vertex[i] = i;
    }

    for(int i=0; i<vertices; i++){
        int j = rand()%vertices;
        swap(vertex[i], vertex[j]);
    }

    //MST generator
    for(int i=1; i<vertices; i++){
        generator[i-1].predecessor = vertex[rand()%i];
        generator[i-1].successor = vertex[i];
    }

    //Filler generator
    for(int i=vertices-1; i<maxEdges; i++){
        generator[i].predecessor = vertex[rand()%vertices];
        generator[i].successor = vertex[rand()%vertices];
        while(generator[i].predecessor == generator[i].successor) generator[i].successor = vertex[rand()%vertices];
        for(int j=0; j<i; j++){
            if((generator[i].predecessor == generator[j].predecessor && generator[i].successor == generator[j].successor)){
                i--;
                break;
            }
        }
    }

    int* temp = new int[maxEdges];

    for(int i=0; i<maxEdges; i++){
        temp[i]=rand()%19+1;
    }

    //INCIDENCE MATRIX
    incidenceMatrix = new int*[vertices];
    for(int i=0; i<vertices; i++) incidenceMatrix[i] = new int[maxEdges];
    for(int i=0; i<vertices; i++){
        for(int j=0; j<maxEdges; j++){
            incidenceMatrix[i][j]=0;
        }
    }
    for(int i=0; i<maxEdges; i++){
        incidenceMatrix[generator[i].predecessor][i] = 1;
        incidenceMatrix[generator[i].successor][i] = -1;
        weight[i] = temp[i];
    }

    //ADJACENCY LIST
    int* counter2 = new int[maxEdges];

    adjacencyList = new Edge* [vertices];
    for (int i=0; i<vertices; i++){
        int counter = 0;
        for(int j=0; j<maxEdges; j++){
            if(generator[j].predecessor == i) counter++;
        }
        adjacencyList[i] = new Edge[counter];
        rowsize[i] = counter;
        counter2[i]=0;
    }

    Edge edge;
    for(int i=0; i<vertices; i++){
        for(int k=0; k<maxEdges; k++) {
            if(generator[k].predecessor==i){
                edge.predecessor = i;
                edge.successor = generator[k].successor;
                edge.weight = temp[k];
                adjacencyList[i][counter2[i]] = edge;
                counter2[i]++;
            }
        }
    }

    delete [] generator;
    delete [] vertex;
    delete [] counter2;
    delete [] temp;
    return maxEdges;
}