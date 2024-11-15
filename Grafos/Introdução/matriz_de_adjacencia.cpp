//Implemente uma classe para representar um grafo utilizando matriz de adjacências

#include <iostream> // Biblioteca padrão para entrada e saída
using namespace std;

// Define o tipo de dado para representar um vértice
typedef int vertex;

// Classe para representar o grafo com matriz de adjacência
class GraphMatrix {
private:
    int m_numVertices;           // Número de vértices no grafo
    int m_numEdges;              // Número de arestas no grafo
    bool** m_edges;              // Ponteiro para a matriz de adjacência

public:
    // Construtor: inicializa a matriz de adjacência
    GraphMatrix(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) {
        // Aloca memória para a matriz de adjacência
        m_edges = new bool*[m_numVertices];
        for (vertex i = 0; i < m_numVertices; i++) {
            m_edges[i] = new bool[m_numVertices];
            // Inicializa todos os elementos da matriz como "false" (sem aresta)
            for (vertex j = 0; j < m_numVertices; j++) {
                m_edges[i][j] = false;
            }
        }
    }

    // Destrutor: libera a memória alocada para a matriz de adjacência
    ~GraphMatrix() {
        for (int i = 0; i < m_numVertices; i++) {
            delete[] m_edges[i]; // Libera memória de cada linha
        }
        delete[] m_edges; // Libera o ponteiro principal
    }

    // Verifica se existe uma aresta entre dois vértices
    bool hasEdge(vertex v1, vertex v2) const {
        return m_edges[v1][v2]; // Retorna o valor da matriz na posição (v1, v2)
    }

    // Adiciona uma aresta entre dois vértices
    void addEdge(vertex v1, vertex v2) {
        if (!hasEdge(v1, v2)) { // Apenas adiciona se a aresta não existir
            m_edges[v1][v2] = true; // Marca a aresta como existente
            m_numEdges++; // Incrementa o número de arestas
        }
    }

    // Remove a aresta entre dois vértices
    void removeEdge(vertex v1, vertex v2) {
        if (hasEdge(v1, v2)) { // Apenas remove se a aresta existir
            m_edges[v1][v2] = false; // Marca a aresta como inexistente
            m_numEdges--; // Decrementa o número de arestas
        }
    }

    // Imprime todas as arestas do grafo no formato "(v1, v2)"
    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            for (vertex j = 0; j < m_numVertices; j++) {
                if (hasEdge(i, j)) { // Se existir uma aresta, imprime
                    cout << "(" << i << "," << j << ") ";
                }
            }
            cout << endl; // Quebra de linha para cada vértice
        }
    }

    // Imprime a matriz de adjacência
    void printMatrix() const {
        for (vertex i = 0; i < m_numVertices; i++) {
            for (vertex j = 0; j < m_numVertices; j++) {
                cout << m_edges[i][j] << " "; // Exibe o valor (0 ou 1)
            }
            cout << endl; // Quebra de linha para a próxima linha da matriz
        }
    }
};

// Função principal para demonstrar o uso da classe GraphMatrix
int main() {
    GraphMatrix g1(6); // Cria um grafo com 6 vértices

    // Adiciona as arestas ao grafo
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 4);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.addEdge(4, 1);

    // Imprime as arestas do grafo
    cout << "Lista de Arestas:" << endl;
    g1.print();

    // Imprime a matriz de adjacência
    cout << "Matriz de Adjacência:" << endl;
    g1.printMatrix();

    return 0;
}