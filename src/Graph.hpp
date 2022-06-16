#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <fstream>
#include "Edge.hpp"
#include "Flags.hpp"

using namespace std;

class Graph
{
private:
    ErrorFlag lastErrorFlag = ErrorFlag::NONE;
public:
    vector<Edge> allEdges;
    set<string> vertexNames;
    int vertexCount = 0;
    const int edgeInfoCount = 3;

    Graph();
    Graph(string fileName);
    ErrorFlag GetLastError();
    bool ParceFileToGraph(string fileNmae);
    Edge ConvertToEdge(vector<string> edgeInfo);
    void CalculateVertexCount();
    bool IsGraphUnidirectional();
    double RunCalculateWaysCount(string fromVertex, string toVertex);
    double RecursWaysCount(string fromVertex, string toVertex);
    bool AddEdge(Edge edge);
    void ShowLastError();

};

