// Dado um grafo não direcionado conexo com pesos, retorne a aresta cuja remoção causaria o maior aumento no custo da árvore geradora míınima.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

// Representação de uma aresta
struct Edge {
    int u, v, weight;
    bool inMST;
};

// União-Find para gerenciar componentes conectados
struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int x) {
        if (x != parent[x]) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;
        if (rank[rootX] < rank[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rank[rootX] == rank[rootY]) rank[rootX]++;
        return true;
    }
};

// Função para calcular a MST usando Kruskal
pair<int, vector<Edge>> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
        return a.weight < b.weight;
    });
    UnionFind uf(n);
    vector<Edge> mst;
    int totalWeight = 0;
    for (Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mst.push_back(e);
            totalWeight += e.weight;
            e.inMST = true;
        }
    }
    return {totalWeight, mst};
}

// Função principal para encontrar a aresta crítica
Edge findCriticalEdge(int n, vector<Edge>& edges) {
    auto [mstWeight, mst] = kruskal(n, edges);
    Edge criticalEdge = {-1, -1, -1, false};
    int maxIncrease = 0;

    for (Edge& e : mst) {
        UnionFind uf(n);
        int newWeight = 0;

        for (Edge& other : edges) {
            if (other.inMST && other.u != e.u && other.v != e.v) {
                if (uf.unite(other.u, other.v)) {
                    newWeight += other.weight;
                }
            }
        }

        for (Edge& other : edges) {
            if (!other.inMST && uf.find(other.u) != uf.find(other.v)) {
                newWeight += other.weight;
                break;
            }
        }

        int increase = newWeight - mstWeight;
        if (increase > maxIncrease) {
            maxIncrease = increase;
            criticalEdge = e;
        }
    }

    return criticalEdge;
}

int main() {
    int n = 5; // Número de vértices
    vector<Edge> edges = {
        {0, 1, 1, false}, {0, 2, 3, false}, {1, 2, 2, false},
        {1, 3, 4, false}, {2, 4, 5, false}, {3, 4, 6, false}
    };

    Edge critical = findCriticalEdge(n, edges);
    cout << "Aresta crítica: (" << critical.u << ", " 
         << critical.v << ") com peso " << critical.weight << endl;

    return 0;
}