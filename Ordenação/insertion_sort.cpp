#include <iostream>
using namespace std;

void insertionSort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int currentValue = v[i];  // Armazena o valor atual
        int j = i - 1;
        
        // Move os elementos do vetor que são maiores que o currentValue para uma posição à frente
        while (j >= 0 && v[j] > currentValue) {
            v[j + 1] = v[j];
            j--;
        }
        
        // Insere o currentValue na posição correta
        v[j + 1] = currentValue;
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
    int v[] = {12, 11, 13, 5, 6};
    int n = sizeof(v) / sizeof(v[0]);
    
    cout << "Vetor original: ";
    printArray(v, n);
    
    // Chama a função de ordenação
    insertionSort(v, n);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
