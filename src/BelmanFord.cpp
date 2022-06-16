#include "BelmanFord.hpp"

BelmanFord::BelmanFord() {

}

BelmanFord::BelmanFord(Graph* graph) {
    SetGraph(graph);
}

ErrorFlag BelmanFord::GetLastError() {
    return lastErrorFlag;
}

void BelmanFord::Reset() {
    lastErrorFlag = ErrorFlag::NONE;
    lengthWays.clear();
    ways.clear();
}

void BelmanFord::SetGraph(Graph* graph){
    // Если граф имел ошибки то работа алгоритма недопустима
    // поле класса с графом не запишется а у класса будет соответствующий флаг ошибки
    if (graph->GetLastError() != ErrorFlag::NONE) {
        lastErrorFlag = ErrorFlag::GRAPH_WITH_ERROR;
        return;
    }

    this->graph = graph;
}

bool BelmanFord::RunAlgoritmMin(string source) {
    // Проверка на выход source за границы
    bool flagOutOfBounds = true;
    for (auto name : graph->vertexNames) {
        if (source == name) {
            flagOutOfBounds = false;
            break;
        }
    }
    if ( flagOutOfBounds ) {
        lastErrorFlag = ErrorFlag::SOURCE_OUT_OF_BOUNDS;
        return false;
    }
    
    // Контейнеры (ключ, значение) для хранения длины путей и строкового представления самого пути
    map<string, float> distances;
    map<string, string> vertexWays;

    // Инициализируем начальные данные о длине пути в соответствии
    // с алгоритмом Белмана-Форда
    for (auto name : graph->vertexNames) {
        // Все вершины inf 
        distances[name] = HUGE_VALF;
        vertexWays[name] = "[";
    }
    // Кроме вершины от которой считаем
    distances[source] = 0;
    
    // Основной цикл алгоритма Белмана-Форда проходим N - 1 раз
    for (auto i = 0; i < graph->vertexCount - 1; i++) {
        for (auto edge : graph->allEdges) {

            if ( distances[edge.fromVertex] != HUGE_VALF &&
                distances[edge.fromVertex] + edge.weight < distances[edge.toVertex]) {
                    distances[edge.toVertex] = distances[edge.fromVertex] + edge.weight;
                    vertexWays[edge.toVertex] = vertexWays[edge.fromVertex] + " " + edge.fromVertex;
                }
        }
    }

    // Решение проблемы негативного цикла, проходим алгоритм еще раз
    // если в какой-то вершине поменяется значение -> присутствует цикл
    for (auto edge : graph->allEdges) {
        if ( distances[edge.fromVertex] != HUGE_VALF &&
            distances[edge.fromVertex] + edge.weight < distances[edge.toVertex]) {
                lastErrorFlag = ErrorFlag::CYCLE_NEGATIVE_WEIGHT;
                return false;
            }
    }
    
    // Для вывода строкового представления пути
    // Шаблон: "[ A D E" -> "[ A D E name ]"
    for (auto name : graph->vertexNames) 
        vertexWays[name] += " " + name + " ]";

    // После того как алгоритм корректно отработал мы записываем резултаты в соответствующие поля класса
    lengthWays = distances;
    ways = vertexWays;
    
    return true;
}

bool BelmanFord::RunAlgoritmMax(string source) {
    // Проверка на выход source за границы
    bool flagOutOfBounds = true;
    for (auto name : graph->vertexNames) {
        if (source == name) {
            flagOutOfBounds = false;
            break;
        }
    }
    if ( flagOutOfBounds ) {
        lastErrorFlag = ErrorFlag::SOURCE_OUT_OF_BOUNDS;
        return false;
    }

    // Контейнеры (ключ, значение) для хранения длины путей и строкового представления самого пути
    map<string, float> distances;
    map<string, string> vertexWays;

    // Инициализируем начальные данные о длине пути в соответствии
    // с алгоритмом Белмана-Форда
    for (auto name : graph->vertexNames) {
        // Все вершины -inf 
        distances[name] = -HUGE_VALF;
        vertexWays[name] = "[";
    }
    // Кроме вершины от которой считаем
    distances[source] = 0;
    
    // Основной цикл алгоритма Белмана-Форда проходим N - 1 раз
    for (auto i = 0; i < graph->vertexCount - 1; i++) {
        for (auto edge : graph->allEdges) {

            if ( distances[edge.fromVertex] != -HUGE_VALF &&
                distances[edge.fromVertex] + edge.weight > distances[edge.toVertex]) {
                    distances[edge.toVertex] = distances[edge.fromVertex] + edge.weight;
                    vertexWays[edge.toVertex] = vertexWays[edge.fromVertex] + " " + edge.fromVertex;
                }
        }
    }

    // Решение проблемы позитивного цикла, проходим алгоритм еще раз
    // если в какой-то вершине поменяется значение -> присутствует цикл
    for (auto edge : graph->allEdges) {
        if ( distances[edge.fromVertex] != -HUGE_VALF &&
            distances[edge.fromVertex] + edge.weight > distances[edge.toVertex]) {
                lastErrorFlag = ErrorFlag::CYCLE_POSITIVE_WEIGHT;
                return false;
            }
    }
    
    // Для вывода строкового представления пути
    // Шаблон: "[ A D E" -> "[ A D E name ]"
    for (auto name : graph->vertexNames) 
        vertexWays[name] += " " + name + " ]";

    // После того как алгоритм корректно отработал мы записываем резултаты в соответствующие поля класса
    lengthWays = distances;
    ways = vertexWays;

    return true;
}

void BelmanFord::ShowResult(){
    if (lastErrorFlag != ErrorFlag::NONE){
        cout << "Not result :(" << endl;
        return;
    }
    
    for (auto name : graph->vertexNames)
    {
        cout << "(" <<  setw(3) << name << " ) ->" << setw(6) << lengthWays[name] << " way: " << ways[name] << endl; 
    }
    
}

void BelmanFord::ShowLastError(){
    switch (lastErrorFlag)
    {
    case ErrorFlag::CYCLE_NEGATIVE_WEIGHT:
        cout << "ERROR: Cycle negative weight in graph" << endl;
        break;
    case ErrorFlag::CYCLE_POSITIVE_WEIGHT:
        cout << "ERROR: Cycle positive weight in graph" << endl;
        break;
    case ErrorFlag::SOURCE_OUT_OF_BOUNDS:
        cout << "ERROR: Source out of bounds" << endl;
        break;  
    case ErrorFlag::GRAPH_WITH_ERROR:
        cout << "ERROR: Your setted graph with error" << endl;
        break;   
    default:
        break;
    }
}