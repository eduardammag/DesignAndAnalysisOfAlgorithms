# 2. BUSCA BINÁRIA (Iterativa)
# Pressupõe que a lista esteja ORDENADA.
def busca_binaria_iterativa(lista, alvo):
    """
    Implementação iterativa da busca binária.
    """
    esquerda = 0
    direita = len(lista) - 1

    while esquerda <= direita:
        meio = (esquerda + direita) // 2  # posição do meio

        if lista[meio] == alvo:
            return meio
        elif lista[meio] < alvo:
            esquerda = meio + 1  # descarta a metade esquerda
        else:
            direita = meio - 1  # descarta a metade direita

    return -1  # não encontrou


# 3. BUSCA BINÁRIA (Recursiva)
def busca_binaria_recursiva(lista, alvo, esquerda, direita):
    """
    Implementação recursiva da busca binária.
    """
    if esquerda > direita:
        return -1  # não encontrou

    meio = (esquerda + direita) // 2

    if lista[meio] == alvo:
        return meio
    elif lista[meio] < alvo:
        return busca_binaria_recursiva(lista, alvo, meio + 1, direita)
    else:
        return busca_binaria_recursiva(lista, alvo, esquerda, meio - 1)


# ----------------------------------------------
# TESTANDO OS ALGORITMOS
# ----------------------------------------------

if __name__ == "__main__":
    lista_desordenada = [10, 23, 45, 70, 11, 15]
    lista_ordenada = sorted(lista_desordenada)  # Necessária para busca binária
    alvo = 45

    print("Lista desordenada:", lista_desordenada)
    print("Lista ordenada:", lista_ordenada)
    print("Alvo:", alvo)

    # Busca sequencial
    print("\n[BUSCA SEQUENCIAL]")
    pos = busca_sequencial(lista_desordenada, alvo)
    print("Posição:", pos if pos != -1 else "Não encontrado")

    # Busca binária iterativa
    print("\n[BUSCA BINÁRIA ITERATIVA]")
    pos = busca_binaria_iterativa(lista_ordenada, alvo)
    print("Posição:", pos if pos != -1 else "Não encontrado")

    # Busca binária recursiva
    print("\n[BUSCA BINÁRIA RECURSIVA]")
    pos = busca_binaria_recursiva(lista_ordenada, alvo, 0, len(lista_ordenada) - 1)
    print("Posição:", pos if pos != -1 else "Não encontrado")


# 🔎 Diferenças e Semelhanças entre Iterativa e Recursiva:
#
# Semelhanças:
# - Ambos aplicam o mesmo princípio da busca binária: dividir a lista ordenada ao meio e descartar metade a cada passo.
# - Ambos têm complexidade de tempo O(log n), muito mais eficiente que a busca sequencial (O(n)).
#
# Diferenças:
# - Iterativa: usa um laço while e atualiza os índices até encontrar ou acabar o intervalo.
#   Vantagem: ocupa menos memória, pois não cria várias chamadas de função.
#   Mais comum em sistemas que precisam de eficiência.
#
# - Recursiva (discursiva): chama a si mesma em cada passo, reduzindo o problema a uma lista menor.
#   Vantagem: o código fica mais próximo da definição matemática do algoritmo, mais intuitivo de entender.
#   Desvantagem: cada chamada ocupa espaço na pilha de execução → em listas muito grandes pode causar estouro de pilha.
