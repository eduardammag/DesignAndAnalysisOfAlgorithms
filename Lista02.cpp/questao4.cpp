#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <set>
#include <limits>

using namespace std;
typedef int vertex;

// Classe para representar um nó da lista de adjacência
class EdgeNode {
private:
    vertex m_otherVertex;
    EdgeNode* m_next;

public:
    EdgeNode(vertex otherVertex, EdgeNode* next)
        : m_otherVertex(otherVertex), m_next(next) {}

    vertex otherVertex() const { return m_otherVertex; }
    EdgeNode* next() const { return m_next; }
    void setNext(EdgeNode* next) { m_next = next; }
};

// Classe que representa o grafo usando listas de adjacência (direcionado)
class GraphAdjList {
private:
    int m_numVertices;
    int m_numEdges;
    EdgeNode** m_edges; // Lista de adjacências
    vector<tuple<vertex, vertex, int>> m_allEdges; // Lista de todas as arestas (v1, v2, peso)

public:
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        m_edges = new EdgeNode*[numVertices];
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = nullptr;
        }
    }

    // Adiciona uma aresta direcionada ao grafo
    void addEdge(vertex v1, vertex v2, int weight) {
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]); // Aresta de v1 -> v2
        m_allEdges.emplace_back(v1, v2, weight);
        m_numEdges++;
    }

    // Retorna o número de vértices
    int numVertices() const {
        return m_numVertices;
    }

    // Retorna todas as arestas
    vector<tuple<vertex, vertex, int>> edges() const {
        return m_allEdges;
    }

    // Imprime o grafo
    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            cout << "Vértice " << i << ": ";
            while (edge) {
                cout << edge->otherVertex() << " ";
                edge = edge->next();
            }
            cout << endl;
        }
    }

    ~GraphAdjList() {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                EdgeNode* next = edge->next();
                delete edge;
                edge = next;
            }
        }
        delete[] m_edges;
    }
};

const int INF = numeric_limits<int>::max(); // Valor infinito para inicialização

// Função para calcular a menor distância de qualquer vértice do caminho C
// até os demais vértices, com restrição de distância máxima X
void calculateDistanceFromPath(GraphAdjList& graph, const vector<int>& path, int X, vector<int>& minDistance) {
    int n = graph.numVertices();
    minDistance.assign(n, INF);
    set<vertex> pathSet(path.begin(), path.end()); // Facilita checar se um vértice está em C
    
    // Fila de prioridade para BFS com pesos
    queue<pair<vertex, int>> q; // {vértice, distância atual}
    
    // Inicializa as distâncias para os vértices em C
    for (vertex v : path) {
        minDistance[v] = 0;
        q.push({v, 0});
    }

    // BFS para calcular as distâncias mínimas de cada vértice de C
    while (!q.empty()) {
        auto [u, dist] = q.front();
        q.pop();
        
        // Percorre as arestas do vértice u
        for (auto& edge : graph.edges()) {
            vertex v1, v2;
            int weight;
            tie(v1, v2, weight) = edge; // Desempacota a tupla (v1, v2, weight)
            
            // Verifica se u é um dos vértices da aresta
            if (u == v1 || u == v2) {
                vertex v = (u == v1) ? v2 : v1; // Determina o outro vértice da aresta

                // Verifica a restrição de distância e atualiza se necessário
                if (dist + 1 <= X && minDistance[v] > dist + 1) {
                    minDistance[v] = dist + 1;
                    q.push({v, dist + 1});
                }
            }
        }
    }
}

// Algoritmo principal para encontrar o caminho mais barato C' respeitando as restrições
vector<int> findCheapestRestrictedPath(GraphAdjList& graph, const vector<int>& path, int X) {
    int n = graph.numVertices();
    vector<int> minDistance; // Distância mínima de um vértice de C
    calculateDistanceFromPath(graph, path, X, minDistance);

    // Algoritmo de Dijkstra modificado para encontrar C'
    priority_queue<tuple<int, vertex, vector<vertex>>, vector<tuple<int, vertex, vector<vertex>>>, greater<>> pq;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    
    vertex start = path.front(); // Início do caminho
    vertex end = path.back();    // Fim do caminho
    
    // Inicializa a fila de prioridade com o vértice inicial
    pq.push({0, start, {start}});
    distance[start] = 0;

    while (!pq.empty()) {
        auto [cost, u, currentPath] = pq.top();
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;

        // Se alcançarmos o destino, retornamos o caminho
        if (u == end) return currentPath;

        // Explora as vizinhanças de u
        for (auto& edge : graph.edges()) {
            vertex v1, v2;
            int weight;
            tie(v1, v2, weight) = edge; // Desempacota a tupla

            // Verifica se u é um dos vértices da aresta
            if (u == v1 || u == v2) {
                vertex v = (u == v1) ? v2 : v1;

                if (!visited[v] && distance[v] > cost + weight && minDistance[v] <= X) {
                    distance[v] = cost + weight;
                    vector<vertex> newPath = currentPath;
                    newPath.push_back(v);
                    pq.push({distance[v], v, newPath});
                }
            }
        }
    }
    return {}; // Retorna vazio se não encontrar caminho
}

int main() {
    // Exemplo de uso do algoritmo
    GraphAdjList graph(6);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 1);
    graph.addEdge(3, 4, 1);
    graph.addEdge(4, 5, 1);

    vector<vertex> path = {0, 5};
    int X = 2;

    vector<vertex> result = findCheapestRestrictedPath(graph, path, X);
    cout << "Caminho mais barato C': ";
    for (vertex v : result) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}
