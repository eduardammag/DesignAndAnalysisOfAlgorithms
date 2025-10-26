#include <stdio.h>
#include <stdlib.h>

// Função auxiliar: ordena um array para encontrar a mediana
void quicksort(int v[], int left, int right) {
    if (left < right) {
        int pivot = v[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (v[j] <= pivot) {
                i++;
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }

        int temp = v[i + 1];
        v[i + 1] = v[right];
        v[right] = temp;

        int partitionIndex = i + 1;
        quicksort(v, left, partitionIndex - 1);
        quicksort(v, partitionIndex + 1, right);
    }
}

// Função auxiliar: retorna a mediana de um array ordenado
int medianOf(int v[], int n) {
    quicksort(v, 0, n - 1); // Ordena o array
    return v[n / 2];        // Retorna o elemento central
}

// Função auxiliar: particiona o array em torno de um pivô
int partition(int v[], int p, int r, int pivot) {
    // Encontra a posição do pivô e o move para o final
    int pivotIndex;
    for (pivotIndex = p; pivotIndex <= r; pivotIndex++) {
        if (v[pivotIndex] == pivot) {
            break;
        }
    }
    int temp = v[pivotIndex];
    v[pivotIndex] = v[r];
    v[r] = temp;

    // Particiona o array em torno do pivô
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] <= pivot) {
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    temp = v[i + 1];
    v[i + 1] = v[r];
    v[r] = temp;

    return i + 1; // Retorna a posição do pivô
}

// Função principal: encontra o k-ésimo menor elemento usando o algoritmo do MOM (Median of Medians)
int selectMOM(int v[], int p, int r, int k) {
    int n = r - p + 1; // Tamanho do array no intervalo
    if (k <= 0 || k > n) {
        return -1; // Retorna -1 se a posição k for inválida
    }

    // Passo 1: Divide o array em grupos de 5 e calcula as medianas
    int median[(n + 4) / 5]; // Array para armazenar as medianas
    int i = 0;
    int pos = p;
    while (pos <= r) {
        int size = r - pos + 1; // Tamanho do grupo
        median[i++] = medianOf(&v[pos], (size >= 5) ? 5 : size); // Calcula a mediana do grupo
        pos += 5; // Avança para o próximo grupo
    }

    // Passo 2: Encontra a mediana das medianas
    int mom = (i == 1) ? median[i - 1] : selectMOM(median, 0, i - 1, i / 2);

    // Passo 3: Particiona o array em torno da mediana das medianas
    int j = partition(v, p, r, mom);

    // Passo 4: Determina a posição do k-ésimo menor elemento
    if (j - p == k - 1) {
        return v[j]; // O pivô é o k-ésimo menor elemento
    }
    if (j - p > k - 1) {
        // O k-ésimo menor está à esquerda
        return selectMOM(v, p, j - 1, k);
    }
    // O k-ésimo menor está à direita
    return selectMOM(v, j + 1, r, k - j + p - 1);
}

int main() {
    // Exemplo de array
    int arr[] = {12, 3, 5, 7, 19, 26, 4, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4; // Queremos o 4º menor elemento

    int result = selectMOM(arr, 0, n - 1, k);

    if (result != -1) {
        printf("O %dº menor elemento é: %d\n", k, result);
    } else {
        printf("Posição inválida!\n");
    }

    return 0;
}

