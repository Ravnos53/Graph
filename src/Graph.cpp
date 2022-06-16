#include "Graph.hpp"

Graph::Graph(){

}

Graph::Graph(string fileName) {
    ParceFileToGraph(fileName);
    CalculateVertexCount();
}

ErrorFlag Graph::GetLastError() {
    return lastErrorFlag;
}

bool Graph::ParceFileToGraph(string fileName) {
    std::string line;
    // Окрываем поток файла для чтения
    std::ifstream in(fileName); 
    if (in.is_open())
    {
        // Для хранения элемента строки (до пробела)
        string elem = "";
        // Вектор для записи инофрмации из одной строки "A B 4" -> ["A", "B", 4] 
        vector<string> edgeInfo;
        // Цикл построчного просмотра всего файла из потока
        while (getline(in, line))
        {
            // Цикл просмотра побуквенно одной строки
            for ( auto ch : line ) {
                // Если пробел или \n, то мы записаное слово из elem 
                // передаем в вектор
                if ( ch == ' ' || ch == '\n' ) {
                    if ( elem.size() != 0 ){
                        edgeInfo.push_back(elem);
                        elem = "";
                    }
                }
                // Если не пробле дополняем elem текущим символом
                else {
                    elem += ch;
                }
            }
            // Дополнение к циклу, так как последний элемент не запишется и нужно его записать 
            // вне цикла 
            if ( elem.size() != 0 ) {
                edgeInfo.push_back(elem);
                elem = "";
            }
            // Проверяем полученные данные из строки
            // Если конвертировать вектор с информацией в Edge не получилось и вернулся пустой Edge
            // то мы выходим и ставим флаг ошибки
            if ( ConvertToEdge(edgeInfo).IsEmptyEdge() ) {
                ShowLastError();
                lastErrorFlag = ErrorFlag::EDGE_EMPTY;
                return false;
            }
            // Добавляем в вектор всех Edges новый Edge
            allEdges.push_back(ConvertToEdge(edgeInfo));
            // Обязательно чистим вектор для следующей работы с ним в цикле
            edgeInfo.clear();
        }

        in.close();     // закрываем файл
    }
    // Если файл не был открыт (не найден)
    else {
        ShowLastError();
        lastErrorFlag = ErrorFlag::FILE_NOT_FOUND;
        return false;
    }
    return true;
}

Edge Graph::ConvertToEdge(vector<string> edgeInfo) {
    // Для возврата при ошибке
    Edge emptyEdge;
    // Для записи и возврата новой Edge
    Edge edge;

    // Обязательно длина вектора с информацией должна быть равной 3
    if ((int)edgeInfo.size() != edgeInfoCount){
        lastErrorFlag = ErrorFlag::EDGE_INFO_COUNT;
        return emptyEdge;
    }

    // Заполняем from vertex
    edge.fromVertex = edgeInfo[0];
    // Заполняем to vertex
    edge.toVertex = edgeInfo[1];
    // Заполняем weigth
    // Функция преобразования string в float выкидывает ошибку при неудаче
    // поэтому мы обернули данный блок кода в try catch
    try {
        float newWeigth = stof(edgeInfo[2]);
        edge.weight = newWeigth;
    }
    catch(const exception& e) {
        lastErrorFlag = ErrorFlag::STOF_ERROR;
        return emptyEdge;
    }
    return edge;
}

void Graph::CalculateVertexCount() {
    vertexNames.clear();
    for (auto edge : allEdges) {
        vertexNames.insert(edge.fromVertex);
        vertexNames.insert(edge.toVertex);
    }
    vertexCount = vertexNames.size();
}

bool Graph::IsGraphUnidirectional() {
    for (auto i = 0; i < (int)allEdges.size(); i++) {
        for (auto j = 0; j < (int)allEdges.size(); j++) {
            if (i != j && allEdges[i].fromVertex == allEdges[j].toVertex && allEdges[i].toVertex == allEdges[j].fromVertex )
            return false;
        }      
    }
    return true;
}

double Graph::RunCalculateWaysCount(string fromVertex, string toVertex) {
    double waysCount = HUGE_VAL;
    // Только если граф однонаправленный
    if ( IsGraphUnidirectional() ) {
        waysCount = RecursWaysCount(fromVertex, toVertex);
    }
    return waysCount;
}

double Graph::RecursWaysCount(string fromVertex, string toVertex) {
    if (fromVertex == toVertex) {
        return 1;
    }

    double waysCount = 0;
    for (auto edge : allEdges){
        if ( edge.toVertex == toVertex ) {
            waysCount += RecursWaysCount(fromVertex, edge.fromVertex);
        }
    }

    return waysCount;
}

void Graph::ShowLastError() {
    switch (lastErrorFlag)
    {
    case ErrorFlag::FILE_NOT_FOUND:
        cout << "ERROR: File not found" << endl;
        break;
    case ErrorFlag::EDGE_EMPTY:
        cout << "ERROR: Edge empty, uncorrect input" << endl;
        break;    
    case ErrorFlag::EDGE_INFO_COUNT:
        cout << "ERROR: Edge info uncorrect size" << endl;
        break;       
    case ErrorFlag::STOI_ERROR:
        cout << "ERROR: String to int fail" << endl;
        break;    
    case ErrorFlag::STOF_ERROR:
        cout << "ERROR: String to float fail" << endl;
        break;    
    default:
        break;
    }
}