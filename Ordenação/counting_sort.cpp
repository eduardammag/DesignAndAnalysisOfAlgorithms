#include <iostream>
using namespace std;

// Função de Counting Sort
void countingSort(int v[], int n, int k) {
    int fs[k + 1];  // Vetor de contagem
    int temp[n];     // Vetor temporário para armazenar a ordenação
    
    // Inicializa o vetor de contagem com 0
    for (int j = 0; j <= k; j++) {
        fs[j] = 0;
    }

    // Conta a frequência dos elementos
    for (int i = 0; i < n; i++) {
        fs[v[i]] += 1;  // Incrementa a contagem do valor encontrado
    }

    // Acumula os valores de fs
    for (int j = 1; j <= k; j++) {
        fs[j] += fs[j - 1];
    }

    // Coloca os elementos na posição correta no vetor temporário
    for (int i = 0; i < n; i++) {
        int j = v[i];
        temp[fs[j] - 1] = v[i];  // Coloca o valor de v[i] na posição adequada
        fs[j]--;
    }

    // Copia os elementos de volta para o vetor original
    for (int i = 0; i < n; i++) {
        v[i] = temp[i];
    }
}

// Função para imprimir o vetor
void printArray(int v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    // Exemplo de vetor a ser ordenado
    int v[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(v) / sizeof(v[0]);
    int k = 8;  // O maior valor do vetor
    
    cout << "Vetor original: ";
    printArray(v, n);
    
    // Chama a função de ordenação
    countingSort(v, n, k);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
