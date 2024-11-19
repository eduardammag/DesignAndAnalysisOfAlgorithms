#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm> 

using namespace std;

typedef int vertex;

class EdgeNode {
private:
    vertex m_otherVertex;
    EdgeNode* m_next;
    
public:
    EdgeNode(vertex otherVertex, EdgeNode* next)
        : m_otherVertex(otherVertex), m_next(next) {}

    vertex otherVertex() const {
        return m_otherVertex;
    }

    EdgeNode* next() const {
        return m_next;
    }

    void setNext(EdgeNode* next) {
        m_next = next;
    }
};

class GraphAdjList {
private:
    int m_numVertices;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices) {
        m_edges = new EdgeNode*[numVertices];
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = NULL;
        }
    }

    void addEdge(vertex v1, vertex v2) {
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
    }

    EdgeNode* getAdj(vertex v) const {
        return m_edges[v];
    }

    int numVertices() const {
        return m_numVertices;
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

// Função de BFS para encontrar o caminho mais curto entre dois vértices
vector<vertex> bfs(const GraphAdjList& graph, vertex start, vertex end) {
    vector<int> parent(graph.numVertices(), -1);  // Para reconstruir o caminho
    vector<bool> visited(graph.numVertices(), false);
    queue<vertex> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        vertex u = q.front();
        q.pop();

        if (u == end) {
            break;  // Encontramos o destino, podemos parar a busca
        }

        for (EdgeNode* edge = graph.getAdj(u); edge != nullptr; edge = edge->next()) {
            vertex v = edge->otherVertex();
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    // Reconstruir o caminho de start a end
    vector<vertex> path;
    for (vertex v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());  // Reverter o caminho para a ordem correta
    return path;
}

// Função principal que encontra o menor caminho passando por todos os vértices de L em ordem
vector<vertex> findMinPathThroughList(GraphAdjList& graph, const vector<vertex>& L) {
    vector<vertex> fullPath;
    
    for (size_t i = 0; i < L.size() - 1; ++i) {
        vector<vertex> path = bfs(graph, L[i], L[i+1]);
        if (path.empty()) {
            return {};  // Se não houver caminho entre L[i] e L[i+1], retornar vetor vazio
        }

        // Adiciona o caminho entre L[i] e L[i+1] ao caminho total (sem repetir o vértice inicial)
        if (!fullPath.empty()) {
            path.erase(path.begin());  // Remove o primeiro vértice, pois já foi incluído
        }
        fullPath.insert(fullPath.end(), path.begin(), path.end());
    }

    return fullPath;
}

// Função de exemplo para rodar o algoritmo
int main() {
    GraphAdjList graph(5);  // Grafo com 5 vértices (0 a 4)
    
    // Adicionando arestas (grafo direcionado sem pesos)
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 0);
    
    // Lista L de vértices
    vector<vertex> L = {0, 2, 4};  // Lista L com os vértices [0, 2, 4]
    
    // Encontrando o menor caminho que passa por todos os vértices de L em ordem
    vector<vertex> path = findMinPathThroughList(graph, L);
    
    // Imprimindo o caminho
    if (path.empty()) {
        cout << "Não há caminho válido." << endl;
    } else {
        cout << "Menor caminho que passa por todos os vértices de L: ";
        for (vertex v : path) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
