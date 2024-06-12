#ifndef AIZO2_SET_H
#define AIZO2_SET_H

#include "Structures.cpp"

struct SetNode{
    int nr;
    int id;
};

class Set {
private:
    int vertices;
    SetNode* Group;
public:
    Set(int vertices);
    ~Set();
    void MakeSet(int vertex);
    int FindSet(int vertex);
    void Union(Edge edge);
};


#endif
