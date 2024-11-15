// Implemente uma classe para representar um grafo utilizando lista de adjacências

#include <iostream> // Biblioteca padrão para entrada e saída
using namespace std;

// Define o tipo de dado para representar um vértice
typedef int vertex;

// Classe para representar um nó na lista de adjacência
class EdgeNode {
public:
    // Construtor: inicializa o vértice e o ponteiro para o próximo nó
    EdgeNode(vertex otherVertex, EdgeNode* next)
        : m_otherVertex(otherVertex), m_next(next) {}

    // Retorna o vértice adjacente armazenado neste nó
    vertex otherVertex() const {
        return m_otherVertex;
    }

    // Retorna o ponteiro para o próximo nó na lista
    EdgeNode* next() const {
        return m_next;
    }

    // Define o próximo nó na lista
    void setNext(EdgeNode* next) {
        m_next = next;
    }

private:
    vertex m_otherVertex;  // O vértice adjacente armazenado neste nó
    EdgeNode* m_next;      // Ponteiro para o próximo nó na lista
};

// Classe para representar o grafo usando lista de adjacência
class GraphAdjList {
public:
    // Construtor: inicializa o grafo com o número de vértices especificado
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        // Aloca memória para o array de listas de adjacência
        m_edges = new EdgeNode*[numVertices];
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = nullptr; // Inicializa todas as listas como vazias
        }
    }

    // Destrutor: libera a memória alocada para as listas de adjacência
    ~GraphAdjList() {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                EdgeNode* next = edge->next();
                delete edge; // Libera o nó atual
                edge = next; // Avança para o próximo nó
            }
        }
        delete[] m_edges; // Libera o array de listas
    }

    // Adiciona uma aresta entre dois vértices
    void addEdge(vertex v1, vertex v2) {
        // Verifica se a aresta já existe
        EdgeNode* edge = m_edges[v1];
        while (edge) {
            if (edge->otherVertex() == v2) { // Se a aresta já existir, retorna
                return;
            }
            edge = edge->next();
        }
        // Adiciona um novo nó na lista de adjacência do vértice v1
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
        m_numEdges++; // Incrementa o número de arestas
    }

    // Remove uma aresta entre dois vértices
    void removeEdge(vertex v1, vertex v2) {
        EdgeNode* edge = m_edges[v1];
        EdgeNode* previousEdge = nullptr;
        while (edge) {
            if (edge->otherVertex() == v2) { // Se encontrar a aresta
                if (previousEdge) {
                    previousEdge->setNext(edge->next()); // Remove do meio
                } else {
                    m_edges[v1] = edge->next(); // Remove do início
                }
                delete edge; // Libera o nó da memória
                m_numEdges--; // Decrementa o número de arestas
                return;
            }
            previousEdge = edge;
            edge = edge->next();
        }
    }

    // Imprime todas as arestas do grafo no formato "(v1, v2)"
    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            EdgeNode* edge = m_edges[i];
            while (edge) {
                cout << "(" << i << "," << edge->otherVertex() << ") ";
                edge = edge->next(); // Avança para o próximo nó
            }
            cout << endl; // Quebra de linha para cada vértice
        }
    }

private:
    int m_numVertices;     // Número de vértices no grafo
    int m_numEdges;        // Número de arestas no grafo
    EdgeNode** m_edges;    // Array de listas de adjacência
};

// Função principal para demonstrar o uso da classe GraphAdjList
int main() {
    GraphAdjList g2(6); // Cria um grafo com 6 vértices

    // Adiciona as arestas ao grafo
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);
    g2.addEdge(4, 1);

    // Imprime as arestas do grafo
    cout << "Lista de Arestas:" << endl;
    g2.print();

    return 0;
}
