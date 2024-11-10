#include <iostream>

// Função que busca um valor 'x' no array 'v' de tamanho 'size'
int search(const int v[], int size, int x) {
    for (int i = 0; i < size; i++) {
        if (v[i] == x) {  // Se o valor for encontrado
            return i;     // Retorna o índice onde o valor foi encontrado
        }
    }
    return -1;  // Retorna -1 se o valor não for encontrado
}

int main() {
    // Definição do array
    int v[] = {1, 2, 3, 4, 5};
    int size = sizeof(v) / sizeof(v[0]);  // Calcula o tamanho do array
    int x = 3;  // Valor que queremos procurar

    // Chama a função de busca
    int result = search(v, size, x);

    // Verifica o resultado e imprime
    if (result != -1) {
        std::cout << "O valor " << x << " foi encontrado no índice " << result << std::endl;
    } else {
        std::cout << "O valor " << x << " não foi encontrado" << std::endl;
    }


    return 0;
}
