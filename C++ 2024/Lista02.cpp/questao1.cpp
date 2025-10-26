#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
using vertex = int;

// Estrutura de nó da aresta
class EdgeNode {
private:
    vertex m_otherVertex;
    EdgeNode* m_next;

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

// Grafo representado por uma lista de adjacências
class GraphAdjList {
private:
    int m_numVertices;
    EdgeNode** m_edges;

public:
    GraphAdjList(int numVertices)
        : m_numVertices(numVertices) {
        m_edges = new EdgeNode*[numVertices];
        for (vertex i = 0; i < numVertices; i++) {
            m_edges[i] = nullptr;
        }
    }

    void addEdge(vertex v1, vertex v2) {
        m_edges[v1] = new EdgeNode(v2, m_edges[v1]);
    }

    EdgeNode* getAdj(vertex v) const {
        return m_edges[v];
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

// Estrutura para armazenar informações de cada vértice
struct TreeNode {
    vertex v;
    TreeNode* pai;
    std::vector<TreeNode*> filhos;
    TreeNode(vertex v) : v(v), pai(nullptr) {}
};

// Função recursiva para construir a árvore a partir da lista de adjacências
void buildTree(GraphAdjList& graph, vertex v, TreeNode** nodes, TreeNode* parent) {
    TreeNode* node = new TreeNode(v);
    node->pai = parent;
    nodes[v] = node;

    for (EdgeNode* edge = graph.getAdj(v); edge != nullptr; edge = edge->next()) {
        vertex u = edge->otherVertex();
        if (!nodes[u]) {
            buildTree(graph, u, nodes, node);  // Recursão para construir a árvore
            node->filhos.push_back(nodes[u]);
        }
    }
}

// Função auxiliar para contar os descendentes em L2
int countDescendants(TreeNode* node, bool* L2) {
    int count = 0;
    for (TreeNode* filho : node->filhos) {
        if (L2[filho->v]) {
            count++;
        }
        count += countDescendants(filho, L2); // Recursão para contar descendentes
    }
    return count;
}

// Função para encontrar vértices com número ímpar de descendentes em L2
void findDescendantCondition(bool* L2, GraphAdjList& graph) {
    TreeNode** nodes = new TreeNode*[graph.numVertices()];
    buildTree(graph, 0, nodes, nullptr);  // Supondo que o vértice 0 seja a raiz da árvore

    for (vertex v = 0; v < graph.numVertices(); v++) {
        int descendantCount = countDescendants(nodes[v], L2);
        if (descendantCount % 2 == 1) {
            L2[v] = true;  // Se o número de descendentes é ímpar, adicione v a L2
        }
    }
}

// Função auxiliar para contar os ancestrais em L2
int countAncestors(TreeNode* node, bool* L2) {
    int count = 0;
    TreeNode* current = node->pai;
    while (current) {
        if (L2[current->v]) {
            count++;
        }
        current = current->pai;
    }
    return count;
}

// Função para encontrar vértices com número ímpar de ancestrais em L2
void findAncestorCondition(bool* L2, GraphAdjList& graph) {
    TreeNode** nodes = new TreeNode*[graph.numVertices()];
    buildTree(graph, 0, nodes, nullptr);  // Supondo que o vértice 0 seja a raiz da árvore

    for (vertex v = 0; v < graph.numVertices(); v++) {
        int ancestorCount = countAncestors(nodes[v], L2);
        if (ancestorCount % 2 == 1) {
            L2[v] = true;  // Se o número de ancestrais é ímpar, adicione v a L2
        }
    }
}

// Função auxiliar para contar primos mais velhos em L2
int countOlderCousins(TreeNode* node, bool* L2) {
    int count = 0;
    TreeNode* parent = node->pai;

    if (parent) {
        for (TreeNode* sibling : parent->filhos) {
            if (sibling != node) {
                // Contar primos mais velhos
                for (TreeNode* cousin : sibling->filhos) {
                    if (L2[cousin->v]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

// Função para encontrar vértices com número ímpar de primos mais velhos em L2
void findCousinCondition(bool* L2, GraphAdjList& graph) {
    TreeNode** nodes = new TreeNode*[graph.numVertices()];
    buildTree(graph, 0, nodes, nullptr);  // Supondo que o vértice 0 seja a raiz da árvore

    for (vertex v = 0; v < graph.numVertices(); v++) {
        int cousinCount = countOlderCousins(nodes[v], L2);
        if (cousinCount % 2 == 1) {
            L2[v] = true;  // Se o número de primos mais velhos é ímpar, adicione v a L2
        }
    }
}

int main() {
    // Criando um grafo com 7 vértices
    GraphAdjList graph(7);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    // Inicializando a lista L1 com alguns vértices
    bool L2[7] = {false, true, true, false, false, false, false};

    // Encontrando L2 para a condição dos descendentes
    findDescendantCondition(L2, graph);

    // Encontrando L2 para a condição dos ancestrais
    findAncestorCondition(L2, graph);

    // Encontrando L2 para a condição dos primos mais velhos
    findCousinCondition(L2, graph);

    // Exibindo L2 após as condições aplicadas
    std::cout << "Vértices que atendem às condições: ";
    for (int i = 0; i < 7; ++i) {
        if (L2[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
