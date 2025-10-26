class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.key = key

# Questão 1: Encontrar o nó com índice mínimo
def find_minimum(node):
    current = node
    while current.left is not None:
        current = current.left
    return current.key

# Questão 2: Encontrar o nó com índice máximo
def find_maximum(node):
    current = node
    while current.right is not None:
        current = current.right
    return current.key

# Questão 3: Encontrar o sucessor de um nó
def find_successor(root, node):
    if node.right:
        return find_minimum(node.right)

    successor = None
    current = root
    while current:
        if node.key < current.key:
            successor = current
            current = current.left
        elif node.key > current.key:
            current = current.right
        else:
            break
    return successor.key if successor else None

# Questão 4: Encontrar o predecessor de um nó
def find_predecessor(root, node):
    if node.left:
        return find_maximum(node.left)

    predecessor = None
    current = root
    while current:
        if node.key > current.key:
            predecessor = current
            current = current.right
        elif node.key < current.key:
            current = current.left
        else:
            break
    return predecessor.key if predecessor else None

# Questão 5: Inserir uma chave mantendo as propriedades da BST
def insert(node, key):
    if node is None:
        return Node(key)

    if key < node.key:
        node.left = insert(node.left, key)
    else:
        node.right = insert(node.right, key)
    
    return node

# Questão 6: Remover um nó mantendo as propriedades da BST
def remove(node, key):
    if node is None:
        return node

    if key < node.key:
        node.left = remove(node.left, key)
    elif key > node.key:
        node.right = remove(node.right, key)
    else:
        if node.left is None:
            return node.right
        elif node.right is None:
            return node.left

        temp = find_minimum(node.right)
        node.key = temp
        node.right = remove(node.right, temp)

    return node
