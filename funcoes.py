# FATORIAL
def fatorial(n):
    if n==0:
        return 1
    elif n<0:
        raise ValueError("Função não definida para números negativos.")    
    return n*fatorial(n-1)    
    
# FIBONACCI
def fibonacci(n):
    if n ==0 or n==1:
        return n
    elif n<0:
        raise ValueError("Função não definida para números negativos.")
    return fibonacci(n-1) + fibonacci(n-2)    

    
# BUSCA BINÁRIA 
    #algoritmo eficiente para encontrar a posição de um elemento em uma lista ordenada
    
def binary_search(values, low, high, value):
    # Verifica se a sublista é válida (há elementos a serem verificados)
    if high >= low:
        # Calcula o índice do meio da sublista
        mid = (high + low) // 2
        
        # Se o valor no meio for o valor procurado, retorna o índice do meio
        if values[mid] == value:
            return mid
        
        # Se o valor do meio for maior que o procurado, busca na metade esquerda
        elif values[mid] > value:
            return binary_search(values, low, mid - 1, value)
        
        # Se o valor do meio for menor que o procurado, busca na metade direita
        else:
            return binary_search(values, mid + 1, high, value)
    
    # Caso a sublista não seja válida (valor não encontrado), retorna -1
    else:
        return -1
    
teste_fatorial = fatorial(4) 
teste_fibonacci = fibonacci(3)
values = [1, 3, 5, 7, 9, 11, 13, 15]  # Lista ordenada para busca
value_to_find = 7  
result = binary_search(values, 0, len(values) - 1, value_to_find)

print(teste_fatorial)
print(teste_fibonacci)
print(result)  # Saída esperada: 3, que é o índice do valor 7 na lista
