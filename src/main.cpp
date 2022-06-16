#include <iostream>
#include <string>
#include <vector>
#include "BelmanFord.hpp"
#include "Graph.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    cout << "Введите название файла с графом: ";
    string fileName;
    cin >> fileName;
    Graph graph(fileName);
    BelmanFord belmanFord(&graph);

    cout << endl << "Введите вершину от которой считать: ";
    string vertexSource;
    cin >> vertexSource;
    // Подсчет и вывод кратчайших путей
    cout << endl << "Кратчайшие пути:" << endl;
    belmanFord.RunAlgoritmMin(vertexSource);
    belmanFord.ShowResult();

    // Подсчет и вывод длиннейших путей
    cout << endl << "Длиннейшие пути:" << endl;
    belmanFord.RunAlgoritmMax(vertexSource);
    belmanFord.ShowResult();

    // Подсчет и вывод длиннейших путей
    cout << endl << "Введите вершину до которой считать (для подсчета кол-ва путей): ";
    string vertexAim;
    cin >> vertexAim;
    cout << "От " << vertexSource << " до " << vertexAim << ": " << graph.RunCalculateWaysCount(vertexSource, vertexAim) << " путей" << endl;

    // Вывод ошибок
    graph.ShowLastError();
    belmanFord.ShowLastError();
}