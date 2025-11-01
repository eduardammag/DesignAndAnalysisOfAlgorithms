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

