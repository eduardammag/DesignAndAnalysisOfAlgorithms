class GraphList:
    def __init__(self, num_vertices: int):
        self.num_vertices = num_vertices
        self.num_edges = 0

        # criando uma lista para cada vértice (lista de listas)
        self.adj_list = [[] for _ in range(num_vertices)]

    def has_edge(self, v1: int, v2: int) -> bool:
        return v2 in self.adj_list[v1]

    def add_edge(self, v1: int, v2: int):
        if not self.has_edge(v1, v2):
            self.adj_list[v1].append(v2)
            self.num_edges += 1

    def remove_edge(self, v1: int, v2: int):
        if self.has_edge(v1, v2):
            self.adj_list[v1].remove(v2)
            self.num_edges -= 1

    def print_edges(self):
        for i in range(self.num_vertices):
            for v2 in self.adj_list[i]:
                print(f"({i}, {v2})", end = " ")
            print()    

    def print_list(self):
        for i in range(self.num_vertices):
            print(f"{i}: {self.adj_list[i]}")


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