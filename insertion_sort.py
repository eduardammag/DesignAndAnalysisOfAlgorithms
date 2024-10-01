#Inserção Ordenação Crescente

def insertion_sort_asc(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

#Inserção Ordenação Decrescente

def insertion_sort_desc(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key > arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

# Exemplo de uso
arr = [12, 11, 13, 5, 6]
insertion_sort_asc(arr)
print("Array ordenado em ordem crescente:", arr)

insertion_sort_desc(arr)
print("Array ordenado em ordem decrescente:", arr)

def linear_search(arr, target):
    for i in range(len(arr)):
        if arr[i] == target:
            return i  # Retorna o índice onde o elemento foi encontrado
    return -1  # Retorna -1 se o elemento não for encontrado

# Exemplo de uso
arr = [10, 23, 45, 70, 11, 15]
target = 45

result = linear_search(arr, target)
if result != -1:
    print(f"Elemento {target} encontrado no índice {result}")
else:
    print(f"Elemento {target} não encontrado no array")
