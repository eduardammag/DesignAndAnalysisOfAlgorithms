#include <iostream>
#include <vector>

// Definição do tipo vertex como um inteiro
typedef int vertex;

// Classe Graph para representar o grafo com vértices e arestas
class Graph {
public:
    int m_numVertices;                    // Número de vértices no grafo
    std::vector<std::vector<bool>> adj;   // Matriz de adjacência (grafo não direcionado)

    // Construtor para inicializar o grafo com um número de vértices
    Graph(int numVertices) : m_numVertices(numVertices), adj(numVertices, std::vector<bool>(numVertices, false)) {}

    // Função para adicionar uma aresta entre dois vértices
    void addEdge(vertex v1, vertex v2) {
        adj[v1][v2] = true;
        adj[v2][v1] = true;  // Para grafo não direcionado
    }

    // Função para verificar se existe uma aresta entre v1 e v2
    bool hasEdge(vertex v1, vertex v2) const {
        return adj[v1][v2];
    }

    // Função para verificar se o caminho é válido
    bool isPath(const vertex path[], int length) const {
        if (length < 2) {
            return false;  // O caminho deve ter pelo menos 2 vértices
        }

        int vertexInx = 0;
        vertex v1 = path[vertexInx++];

        // Verifica se há uma aresta entre cada par de vértices consecutivos
        do {
            vertex v2 = path[vertexInx++];
            if (!hasEdge(v1, v2)) {  // Se não houver aresta, o caminho não é válido
                return false;
            }
            v1 = v2;  // Atualiza v1 para v2
        } while (vertexInx < length);

        return true;  // Se todas as arestas são válidas, o caminho é válido
    }

    // Função para verificar se o caminho é válido e se contém ciclo
    bool isPath(const vertex path[], int length, bool& hasCycle) const {
        if (length < 2) {
            return false;  // O caminho deve ter pelo menos 2 vértices
        }

        int vertexInx = 0;
        vertex v1 = path[vertexInx++];

        // Array para marcar vértices visitados
        std::vector<bool> visited(m_numVertices, false);
        visited[v1] = true;

        // Verifica se há uma aresta entre cada par de vértices consecutivos
        do {
            vertex v2 = path[vertexInx++];

            if (!hasEdge(v1, v2)) {  // Se não houver aresta, o caminho não é válido
                return false;
            }

            // Se o vértice v2 já foi visitado, então há um ciclo
            if (visited[v2]) {
                hasCycle = true;  // Detecta ciclo
            }

            visited[v2] = true;  // Marca v2 como visitado
            v1 = v2;  // Atualiza v1 para v2
        } while (vertexInx < length);

        return true;  // Se todas as arestas são válidas, o caminho é válido
    }
};

int main() {

    // Criando um grafo com 4 vértices
    Graph g(4);

    // Adicionando arestas ao grafo
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    // Caminho a ser verificado
    vertex path[] = {0, 1, 2, 3};  // Um caminho com 4 vértices
    int length = 4;

    // Verifica se o caminho é válido
    bool validPath = g.isPath(path, length);
    if (validPath) {
        std::cout << "O caminho é válido!" << std::endl;
    } else {
        std::cout << "O caminho não é válido." << std::endl;
    }

    // Verifica se o caminho é válido e se contém ciclos
    bool hasCycle = false;
    validPath = g.isPath(path, length, hasCycle);
    if (validPath) {
        if (hasCycle) {
            std::cout << "O caminho é válido, mas contém um ciclo!" << std::endl;
        } else {
            std::cout << "O caminho é válido e não contém ciclos." << std::endl;
        }
    } else {
        std::cout << "O caminho não é válido." << std::endl;
    }

    // Testando um caminho com ciclo
    vertex pathWithCycle[] = {0, 1, 2, 3, 0};  // Um caminho com um ciclo (volta para o vértice 0)
    length = 5;

    hasCycle = false;
    validPath = g.isPath(pathWithCycle, length, hasCycle);
    if (validPath) {
        if (hasCycle) {
            std::cout << "O caminho é válido, mas contém um ciclo!" << std::endl;
        } else {
            std::cout << "O caminho é válido e não contém ciclos." << std::endl;
        }
    } else {
        std::cout << "O caminho não é válido." << std::endl;
    }

    return 0;
}
