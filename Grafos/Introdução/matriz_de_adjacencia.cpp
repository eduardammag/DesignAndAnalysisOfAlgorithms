//Implemente uma classe para representar um grafo utilizando matriz de adjacências
#include <iostream> 
using namespace std;

// Define um tipo `vertex` como sinônimo de `int`
typedef int vertex; 

// Declaração da classe GraphMatrix para representar um grafo com matriz de adjacência
class GraphMatrix {
private:
    int m_numVertices; // Número de vértices no grafo
    int m_numEdges;    // Número de arestas no grafo
    bool** m_edges;    // Ponteiro duplo para representar a matriz de adjacência

public:
    // Construtor que inicializa o grafo com um número específico de vértices
    GraphMatrix(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0) { // Inicializa número de vértices e arestas
        m_edges = new bool*[m_numVertices]; // Aloca um array de ponteiros para as linhas da matriz
        for (vertex i = 0; i < m_numVertices; i++) { // Para cada linha da matriz:
            m_edges[i] = new bool[m_numVertices]; // Aloca um array de booleanos
            for (vertex j = 0; j < m_numVertices; j++) { // Inicializa cada célula da matriz
                m_edges[i][j] = false; // Define que inicialmente não há arestas
            }
        }
    }

    // Verifica se existe uma aresta entre dois vértices (consulta apenas)
    bool hasEdge(vertex v1, vertex v2) const {
        return m_edges[v1][v2]; // Retorna o valor na matriz de adjacência
    }

    // Adiciona uma aresta entre dois vértices
    void addEdge(vertex v1, vertex v2) {
        if (!hasEdge(v1, v2)) {       // Verifica se a aresta já não existe
            m_edges[v1][v2] = true;  // Marca a célula correspondente como verdadeira
            m_numEdges++;            // Incrementa o contador de arestas
        }
    }

    // Remove uma aresta entre dois vértices
    void removeEdge(vertex v1, vertex v2) {
        if (hasEdge(v1, v2)) {       // Verifica se a aresta existe
            m_edges[v1][v2] = false; // Marca a célula correspondente como falsa
            m_numEdges--;            // Decrementa o contador de arestas
        }
    }

    // Imprime todas as arestas do grafo como pares de vértices
    void print() const {
        for (vertex i = 0; i < m_numVertices; i++) {      // Percorre todas as linhas
            for (vertex j = 0; j < m_numVertices; j++) {  // Percorre todas as colunas
                if (hasEdge(i, j)) {                      // Se há uma aresta
                    cout << "(" << i << "," << j << ")";  // Imprime o par de vértices
                }
            }
            cout << endl; // Quebra de linha após cada linha da matriz
        }
    }

    // Imprime a matriz de adjacência
    void printMatrix() const {
        for (vertex i = 0; i < m_numVertices; i++) {     // Percorre todas as linhas
            for (vertex j = 0; j < m_numVertices; j++) { // Percorre todas as colunas
                cout << m_edges[i][j] << " ";           // Imprime o valor da célula
            }
            cout << endl; // Quebra de linha após cada linha da matriz
        }
    }

    // Destrutor que desaloca a matriz de adjacência
    ~GraphMatrix() {
        for (int i = 0; i < m_numVertices; i++) { // Para cada linha da matriz
            delete[] m_edges[i]; // Libera a memória do array da linha
        }
        delete[] m_edges; // Libera o array de ponteiros
    }
};

int main() {
    GraphMatrix g1(6); // Cria um grafo com 6 vértices

    // Imprime a matriz de adjacência inicial
    g1.printMatrix();

    // Adiciona várias arestas ao grafo
    g1.addEdge(0, 1);
    g1.addEdge(0, 0);
    g1.addEdge(0, 2);
    g1.addEdge(1, 3);
    g1.addEdge(1, 4);
    g1.addEdge(2, 4);
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    g1.addEdge(4, 1);

    // Imprime as arestas na forma de pares de vértices
    g1.print();

    // Imprime novamente a matriz de adjacência após as adições
    g1.printMatrix();

    return 0; // Finaliza o programa
}
