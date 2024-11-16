#include <iostream>
using namespace std;

// Função de mesclagem de dois subvetores
void merge(int v[], int startA, int startB, int endB) {
    int r[endB - startA];  // Vetor auxiliar para armazenar os elementos ordenados
    int aInx = startA;
    int bInx = startB;
    int rInx = 0;
    
    // Mescla os dois subvetores enquanto houver elementos em ambos
    while (aInx < startB && bInx < endB) {
        r[rInx++] = (v[aInx] <= v[bInx]) ? v[aInx++] : v[bInx++];
    }
    
    // Adiciona os elementos restantes de A, caso haja
    while (aInx < startB) { r[rInx++] = v[aInx++]; }
    
    // Adiciona os elementos restantes de B, caso haja
    while (bInx < endB) { r[rInx++] = v[bInx++]; }
    
    // Copia os elementos do vetor auxiliar de volta para o vetor original
    for (aInx = startA; aInx < endB; ++aInx) { 
        v[aInx] = r[aInx - startA]; 
    }
}

// Função de ordenação Merge Sort
void mergeSort(int v[], int startInx, int endInx) {
    if (startInx < endInx - 1) {
        int midInx = (startInx + endInx) / 2;
        
        // Divide o vetor em duas metades e ordena cada uma recursivamente
        mergeSort(v, startInx, midInx);
        mergeSort(v, midInx, endInx);
        
        // Mescla as duas metades ordenadas
        merge(v, startInx, midInx, endInx);
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
    mergeSort(v, 0, n);
    
    cout << "Vetor ordenado: ";
    printArray(v, n);
    
    return 0;
}
