#include "Edge.hpp"

Edge::Edge(){
    this->fromVertex = "";
    this->toVertex = "";
    this->weight = -1;
}

Edge::Edge(string fromVertex, string toVertex, float weigth){
    this->fromVertex = fromVertex;
    this->toVertex = toVertex;
    this->weight = weigth;
}

bool Edge::IsEmptyEdge(){
    if (fromVertex == "" && toVertex == "" && weight == -1)
        return true;
    return false;
    
}