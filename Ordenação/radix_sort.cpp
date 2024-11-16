#include <iostream>
using namespace std;

// Função de Radix Sort
void radixSort(unsigned char* v[], int n, int W, int K) {
    int fp[K + 1];  // Vetor de contagem para cada possível valor de byte
    unsigned char* aux[n];  // Vetor auxiliar para armazenar a ordenação temporária
    
    // Processa cada byte da palavra (de W-1 até 0)
    for (int w = W - 1; w >= 0; w--) {
        // Inicializa o vetor de contagem
        for (int j = 0; j <= K; j++) {
            fp[j] = 0;
        }
        
        // Conta a frequência de cada valor de byte em v[i][w]
        for (int i = 0; i < n; i++) {
            fp[v[i][w] + 1] += 1;
        }
        
        // Acumula as frequências
        for (int j = 1; j <= K; j++) {
            fp[j] += fp[j - 1];
        }
        
        // Preenche o vetor auxiliar (aux) com os valores ordenados por esse byte
        for (int i = 0; i < n; i++) {
            int j = v[i][w];
            aux[fp[j]] = v[i];
            fp[j]++;
        }
        
        // Copia os elementos ordenados de volta para o vetor original
        for (int i = 0; i < n; i++) {
            v[i] = aux[i];
        }
    }
}

// Função para imprimir o vetor de ponteiros
void printArray(unsigned char* v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "[" << (int)v[i][0] << ", " << (int)v[i][1] << "] ";
    }
    cout << endl;
}

int main() {
    // Exemplo de vetor de ponteiros para 'unsigned char'
    unsigned char arr1[] = {12, 5};
    unsigned char arr2[] = {3, 9};
    unsigned char arr3[] = {2, 8};
    unsigned char arr4[] = {6, 7};
    
    unsigned char* v[] = {arr1, arr2, arr3, arr4};  // Vetor de ponteiros
    int n = 4;  // Número de elementos no vetor
    int W = 2;  // Número de bytes por elemento
    int K = 9;  // Valor máximo de cada byte (0-9)

    cout << "Vetor original: ";
    printArray(v, n);

    // Chama a função de ordenação
    radixSort(v, n, W, K);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
