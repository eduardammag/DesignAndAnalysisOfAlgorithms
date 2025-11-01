from graph_list import *
from funcoes import *
from dfs import *

g1= GraphList(6)
g1.print_list()

print("###############################")

g1.add_edge(0, 1)
g1.add_edge(0, 2)
g1.add_edge(1, 3)
g1.add_edge(1, 4)
g1.add_edge(2, 4)
g1.add_edge(3, 4)
g1.add_edge(4, 5)
g1.add_edge(4, 1)
g1.print_list()

print("###############################")

print(g1.has_edge(4,5))
g1.remove_edge(4,5)
print(g1.has_edge(4,5))

print("###############################")

g1.print_list()
print("###############################")

g1.print_edges()

g2 = GraphList(6)
g3 = GraphList(4)
g3.add_edge(0, 1)
g3.add_edge(1, 2)
g3.add_edge(2, 3)
g3.add_edge(0, 3)

g4 = GraphList(4)
g4.add_edge(0, 1)
g4.add_edge(1, 2)

g2.add_edge(0, 1)
g2.add_edge(1, 2)
print("g2 is subgraph of g1?" , is_subgraph(g1, g2))
print("g4 is subgraph of g3?" , is_subgraph(g3, g4))


print("g2 is subgraph of g1?" , is_subgraph_optimazed(g1, g2))
print("g4 is subgraph of g3?" , is_subgraph_optimazed(g3, g4))

print("###############################")

g5 = GraphList(5)
g5.add_edge(0, 1)
g5.add_edge(1, 2)
g5.add_edge(2, 3)
g5.add_edge(3, 4)

print("Lista de adjacencia:")
g5.print_list()

caminhos = [
[0, 1, 2, 3],     # caminho válido e simples
[0, 1, 2, 1, 0],  # válido mas nao simples (repetições)
[0, 2, 3],        # inválido (nao há aresta direta 0–2)
]

for c in caminhos:
    valido, simples = is_path(g5, c)
    print(f"Caminho {c} -> valido: {valido}, simples: {simples}")


print("###############################")

g6 = GraphList(6)
g6.add_edge(0, 1)
g6.add_edge(0, 2)
g6.add_edge(1, 3)
g6.add_edge(1, 4)
g6.add_edge(2, 5)

print("Lista de adjacência:")
g6.print_list()

pre_order = dfs(g6)

print("###############################")

g7= GraphList(5)
g7.add_edge(0, 1)
g7.add_edge(0, 2)
g7.add_edge(1, 3)
g7.add_edge(2, 3)
g7.add_edge(3, 4)

g7.print_list()
print("A numeraçao e topologica?", is_topological(g7))

# Adicionando uma aresta que viola a topologia
g7.add_edge(3, 1)
print("Apos adicionar 3 -> 1, a numeraçao e topologica?", is_topological(g7))

print("###############################")

# Criando grafo
g8 = GraphList(6)
g8.add_edge(5, 2)
g8.add_edge(5, 0)
g8.add_edge(4, 0)
g8.add_edge(4, 1)
g8.add_edge(2, 3)
g8.add_edge(3, 1)

g9 = GraphList(3)
g9.add_edge(0, 1)
g9.add_edge(1, 2)
g9.add_edge(2, 0) 

# Função de ordenação topologica
has_order, order = has_topological_order(g8)
print("Tem ordenação topologica?", has_order)
print("Ordem topologica:", order)

has_order, order = has_topological_order(g9)
print("Tem ordenação topologica?", has_order)
print("Ordem topologica:", order)