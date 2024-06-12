#pragma once
struct Edge{
    int predecessor;
    int successor;
    int weight;
};

#pragma once
struct Vertex{
    int number;
    int predecessor;
    int distance;
};
