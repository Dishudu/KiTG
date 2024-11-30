#include <vector>
#include <iostream>
#include <climits>

struct Edge{
    int to;
    int weight;
};

void addEdge(std::vector<std::vector<Edge>> &graph, int from, int to, int weight){
    graph[from].push_back({to, weight});
    //graph[to].push_back({from, weight}); // Для неориентированного графа
}

std::vector<int> dijkstra(const std::vector<std::vector<Edge>> &graph, int start){
    int n = graph.size();
    std::vector<int> distances(n, INT_MAX);
    distances[start] = 0;
    std::vector<bool> visited(n, false);

    for(int i = 0; i < n; i++){
        int min_distance = INT_MAX;
        int current_vertex = -1;

        for(int vertex = 0; vertex < n; vertex++){
            if(!visited[vertex] && distances[vertex] < min_distance){
                min_distance = distances[vertex];
                current_vertex = vertex;
            }
        }

        if(current_vertex == -1){break;}

        visited[current_vertex] = true;

        for(const auto &edge : graph[current_vertex]){
            int next_vertex = edge.to;
            int weight = edge.weight;
            
            if(!visited[next_vertex] && distances[current_vertex] + weight < distances[next_vertex]){
                distances[next_vertex] = distances[current_vertex] + weight;
            }
        }   
    }

    return distances;
}