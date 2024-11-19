// Implemente uma classe para representar um grafo utilizando lista de adjacências
#include <iostream>
using namespace std;
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
    
    
    // Método getter para m_edges (lista de adjacência)
    EdgeNode** edges() {
        return m_edges;
    }
    
    
    // Método que verifica se o grafo H é um subgrafo de G
    bool isSubGraph(GraphAdjList & h) {
    // Obtém a lista de adjacência de H
    EdgeNode ** hEdges = h.edges();  
    
    // Itera sobre cada vértice de G
    for (vertex i = 0; i < m_numVertices; i++) {  // Para cada vértice de G
        // Obtém a lista de arestas do vértice 'i' no grafo H
        EdgeNode * hEdge = hEdges[i];
        
        // Verifica cada aresta em H para o vértice 'i'
        while (hEdge) {  // Para cada aresta em H ligada ao vértice i
            // Obtém a lista de arestas do vértice 'i' no grafo G
            EdgeNode * gEdge = m_edges[i];
            bool found = false;
            
            // Verifica se a aresta de H existe em G
            while (gEdge) {  // Para cada aresta em G ligada ao vértice i
                // Se encontrar a aresta correspondente, marca como encontrada
                if (hEdge->otherVertex() == gEdge->otherVertex()) {
                    found = true;
                    break;  // Se encontrar, sai do loop
                }
                gEdge = gEdge->next();  // Avança para a próxima aresta em G
            }
            
            // Se a aresta de H não foi encontrada em G, retorna false
            if (!found) { 
                return false;  
            }
            
            hEdge = hEdge->next();  // Avança para a próxima aresta em H
        }
    }
    
    // Se todas as arestas de H foram encontradas em G, retorna true
    return true;
}

/*
Complexidade da função `isSubGraph()`:

- O loop externo percorre todos os vértices de G (O(V)), onde V é o número de vértices em G.
- Para cada vértice de G, a função percorre as arestas em H (O(E₁)) para esse vértice, onde E₁ é o número de arestas em H conectadas a cada vértice.
- Para cada aresta de H, a função percorre as arestas em G (O(E₂)) para o mesmo vértice, onde E₂ é o número de arestas de G conectadas ao vértice.

A complexidade total será aproximadamente O(V * (E₁ + E₂)).

No pior caso, onde o número de arestas em H e G é proporcional ao número de vértices (grafos densos), a complexidade pode ser O(V²). No entanto, para grafos esparsos, a complexidade é mais eficiente, sendo O(V * E), onde E é o número total de arestas de G e H.

Portanto, a complexidade da função `isSubGraph()` é O(V * E), onde:
- V é o número de vértices de G.
- E é o número total de arestas em G e H.
*/

};

int main() {
     // Criando o grafo principal (g) com 6 vértices
    GraphAdjList g(6);

    // Adicionando arestas ao grafo g
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(4, 1);

    // Criando o grafo h (subgrafo) com 6 vértices
    GraphAdjList h(6);

    // Adicionando arestas ao grafo h (subgrafo)
    h.addEdge(0, 1);
    h.addEdge(0, 2);
    h.addEdge(1, 3);
    h.addEdge(1, 4);
    h.addEdge(2, 4);
    h.addEdge(3, 4);

    // Exibindo as arestas do grafo g (principal)
    cout << "Grafo G (principal):" << endl;
    g.print();

    // Exibindo as arestas do grafo h (subgrafo)
    cout << "Grafo H (subgrafo):" << endl;
    h.print();

    // Verificando se o grafo h é subgrafo de g
    if (g.isSubGraph(h)) {
        cout << "O grafo H é um subgrafo de G." << endl;
    } else {
        cout << "O grafo H não é um subgrafo de G." << endl;
    }

    // Modificando o grafo h para testar o caso negativo
    h.removeEdge(1, 3); // Removendo uma aresta que está presente em g mas não em h

    // Exibindo as arestas do grafo h após a modificação
    cout << "Grafo H após remoção da aresta (1, 3):" << endl;
    h.print();

    // Verificando novamente se h é subgrafo de g após a modificação
    if (g.isSubGraph(h)) {
        cout << "O grafo H é um subgrafo de G." << endl;
    } else {
        cout << "O grafo H não é um subgrafo de G." << endl;
    }

    return 0;
}
