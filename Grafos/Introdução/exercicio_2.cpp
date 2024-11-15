// Dado um grafo 𝐺 = (𝑉,𝐸) e um caminho 𝑃 composto por uma sequência de vértices, verifique se 𝑃 é um caminho de 𝐺, e se o caminho é simples.

#include <vector>
#include <unordered_set>
#include <iostream>

bool isPathAndSimpleMatrix(GraphMatrix &g, const std::vector<int> &path) {
    int n = path.size();
    bool **adjMatrix = g.edges(); // Obter a matriz de adjacência

    // Verificar se cada aresta do caminho existe
    for (int i = 0; i < n - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        if (!adjMatrix[u][v]) { // Se não há aresta entre u e v
            return false;
        }
    }

    // Verificar se o caminho é simples
    std::unordered_set<int> visited;
    for (int v : path) {
        if (visited.find(v) != visited.end()) {
            return false; // Encontrou repetição
        }
        visited.insert(v);
    }

    return true; // É um caminho válido e simples
}

/*
Complexidade:
1. **Verificação de arestas:** \( O(|P|) \), onde \( |P| \) é o número de vértices no caminho.
   - Cada busca na matriz é \( O(1) \).
2. **Verificação de simplicidade:** \( O(|P|) \), devido ao uso de um conjunto.
3. **Complexidade total:** \( O(|P|) \), linear no tamanho do caminho.
*/


#include <vector>
#include <unordered_set>
#include <iostream>

bool isPathAndSimpleList(GraphAdjList &g, const std::vector<int> &path) {
    int n = path.size();
    EdgeNode **adjList = g.edges(); // Obter a lista de adjacência

    // Verificar se cada aresta do caminho existe
    for (int i = 0; i < n - 1; i++) {
        int u = path[i];
        int v = path[i + 1];

        // Percorrer a lista de adjacência de u
        bool found = false;
        EdgeNode *edge = adjList[u];
        while (edge) {
            if (edge->otherVertex() == v) {
                found = true;
                break;
            }
            edge = edge->next();
        }
        if (!found) { // Se não encontrou a aresta
            return false;
        }
    }

    // Verificar se o caminho é simples
    std::unordered_set<int> visited;
    for (int v : path) {
        if (visited.find(v) != visited.end()) {
            return false; // Encontrou repetição
        }
        visited.insert(v);
    }

    return true; // É um caminho válido e simples
}

/*
Complexidade:
1. **Verificação de arestas:** \( O(|P| \cdot d_{G,\text{max}}) \), onde \( d_{G,\text{max}} \) é o grau máximo em \( G \).
   - Percorrer a lista de adjacência é \( O(d_{G,\text{max}}) \) por vértice.
2. **Verificação de simplicidade:** \( O(|P|) \), devido ao uso de um conjunto.
3. **Complexidade total:** \( O(|P| \cdot d_{G,\text{max}}) \).
*/

/*
Comparação das abordagens para verificar se um caminho é válido e simples:

1. **Matriz de Adjacência**:
   - **Vantagens**:
     - Verificação de arestas é extremamente eficiente: \( O(1) \) por par de vértices.
     - Ideal para grafos densos onde \( |E| \) é próximo de \( |V|^2 \).
   - **Desvantagens**:
     - Alta utilização de memória: \( O(|V|^2) \), mesmo em grafos esparsos.
     - Menos eficiente em grafos com poucos vértices conectados.

2. **Lista de Adjacência**:
   - **Vantagens**:
     - Economiza memória: \( O(|V| + |E|) \), ideal para grafos esparsos.
     - Aloca apenas espaço proporcional ao número de arestas presentes.
   - **Desvantagens**:
     - Verificação de arestas pode ser mais lenta: \( O(d_{G,\text{max}}) \), onde \( d_{G,\text{max}} \) é o grau máximo do grafo.
     - Menor desempenho em grafos densos devido à necessidade de percorrer listas.

3. **Complexidade Comparada**:
   - **Matriz de Adjacência**: \( O(|P|) \), onde \( |P| \) é o número de vértices no caminho.
   - **Lista de Adjacência**: \( O(|P| \cdot d_{G,\text{max}}) \), dependendo do grau máximo do grafo.

**Conclusão**:
- Utilize **matriz de adjacência** para grafos densos onde a rapidez na verificação de arestas é essencial e há recursos de memória disponíveis.
- Prefira **lista de adjacência** em grafos esparsos para reduzir o uso de memória e melhor eficiência geral.
*/
