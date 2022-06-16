    #pragma once
    #include <string>
    #include <map>
    #include <iomanip>
    #include <cmath>
    #include "Graph.hpp"
    #include "Edge.hpp"
    #include "Flags.hpp"

    using namespace std;

    class BelmanFord
    {
    private:
        ErrorFlag lastErrorFlag = ErrorFlag::NONE;
    public:
        map<string, float> lengthWays;
        map<string, string> ways;
        Graph* graph;

        BelmanFord();
        BelmanFord(Graph* graph);
        ErrorFlag GetLastError();
        void SetGraph(Graph* graph);
        void Reset();
        bool RunAlgoritmMin(string source);
        bool RunAlgoritmMax(string source);
        void ShowResult();
        void ShowLastError();
    };

