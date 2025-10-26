#include <iostream>
using namespace std;

// Função para trocar dois elementos no vetor
void swapValues(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Função de particionamento para o Quick Sort
int partition(int v[], int p, int r) {
    int pivot = v[r];  // Pivô é o último elemento
    int j = p;  // Índice para a troca
    
    for (int i = p; i < r; i++) {
        // Se o elemento é menor ou igual ao pivô, troque ele
        if (v[i] <= pivot) {
            swapValues(v, i, j);  // Troca os elementos
            j++;
        }
    }
    
    // Coloca o pivô na posição correta
    swapValues(v, j, r);
    return j;
}

// Função de ordenação Quick Sort
void quicksort(int v[], int p, int r) {
    if (p < r) {
        // Particiona o vetor e obtém a posição do pivô
        int j = partition(v, p, r);
        
        // Ordena as duas metades
        quicksort(v, p, j - 1);
        quicksort(v, j + 1, r);
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
    int v[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(v) / sizeof(v[0]);
    
    cout << "Vetor original: ";
    printArray(v, n);
    
    // Chama a função de ordenação
    quicksort(v, 0, n - 1);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
