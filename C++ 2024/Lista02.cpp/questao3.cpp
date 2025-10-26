#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;

typedef int vertex;
const int INF = numeric_limits<int>::max();

// Classe para representar o grafo usando listas de adjacência
class GraphAdjList {
private:
    int m_numVertices;
    vector<vector<pair<vertex, int>>> adjList;

public:
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices), adjList(numVertices) {}

    // Adiciona uma aresta direcionada ao grafo
    void addEdge(vertex v1, vertex v2, int weight) {
        adjList[v1].emplace_back(v2, weight);
    }

    // Retorna o número de vértices
    int numVertices() const {
        return m_numVertices;
    }

    // Retorna as adjacências de um vértice
    const vector<pair<vertex, int>>& getAdj(vertex v) const {
        return adjList[v];
    }
};

// Função auxiliar para calcular a menor distância de uma fonte usando Dijkstra
vector<int> dijkstra(GraphAdjList &graph, vertex source) {
    int numVertices = graph.numVertices(); // Número de vértices
    vector<int> dist(numVertices, INF);    // Inicializa as distâncias como infinito
    vector<bool> visited(numVertices, false); // Marca os vértices visitados
    dist[source] = 0;

    // Fila de prioridade (min-heap)
    priority_queue<pair<int, vertex>, vector<pair<int, vertex>>, greater<pair<int, vertex>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        vertex u = pq.top().second;
        pq.pop();

        if (visited[u]) continue; // Ignorar se já foi processado
        visited[u] = true;

        for (const auto &[v, weight] : graph.getAdj(u)) {
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist; // Retorna as menores distâncias do vértice de origem
}

// Função principal para encontrar o vértice desejado
vertex findOptimalVertex(GraphAdjList &graph, const vector<vertex> &L) {
    int numVertices = graph.numVertices();
    vector<vector<int>> allDistances(L.size(), vector<int>(numVertices, INF));

    // Calcula as distâncias de cada vértice na lista L
    for (size_t i = 0; i < L.size(); i++) {
        allDistances[i] = dijkstra(graph, L[i]);
    }

    vertex optimalVertex = -1;
    int minMaxDistance = INF;

    // Para cada vértice do grafo, calcula o máximo das distâncias
    for (vertex v = 0; v < numVertices; v++) {
        int maxDistance = 0;
        for (size_t i = 0; i < L.size(); i++) {
            maxDistance = max(maxDistance, allDistances[i][v]);
        }
        if (maxDistance < minMaxDistance) {
            minMaxDistance = maxDistance;
            optimalVertex = v;
        }
    }

    return optimalVertex;
}

int main() {
    // Exemplo de uso
    GraphAdjList graph(5); // Grafo com 5 vértices
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 3);
    graph.addEdge(2, 4, 4);

    vector<vertex> L = {0, 1}; // Conjunto de vértices
    vertex optimal = findOptimalVertex(graph, L);

    cout << "Vértice ótimo: " << optimal << endl;

    return 0;
}
