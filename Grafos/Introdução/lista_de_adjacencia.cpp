// Implemente uma classe para representar um grafo utilizando lista de adjacências
#include <iostream>
using namespace std;

// Define o tipo "vertex" como um sinonimo para "int"
typedef int vertex;

// Classe que representa um nó da lista de adjacência (um destino para uma aresta).
class EdgeNode {
private:
    vertex m_otherVertex; // O vértice de destino da aresta.
    EdgeNode* m_next;     // Ponteiro para o próximo nó da lista (próxima aresta).

public:
    // Construtor que inicializa o vértice de destino e o próximo nó.
    EdgeNode(vertex otherVertex, EdgeNode* next)
        : m_otherVertex(otherVertex), m_next(next) {}

    // Retorna o vértice de destino da aresta.
    vertex otherVertex() const {
        return m_otherVertex;
    }

    // Retorna o ponteiro para o próximo nó.
    EdgeNode* next() const {
        return m_next;
    }

    // Atualiza o ponteiro para o próximo nó.
    void setNext(EdgeNode* next) {
        m_next = next;
    }
};

// Classe que representa o grafo usando listas de adjacência.
class GraphAdjList {
private:
    int m_numVertices;  // Número de vértices no grafo.
    int m_numEdges;     // Número de arestas no grafo.
    EdgeNode** m_edges; // Array de ponteiros para listas de adjacência.

public:
    // Construtor que inicializa o grafo com um número fixo de vértices.
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        m_edges = new EdgeNode*[numVertices]; // Aloca espaço para as listas.
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = NULL; // Inicializa todas as listas como vazias.
        }
    }

    // Função para adicionar uma aresta entre v1 e v2.
    void addEdge(vertex v1, vertex v2) {
        EdgeNode* edge = m_edges[v1]; // Percorre a lista de adjacência de v1.
        while (edge) {
            if (edge->otherVertex() == v2) { // Se a aresta já existe, não faz nada.
                return;
            }
            edge = edge->next();
        }
        // Cria um novo nó no início da lista de adjacência de v1.
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
        m_numEdges++; // Incrementa o contador de arestas.
    }

    // Função para remover uma aresta entre v1 e v2.
    void removeEdge(vertex v1, vertex v2) {
        EdgeNode* edge = m_edges[v1];       // Ponteiro para percorrer a lista.
        EdgeNode* previousEdge = NULL;     // Ponteiro para manter o nó anterior.
        while (edge) {
            if (edge->otherVertex() == v2) { // Encontra a aresta.
                if (previousEdge) {
                    // Se há um nó anterior, conecta o anterior ao próximo.
                    previousEdge->setNext(edge->next());
                } else {
                    // Se não há nó anterior, atualiza o início da lista.
                    m_edges[v1] = edge->next();
                }
                delete edge; // Libera a memória da aresta removida.
                m_numEdges--; // Decrementa o contador de arestas.
                return;
            }
            previousEdge = edge;  // Atualiza o nó anterior.
            edge = edge->next();  // Avança para o próximo nó.
        }
    }

    // Função para imprimir as arestas do grafo.
    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                cout << "(" << i << "," << edge->otherVertex() << ") ";
                edge = edge->next(); // Avança para o próximo nó.
            }
        }
        cout << endl;
    }

    // Destrutor que libera toda a memória alocada.
    ~GraphAdjList() {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                EdgeNode* next = edge->next();
                delete edge; // Libera cada nó da lista de adjacência.
                edge = next;
            }
        }
        delete[] m_edges; // Libera o array de listas de adjacência.
    }
};

int main() {
    GraphAdjList g(6); // Cria um grafo com 6 vértices.

    // Adiciona algumas arestas ao grafo.
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 1);

    // Exibe todas as arestas do grafo.
    cout << "Lista de arestas antes de remover alguma aresta:" << endl;
    g.print();

    // Remove uma aresta.
    g.removeEdge(4, 1);

    // Exibe todas as arestas novamente.
    cout << "Lista de arestas após remover a aresta (4,1):" << endl;
    g.print();

    // Remove outra aresta.
    g.removeEdge(1, 3);

    // Exibe as arestas novamente.
    cout << "Lista de arestas após remover a aresta (1,3):" << endl;
    g.print();

    return 0;
}
