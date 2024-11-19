//Dados dois grafos 𝐺 = (𝑉,𝐸) e 𝐻 = (𝑉’,𝐸’) com 𝑉 = 𝑉’, crie um algoritmo otimizado usando lista de adjacência que verifica se 𝐻 é subgrafo de 𝐺.

//Usar o símbolo & em um parâmetro de uma função faz com que a função não receba uma cópia do objeto GraphMatrix como argumento, 
//mas sim uma referência ao objeto original. Isso significa que qualquer modificação feita no objeto h dentro da função afetará o objeto original, 
//pois ambos se referem ao mesmo dado na memória.

#include <iostream>
using namespace std;
#include <unordered_set>
#include <utility>
#include <vector>

typedef int vertex;

class EdgeNode {
private:
    vertex m_otherVertex; // O vértice de destino da aresta.
    EdgeNode* m_next;     // Ponteiro para o próximo nó da lista (próxima aresta).

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
    int m_numEdges;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        m_edges = new EdgeNode*[numVertices];
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = NULL;
        }
    }

    void addEdge(vertex v1, vertex v2) {
        EdgeNode* edge = m_edges[v1];
        while (edge) {
            if (edge->otherVertex() == v2) {
                return;
            }
            edge = edge->next();
        }
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
        m_numEdges++;
    }

    void removeEdge(vertex v1, vertex v2) {
        EdgeNode* edge = m_edges[v1];
        EdgeNode* previousEdge = NULL;
        while (edge) {
            if (edge->otherVertex() == v2) {
                if (previousEdge) {
                    previousEdge->setNext(edge->next());
                } else {
                    m_edges[v1] = edge->next();
                }
                delete edge;
                m_numEdges--;
                return;
            }
            previousEdge = edge;
            edge = edge->next();
        }
    }

    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                cout << "(" << i << "," << edge->otherVertex() << ") ";
                edge = edge->next();
            }
        }
        cout << endl;
    }

    EdgeNode** edges() const {
        return m_edges;
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


// Função para verificar se um grafo H é subgrafo de G usando lista de adjacência e otimização com conjuntos
bool isSubGraphOptimized(GraphAdjList &h) {
    // Criar um conjunto para armazenar as arestas de G no formato (v1, v2)
    unordered_set<pair<int, int>, pair_hash> gEdges;

    // Preencher o conjunto com as arestas de G
    for (vertex i = 0; i < m_numVertices; i++) {
        EdgeNode *gEdge = m_edges[i];
        while (gEdge) {
            gEdges.insert({i, gEdge->otherVertex()}); // Adiciona a aresta de G
            gEdge = gEdge->next();
        }
    }

    // Verificar as arestas de H
    EdgeNode **hEdges = h.edges(); // Obter a lista de adjacência de H
    for (vertex i = 0; i < m_numVertices; i++) {
        EdgeNode *hEdge = hEdges[i];
        while (hEdge) {
            // Verifica se a aresta de H está presente no conjunto de arestas de G
            if (gEdges.find({i, hEdge->otherVertex()}) == gEdges.end()) {
                return false; // Aresta de H não encontrada em G
            }
            hEdge = hEdge->next();
        }
    }

    return true; // Todas as arestas de H estão presentes em G
}

// Função hash para std::pair, necessária para usar pares em unordered_set
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

/*
Complexidade:
1. **Construção do conjunto gEdges:**
   - Percorre todas as arestas de G, inserindo-as no conjunto.
   - Tempo: \( O(|E|) \), onde \( |E| \) é o número de arestas em G.

2. **Verificação das arestas de H:**
   - Para cada aresta de H, verifica sua presença no conjunto.
   - Cada busca em um unordered_set é \( O(1) \), então o custo total é \( O(|E_H|) \), onde \( |E_H| \) é o número de arestas em H.

**Complexidade total:** \( O(|E| + |E_H|) \).

Esta solução é eficiente para grafos esparsos, pois o custo é proporcional ao número de arestas em vez de \( O(|V|^2) \).
*/
int main() {
    GraphAdjList G(5);
    GraphAdjList H(5);

    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 3);

    H.addEdge(0, 1);
    H.addEdge(1, 2);

    cout << (isSubGraph(G, H) ? "H é subgrafo de G" : "H não é subgrafo de G") << endl;

    GraphMatrix Gm(5);
    GraphMatrix Hm(5);

    Gm.addEdge(0, 1);
    Gm.addEdge(1, 2);
    Gm.addEdge(2, 3);

    Hm.addEdge(0, 1);
    Hm.addEdge(1, 2);

    cout << (isSubGraph(Gm, Hm) ? "Hm é subgrafo de Gm" : "Hm não é subgrafo de Gm") << endl;

    return 0;
}
