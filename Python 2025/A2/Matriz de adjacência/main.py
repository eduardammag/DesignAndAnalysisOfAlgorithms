from graph_matrix import *
from funcoes import *
from dfs import *

g1= GraphMatrix(6)
g1.print_matriz()

print("###############################")

g1.add_edge(0, 1)
g1.add_edge(0, 2)
g1.add_edge(1, 3)
g1.add_edge(1, 4)
g1.add_edge(2, 4)
g1.add_edge(3, 4)
g1.add_edge(4, 5)
g1.add_edge(4, 1)
g1.print_matriz()

print("###############################")

print(g1.has_edge(4,5))
g1.remove_edges(4,5)
print(g1.has_edge(4,5))

print("###############################")

g1.print_matriz()

print("###############################")

g1.print_edges()

g2 = GraphMatrix(6)
g3 = GraphMatrix(4)
g3.add_edge(0, 1)
g3.add_edge(1, 2)
g3.add_edge(2, 3)
g3.add_edge(0, 3)

g4 = GraphMatrix(4)
g4.add_edge(0, 1)
g4.add_edge(1, 2)

g2.add_edge(0, 1)
g2.add_edge(1, 2)
print("g2 is subgraph of g1?" , is_subgraph(g1, g2))
print("g4 is subgraph of g3?" , is_subgraph(g3, g4))


print("###############################")
g5 = GraphMatrix(5)
g5.add_edge(0, 1)
g5.add_edge(1, 2)
g5.add_edge(2, 3)
g5.add_edge(3, 4)

# Caminho válido e simples
print(is_path(g5, [0, 1, 2, 3]))      

# Caminho válido, mas não simples (repete vértice)
print(is_path(g5, [0, 1, 2, 1, 2]))   

# Caminho inválido (falta aresta 3→1)
print(is_path(g5, [0, 1, 2, 3, 1]))   

print("###############################")

g6 = GraphMatrix(5)
g6.add_edge(0, 1)
g6.add_edge(0, 2)
g6.add_edge(1, 3)
g6.add_edge(3, 4)

print("g6")
dfs(g6)

print("###############################")

g7 = GraphMatrix(3)
g7.add_edge(0, 1)
g7.add_edge(1, 2)


print("g7")
dfs(g7, start_vertex=1)

print("###############################")
g8 = GraphMatrix(6)
g8.add_edge(0, 1)
g8.add_edge(1, 2)
g8.add_edge(2, 3)
g8.add_edge(3, 4)
g8.add_edge(4, 5)
g8.add_edge(5, 0)  

print("g8")
dfs(g8)

print("###############################")
g9 = GraphMatrix(4)
g9.add_edge(0, 1)
g9.add_edge(1, 2)
g9.add_edge(2, 3)

print(is_topological(g9))  

g9.add_edge(3, 1)  
print(is_topological(g9))  

print("###############################")

# Criando grafo
g10 = GraphMatrix(6)
g10.add_edge(5, 2)
g10.add_edge(5, 0)
g10.add_edge(4, 0)
g10.add_edge(4, 1)
g10.add_edge(2, 3)
g10.add_edge(3, 1)

g11 = GraphMatrix(3)
g11.add_edge(0, 1)
g11.add_edge(1, 2)
g11.add_edge(2, 0) 

# Função de ordenação topológica
has_order, order = has_topological_order(g10)
print("Tem ordenação topológica?", has_order)
print("Ordem topológica:", order)

has_order, order = has_topological_order(g11)
print("Tem ordenação topológica?", has_order)
print("Ordem topológica:", order)