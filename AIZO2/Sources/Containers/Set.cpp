#include "Set.h"

Set::Set(int vertices) {
    this->vertices=vertices;
    Group = new SetNode[vertices];
}

Set::~Set() {
    delete [] Group;
}

void Set::MakeSet(int vertex) {
    Group[vertex].nr = vertex;
    Group[vertex].id = 0;
}

int Set::FindSet(int vertex) {
    if(Group[vertex].nr != vertex) Group[vertex].nr = FindSet(Group [vertex].nr);
    return Group[vertex].nr;
}

void Set::Union(Edge edge) {
    int ru, rv;

    ru = FindSet(edge.predecessor);   // Wyznaczamy korzeń drzewa z węzłem u
    rv = FindSet(edge.successor);     // Wyznaczamy korzeń drzewa z węzłem v
    if(ru != rv)                              // Korzenie muszą być różne
    {
        if(Group[ru].id > Group[rv].id)    // Porównujemy rangi drzew
            Group[rv].nr = ru;              // ru większe, dołączamy rv
        else
        {
            Group[ru].nr = rv;             // równe lub rv większe, dołączamy ru
            if(Group[ru].id == Group[rv].id) Group[rv].id++;
        }
    }
}
