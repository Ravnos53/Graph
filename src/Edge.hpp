#pragma once
#include <string>

using namespace std;

class Edge{
private:
public:
    string fromVertex;
    string toVertex;
    float weight;

    Edge();
    Edge(string fromVertex, string toVertex, float weigth);

    bool IsEmptyEdge();
    

};