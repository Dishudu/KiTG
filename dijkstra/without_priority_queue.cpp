#include <iostream>
#include <vector>
#include <climits>
#include <windows.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// Структура для хранения рёбер графа
struct Edge {
    int to;    // Вершина назначения
    int weight; // Вес ребра
};

// Функция для добавления рёбер в граф
void addEdge(vector<vector<Edge>>& graph, int from, int to, int weight) {
    graph[from].push_back({to, weight});
    // graph[to].push_back({from, weight}); // Если граф неориентированный
}

// Реализация алгоритма Дейкстры без очереди с приоритетом  
vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size();
    vector<int> distances(n, INT_MAX); // Минимальные расстояния до вершин
    distances[start] = 0; // Расстояние до стартовой вершины равно 0
    vector<bool> visited(n, false);   // Массив для отметки посещённых вершин

    for (int i = 0; i < n; ++i) {
        // Шаг 1: Найти вершину с минимальным расстоянием, которая ещё не обработана
        int min_distance = INT_MAX;
        int current_vertex = -1;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && distances[v] < min_distance) {
                min_distance = distances[v];
                current_vertex = v;
            }
        }

        if (current_vertex == -1) {
            // Все достижимые вершины обработаны
            break;
        }

        // Шаг 2: Отметить текущую вершину как посещённую
        visited[current_vertex] = true;

        // Шаг 3: Обновить расстояния до соседей текущей вершины
        for (const auto& edge : graph[current_vertex]) {
            int next_vertex = edge.to;
            int weight = edge.weight;

            if (!visited[next_vertex] &&
             distances[current_vertex] + weight < distances[next_vertex]) {
                distances[next_vertex] = distances[current_vertex] + weight;
            }
        }
    }

    return distances; // Возвращаем минимальные расстояния
}
int main(){
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем вывод в кодировке UTF-8
    // Пример использования
    int n = 500; // Количество вершин
    vector<vector<Edge>> graph(n);

    // Добавление рёбер
    srand(time(0));

    int vertices = 500, edges = 4000;
    for (int i = 0; i < edges; ++i) {
        int from = rand() % vertices;
        int to = rand() % vertices;
        int weight = rand() % 50 + 1; // Вес от 1 до 50
        addEdge(graph, from, to, weight);
    }

    int start = 0; // Начальная вершина

    auto start_time = chrono::high_resolution_clock::now(); //начало измерений
    vector<int> distances = dijkstra(graph, start);
    auto end_time = chrono::high_resolution_clock::now(); //конец измерений

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

    cout << "Время выполнения: " 
        << chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() 
        << " мкс\n";

    return 0;
}
