#include <iostream>
using namespace std;

// Função de bubble sort para um vetor
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Últimos i elementos já estão ordenados
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Troca os elementos adjacentes se estiverem na ordem errada
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para imprimir o vetor
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Função principal
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Array antes do Bubble Sort: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "Array depois do Bubble Sort: ";
    printArray(arr, n);

    return 0;
}
