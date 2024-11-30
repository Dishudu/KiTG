#include <iostream>
#include <vector>
#include <queue>
#include <climits> // Для INT_MAX
#include <windows.h>
using namespace std;

// Структура для хранения рёбер графа
struct Edge {
    int to;    // Вершина назначения
    int weight; // Вес ребра
};

// Функция для добавления ребра в граф
void addEdge(vector<vector<Edge>>& graph, int from, int to, int weight) {
    graph[from].push_back({to, weight});
    // graph[to].push_back({from, weight}); // Если граф неориентированный
}

// Реализация алгоритма Дейкстры
vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX); // Минимальные расстояния до вершин
    distances[start] = 0; // Расстояние до стартовой вершины равно 0

    // Очередь с приоритетом, где пары {расстояние, вершина}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        // Если расстояние устарело, пропускаем вершину 
        if (current_distance > distances[current_vertex]) continue;

        // Обрабатываем соседей текущей вершины
        for (const auto& edge : graph[current_vertex]) {
            int next_vertex = edge.to;
            int weight = edge.weight;

            // Рассчитываем потенциальное новое расстояние
            int new_distance = current_distance + weight;
            if (new_distance < distances[next_vertex]) {
                distances[next_vertex] = new_distance;
                pq.push({new_distance, next_vertex});
            }
        }
    }

    return distances; // Возвращаем минимальные расстояния
}

int main() {
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем вывод в кодировке UTF-8
    // Пример использования
    int n = 5; // Количество вершин
    vector<vector<Edge>> graph(n);

    // Добавление рёбер
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 3);

    int start = 0; // Начальная вершина
    vector<int> distances = dijkstra(graph, start);

    // Вывод результатов
    cout << "Минимальные расстояния от вершины " << start << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Вершина " << i << ": ";
        if (distances[i] == INT_MAX) {
            cout << "Недостижима\n";
        } else {
            cout << distances[i] << "\n";
        }
    }

    return 0;
}
