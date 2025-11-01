from graph_list import GraphList

# para G e H com o mesmo número de vértices, H é subgrafo de G?
def is_subgraph(G:GraphList, H:GraphList) -> bool:
    if G.num_vertices != H.num_vertices:
        return False
    
    for i in range(H.num_vertices):
        for v2 in H.adj_list[i]:
            if not G.has_edge(i, v2):
                return False
            
    return True      

#OVE

#ver a complexidade desses dois 
def is_subgraph_optimazed(G: GraphList, H: GraphList) -> bool:
    for i in range(H.num_vertices):
        g_edges = set(G.adj_list[i]) 
        #set é um conjunto criado a partir de uma tabela hash, a complexidade vai de O(n) - percorrer toda a lista - para o(1), calcula o hash e acha a posição
        for v2 in H.adj_list[i]:
            if v2 not in g_edges:
                return False
    return True        #O(V3)

#tenta usar o map pra ver quanto da

#Dado 𝐺 = (𝑉,𝐸) e um caminho 𝑃 composto por uma sequência de vértices.
# 𝑃 é um caminho de 𝐺? O caminho é simples (sem repetição de vértices)?

def is_path(graph: GraphList, path: list[int]) -> tuple[bool, bool]:
    "Funciona para grafos direcionados ou não."

    length = len(path)

    # Um caminho precisa ter pelo menos 2 vértices
    if length < 2:
        return False, False
    
    is_simple = True
    visited = set()

    for i in range(length-1):
        v1 = path[i]
        v2 = path[i+1]

        # Verifica se há uma aresta entre v1 e v2 no grafo
        if not graph.has_edge(v1, v2):
            return False, False
        
        # Verifica se o vértice atual já foi visitado
        if v1 in visited:
            is_simple = False 
        else:
            visited.add(v1)    
    
    # Checando o último vértice
    if path[-1] in visited:
        is_simple = False

    return True, is_simple    

# 3) Crie um algoritmo que verifica se a numeração dos vértices de um grafo G=(𝑉,𝐸) é topológica.

def is_topological(graph: GraphList) -> bool:
    """
    Verifica se a numeração dos vértices é uma ordenação topológica.
    Em uma ordenação topológica válida, todas as arestas vão de i -> j
    com i < j.
    """
    for i in range(graph.num_vertices):
        for neighbor in graph.adj_list[i]:
            if i >= neighbor:
                # Se existir uma aresta para um vértice menor ou igual, não é topológica
                return False
    return True

# 4) Crie um algoritmo para determinar se um grafo possui ordenação topológica e determiná-la