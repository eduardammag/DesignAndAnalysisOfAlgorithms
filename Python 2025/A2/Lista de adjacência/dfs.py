from graph_list import GraphList

def dfs_recursive(graph: GraphList, v: int, pre_order: list[int], counter: list[int]) -> None:
    """
    Marca o vértice `v` como visitado e explora seus vizinhos recursivamente.
    """
    pre_order[v] = counter[0]
    print(f"Visitando vertice {v} -> pre_order = {pre_order}, contador = {counter[0]}")
    counter[0] += 1

    for neighbor in graph.adj_list[v]:
        if pre_order[neighbor] == -1:
            print(f" Indo de {v} -> {neighbor}")
            dfs_recursive(graph, neighbor, pre_order, counter)

    print(f"Retornando de {v}")


def dfs(graph: GraphList, start_vertex: int = 0) -> list[int]:
    """
    Retorna a lista pre_order, indicando o instante de descoberta de cada vértice.
    """
    num_vertices = graph.num_vertices
    pre_order: list[int] = [-1] * num_vertices
    counter: list[int] = [0]

    print(f"\n--- Iniciando DFS a partir do vertice {start_vertex} ---")
    dfs_recursive(graph, start_vertex, pre_order, counter)

    for v in range(num_vertices):
        if pre_order[v] == -1:
            print(f"\n--- Iniciando nova DFS em componente desconexa a partir do vertice {v} ---")
            dfs_recursive(graph, v, pre_order, counter)

    print("\nDFS finalizada. Ordem final de visita:")
    print(pre_order)
    return pre_order


# Tempo de execução:
# 1. Cada vértice do grafo é visitado exatamente uma vez.
# 2. Para cada vértice, percorremos todos os seus vizinhos na lista de adjacência.
# 3. Cada aresta do grafo é examinada no máximo uma vez (para grafos direcionados)
#    ou duas vezes (para grafos não direcionados), mas isso ainda é O(E).

#   Tempo total = O(V + E)
#     - O(V) para visitar todos os vértices
#     - O(E) para percorrer todas as arestas

# Espaço utilizado:
# 1. A lista pre_order tem tamanho V → O(V)
# 2. A lista counter tem tamanho 1 → O(1)
# 3. Pilha de chamadas recursivas no pior caso pode ter profundidade O(V)
#
# Espaço total = O(V)

#   Para qualquer DFS, conte quantas vezes cada vértice é visitado (O(V))
#   e quantas vezes cada aresta é percorrida (O(E)), some os dois e terá O(V + E).

