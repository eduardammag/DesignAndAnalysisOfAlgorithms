//Dados dois grafos 𝐺 = (𝑉,𝐸) e 𝐻 = (𝑉’,𝐸’) com 𝑉 = 𝑉’, crie um algoritmo que verifica se 𝐻 é subgrafo de 𝐺.

// Função para verificar se um grafo H é subgrafo de G usando matriz de adjacência
bool isSubGraph(GraphMatrix &h) {
    // Obtém a matriz de adjacência de H
    bool **hEdges = h.edges();

    // Percorre todos os pares de vértices
    for (vertex i = 0; i < m_numVertices; i++) {
        for (vertex j = 0; j < m_numVertices; j++) {
            // Se existe uma aresta em H, verifica se ela também existe em G
            if (hEdges[i][j]) {
                if (!m_edges[i][j]) { // Se não existe em G
                    return false;    // H não é subgrafo de G
                }
            }
        }
    }
    return true; // Todos os pares de arestas de H estão presentes em G
}

/* 
Complexidade:
- **Percorrer a matriz:** Há dois loops aninhados para percorrer todos os pares de vértices, o que resulta em uma complexidade de \( O(|V|^2) \).
- **Verificação de aresta:** Cada verificação é \( O(1) \), pois estamos acessando diretamente uma célula da matriz.

**Complexidade total:** \( O(|V|^2) \).

Como \( H \) possui o mesmo conjunto de vértices que \( G \), a complexidade não depende diretamente do número de arestas, apenas do número de vértices \( |V| \).

Observação: Este método é eficiente para grafos densos, mas pode ser menos eficiente para grafos esparsos devido ao alto custo em espaço e tempo das matrizes.
*/


// Função para verificar se um grafo H é subgrafo de G usando lista de adjacência
bool isSubGraph(GraphAdjList &h) {
    // Obtém a lista de adjacência de H
    EdgeNode **hEdges = h.edges();

    // Percorre todos os vértices do grafo
    for (vertex i = 0; i < m_numVertices; i++) {
        EdgeNode *hEdge = hEdges[i]; // Lista de arestas de H para o vértice i

        // Para cada aresta em H, verifica se ela também existe em G
        while (hEdge) {
            EdgeNode *gEdge = m_edges[i]; // Lista de arestas de G para o vértice i
            bool found = false;

            // Percorre a lista de arestas de G para encontrar a aresta de H
            while (gEdge) {
                if (hEdge->otherVertex() == gEdge->otherVertex()) {
                    found = true; // Aresta encontrada em G
                    break;
                }
                gEdge = gEdge->next();
            }

            // Se a aresta não foi encontrada em G, H não é subgrafo de G
            if (!found) {
                return false;
            }

            hEdge = hEdge->next(); // Próxima aresta de H
        }
    }
    return true; // Todas as arestas de H estão presentes em G
}

/* 
Complexidade:
- **Loop externo (vértices):** Percorre todos os \( |V| \) vértices.
- **Loop interno (arestas de H):** Para cada vértice, percorre as arestas de H adjacentes a ele. Seja \( d_H(v) \) o grau do vértice em H.
- **Loop mais interno (arestas de G):** Para cada aresta de H, percorre as arestas de G adjacentes ao mesmo vértice. Seja \( d_G(v) \) o grau do vértice em G.

**Complexidade total:** \( O(\sum_{v \in V} d_H(v) \cdot d_G(v)) \), que pode ser aproximada como \( O(|E_H| \cdot d_{G,\text{max}}) \), onde \( d_{G,\text{max}} \) é o maior grau em \( G \).

Para grafos esparsos, onde \( |E_H| \ll |V|^2 \), este método pode ser mais eficiente que o método baseado em matriz.

**Otimização possível:**
- Usar um mapa ou conjunto para armazenar as arestas de G e verificar a existência de arestas em \( O(1) \) em vez de \( O(d_G(v)) \).
*/

#include <unordered_set>
#include <utility> // Para std::pair
#include <vector>

// Função para verificar se um grafo H é subgrafo de G usando lista de adjacência e otimização com conjuntos
bool isSubGraphOptimized(GraphAdjList &h) {
    // Criar um conjunto para armazenar as arestas de G no formato (v1, v2)
    std::unordered_set<std::pair<int, int>, pair_hash> gEdges;

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
