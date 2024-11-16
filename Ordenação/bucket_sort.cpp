#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Função de Insertion Sort (usada para ordenar dentro dos baldes)
void insertionSort(vector<float>& b) {
    int n = b.size();
    for (int i = 1; i < n; i++) {
        float currentValue = b[i];
        int j = i - 1;
        while (j >= 0 && b[j] > currentValue) {
            b[j + 1] = b[j];
            j--;
        }
        b[j + 1] = currentValue;
    }
}

// Função de Bucket Sort
void bucketSort(float v[], int n) {
    // Criar n baldes
    vector<float> b[n];

    // Coloca os elementos nos baldes
    for (int i = 0; i < n; i++) {
        int inx = n * v[i];  // Encontra o índice do balde baseado no valor de v[i]
        b[inx].push_back(v[i]);
    }

    // Ordena cada balde utilizando o Insertion Sort
    for (int i = 0; i < n; i++) {
        insertionSort(b[i]);
    }

    // Coloca os elementos de volta no vetor original
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            v[index++] = b[i][j];
        }
    }
}

// Função para imprimir o vetor
void printArray(float v[], int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    // Exemplo de vetor de números flutuantes
    float v[] = {0.42, 0.32, 0.65, 0.12, 0.53, 0.22, 0.42};
    int n = sizeof(v) / sizeof(v[0]);

    cout << "Vetor original: ";
    printArray(v, n);

    // Chama a função de ordenação
    bucketSort(v, n);

    cout << "Vetor ordenado: ";
    printArray(v, n);

    return 0;
}
