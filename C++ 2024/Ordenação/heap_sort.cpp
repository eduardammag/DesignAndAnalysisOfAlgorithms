#include <iostream>
using namespace std;

// Função para trocar dois elementos no vetor
void swapValues(int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// Função para ajustar a estrutura do heap (heapify)
void heapify(int v[], int n, int i) {
    int inx = i;
    int leftInx = 2 * i + 1;   // Índice do filho esquerdo
    int rightInx = 2 * i + 2;  // Índice do filho direito
    
    // Se o filho esquerdo for maior que o nó atual
    if (leftInx < n && v[leftInx] > v[inx]) {
        inx = leftInx;
    }
    
    // Se o filho direito for maior que o nó atual
    if (rightInx < n && v[rightInx] > v[inx]) {
        inx = rightInx;
    }
    
    // Se a troca for necessária
    if (inx != i) {
        swapValues(v, i, inx);  // Troca o valor do nó atual com o maior filho
        heapify(v, n, inx);      // Chama recursivamente para o sub-heap afetado
    }
}

// Função para construir o heap (rearranjar o vetor)
void buildHeap(int v[], int n) {
    // Começa do último nó não folha e aplica heapify para todo o vetor
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i);
    }
}

// Função para ordenar o vetor utilizando Heap Sort
void heapSort(int v[], int n) {
    buildHeap(v, n);  // Constrói o heap
    
    // Extrai os elementos do heap e ajusta a estrutura
    for (int i = n - 1; i > 0; i--) {
        swapValues(v, 0, i);     // Troca o maior elemento (raiz) com o último elemento
        heapify(v, i, 0);        // Aplica heapify para a nova raiz do heap
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
    heapSort(v, n);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
