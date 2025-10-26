// Dado um grafo não direcionado conexo com pesos, retorne a aresta cuja remoção causaria o maior aumento no custo da árvore geradora míınima.

#include <iostream>
#include <vector>
#include <algorithm>
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

// Classe que representa o grafo usando listas de adjacência
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

    // Adiciona uma aresta ao grafo
    void addEdge(vertex v1, vertex v2, int weight) {
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
        m_edges[v2] = new EdgeNode(v1, m_edges[v2]); // Grafo não-direcionado
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

// Classe auxiliar para a Union-Find (Disjoint-Set)
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Algoritmo de Kruskal para encontrar a MST
int kruskal(GraphAdjList& graph, vector<tuple<vertex, vertex, int>>& mstEdges) {
    vector<tuple<vertex, vertex, int>> edges = graph.edges();
    sort(edges.begin(), edges.end(), [](auto& e1, auto& e2) {
        return get<2>(e1) < get<2>(e2);
    });

    UnionFind uf(graph.numVertices());
    int mstCost = 0;

    for (auto& [v1, v2, weight] : edges) {
        if (uf.find(v1) != uf.find(v2)) {
            uf.unionSets(v1, v2);
            mstCost += weight;
            mstEdges.push_back({v1, v2, weight});
        }
    }

    return mstCost;
}

// Calcula o aumento crítico no custo ao remover uma aresta da MST
int criticalEdgeMST(GraphAdjList& graph) {
    vector<tuple<vertex, vertex, int>> mstEdges;
    int mstCost = kruskal(graph, mstEdges);

    int maxIncrease = 0;

    for (auto& edge : mstEdges) {
        GraphAdjList tempGraph(graph.numVertices());

        // Reconstroi o grafo sem a aresta removida
        for (auto& e : graph.edges()) {
            if (e != edge) {
                tempGraph.addEdge(get<0>(e), get<1>(e), get<2>(e));
            }
        }

        vector<tuple<vertex, vertex, int>> newMSTEdges;
        int newMSTCost = kruskal(tempGraph, newMSTEdges);

        maxIncrease = max(maxIncrease, newMSTCost - mstCost);
    }

    return maxIncrease;
}

int main() {
    GraphAdjList graph(6);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 0, 4);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 5, 2);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 3);
    graph.addEdge(5, 4, 3);

    cout << "Grafo (Lista de Adjacência):" << endl;
    graph.print();

    vector<tuple<vertex, vertex, int>> mstEdges;
    int mstCost = kruskal(graph, mstEdges);

    cout << "\nÁrvore Geradora Mínima (MST):" << endl;
    for (auto& [v1, v2, weight] : mstEdges) {
        cout << "(" << v1 << ", " << v2 << ", " << weight << ")" << endl;
    }
    cout << "Custo Total da MST: " << mstCost << endl;

    int criticalIncrease = criticalEdgeMST(graph);
    cout << "\nAumento Máximo ao Remover uma Aresta Crítica: " << criticalIncrease << endl;

    return 0;
}
