//Dados dois grafos 𝐺 = (𝑉,𝐸) e 𝐻 = (𝑉’,𝐸’) com 𝑉 = 𝑉’, crie um algoritmo que verifica se 𝐻 é subgrafo de 𝐺.

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

class GraphMatrix {
private:
    int m_numVertices;
    int m_numEdges;
    bool** m_edges;

public:
    GraphMatrix(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        m_edges = new bool*[m_numVertices];
        for (vertex i = 0; i < m_numVertices; i++) {
            m_edges[i] = new bool[m_numVertices];
            for (vertex j = 0; j < m_numVertices; j++) {
                m_edges[i][j] = false;
            }
        }
    }

    bool hasEdge(vertex v1, vertex v2) const {
        return m_edges[v1][v2];
    }

    void addEdge(vertex v1, vertex v2) {
        if (!hasEdge(v1, v2)) {
            m_edges[v1][v2] = true;
            m_numEdges++;
        }
    }

    void removeEdge(vertex v1, vertex v2) {
        if (hasEdge(v1, v2)) {
            m_edges[v1][v2] = false;
            m_numEdges--;
        }
    }

    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            for (vertex j = 0; j < m_numVertices; j++) {
                if (hasEdge(i, j)) {
                    cout << "(" << i << "," << j << ") ";
                }
            }
            cout << endl;
        }
    }

    void printMatrix() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            for (vertex j = 0; j < m_numVertices; j++) {
                cout << m_edges[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool** edges() const {
        return m_edges;
    }

    int numVertices() const {
        return m_numVertices;
    }

    ~GraphMatrix() {
        for (int i = 0; i < m_numVertices; i++) {
            delete[] m_edges[i];
        }
        delete[] m_edges;
    }
};


// Função para verificar se um grafo H é subgrafo de G usando matriz de adjacência
bool isSubGraph(const GraphMatrix& G, const GraphMatrix& h) {
    // Obtenha as matrizes de adjacência dos grafos G e H
    bool** gEdges = G.edges();  // Matriz de adjacências do grafo G
    bool** hEdges = h.edges();  // Matriz de adjacências do grafo H

    // Itera sobre todos os vértices do grafo H
    for (vertex i = 0; i < h.numVertices(); i++) {
        // Itera sobre todos os vértices do grafo H
        for (vertex j = 0; j < h.numVertices(); j++) {
            // Se houver uma aresta entre os vértices i e j no grafo H
            if (hEdges[i][j]) {
                // Verifica se essa aresta também existe no grafo G
                if (!gEdges[i][j]) {
                    // Se a aresta não existir em G, H não é um subgrafo de G
                    return false;
                }
            }
        }
    }
    // Se todas as arestas de H forem encontradas em G, então H é um subgrafo de G
    return true;
}


/* 
Complexidade:
- Há 2 loops aninhados para percorrer todos os pares de vértices, o que resulta em uma complexidade de (O(|V|^2)).
- Cada verificação de aresta é (O(1)), pois estamos acessando diretamente uma célula da matriz.
Como H possui o mesmo conjunto de vértices que G, a complexidade não depende diretamente do número de arestas, apenas do número de vértices.
Obs:: Este método é eficiente para grafos densos, mas pode ser menos eficiente para grafos esparsos devido ao alto custo em espaço e tempo.
*/


// Função para verificar se um grafo H é subgrafo de G usando lista de adjacência
bool isSubGraph(const GraphAdjList& G, const GraphAdjList& h) {
    EdgeNode** gEdges = G.edges();
    EdgeNode** hEdges = h.edges();

    for (vertex i = 0; i < h.numVertices(); i++) {
        EdgeNode* hEdge = hEdges[i];
        while (hEdge) {
            EdgeNode* gEdge = gEdges[i];
            bool found = false;
            while (gEdge) {
                if (hEdge->otherVertex() == gEdge->otherVertex()) {
                    found = true;
                    break;
                }
                gEdge = gEdge->next();
            }
            if (!found) {
                return false;
            }
            hEdge = hEdge->next();
        }
    }
    return true;
}

/* 
-Loop externo (vértices): Percorre todos os |V| vértices.
-Loop interno (arestas de H): Para cada vértice, percorre as arestas de H adjacentes a ele. Seja d_H(v) o grau do vértice em H.
-Loop mais interno (arestas de G): Para cada aresta de H, percorre as arestas de G adjacentes ao mesmo vértice. Seja d_G(v) o grau do vértice em G.

-Complexidade total: O(∑_{v ∈ V} [d_H(v) · d_G(v)]),
que pode ser aproximada como O(|E_H| · d_{G,max}), onde d_{G,max} é o maior grau de G.
Isso significa que, para cada vértice em H, estamos verificando as arestas correspondentes em G,
comparando os graus dos vértices em ambos os grafos. 
O tempo de execução é proporcional ao número total de arestas em H multiplicado pelo maior grau de G.
Para grafos esparsos, onde o número de arestas |E_H| é muito menor do que |V|^2, 
este método baseado em listas pode ser mais eficiente do que o método baseado em matrizes,
pois as listas de adjacência permitem um acesso mais eficiente às arestas,
especialmente quando o grau de G é relativamente baixo.
 
-Otimização possível: Usar um mapa ou conjunto para armazenar as arestas de G e verificar a existência de arestas em O(1) em vez de O(d_G(v)).
*/

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
