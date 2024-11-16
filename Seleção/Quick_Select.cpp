#include <stdio.h>

// Função auxiliar: particiona o array em torno de um pivô
int partition(int v[], int l, int r) {
    int pivot = v[r]; // Escolhe o último elemento como pivô
    int i = l - 1;    // Índice do menor elemento

    for (int j = l; j < r; j++) {
        if (v[j] <= pivot) {
            i++;
            // Troca v[i] e v[j]
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    // Coloca o pivô na posição correta
    int temp = v[i + 1];
    v[i + 1] = v[r];
    v[r] = temp;

    return i + 1; // Retorna a posição do pivô
}

// Função quickselect: encontra o k-ésimo menor elemento no array
int quickselect(int v[], int l, int r, int x) {
    // Verifica se a posição 'x' é válida no intervalo atual
    if (x > 0 && x <= r - l + 1) {
        // Encontra a posição do pivô após particionar o array
        int j = partition(v, l, r);

        // Caso base: se o pivô está na posição desejada, retorna o valor do pivô
        if (j - l == x - 1) {
            return v[j];
        }

        // Se a posição do pivô está à esquerda do k-ésimo menor,
        // chama quickselect recursivamente para a metade esquerda do array
        if (j - l > x - 1) {
            return quickselect(v, l, j - 1, x);
        }

        // Caso contrário, chama quickselect recursivamente para a metade direita do array,
        // ajustando a posição de 'x' para refletir o novo intervalo
        return quickselect(v, j + 1, r, x - j + l - 1);
    }

    // Retorna -1 se 'x' estiver fora dos limites do array
    return -1;
}

int main() {
    // Exemplo de uso
    int arr[] = {12, 3, 5, 7, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3; // Queremos o 3º menor elemento

    int result = quickselect(arr, 0, n - 1, k);

    if (result != -1) {
        printf("O %dº menor elemento é: %d\n", k, result);
    } else {
        printf("Posição inválida!\n");
    }

    return 0;
}
