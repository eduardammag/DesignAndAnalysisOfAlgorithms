from graph_list import GraphList, is_subgraph, is_subgraph_optimazed
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