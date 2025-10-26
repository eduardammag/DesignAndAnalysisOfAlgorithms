//C++ - Inserção Ordenação Crescente

#include <iostream>
using namespace std;

void insertionSortAsc(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


void insertionSortDesc(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Retorna o índice onde o elemento foi encontrado
        }
    }
    return -1;  // Retorna -1 se o elemento não for encontrado
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSortAsc(arr, n);
    cout << "Array ordenado em ordem crescente: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;









    

    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSortDesc(arr, n);
    cout << "Array ordenado em ordem decrescente: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;









int arr[] = {10, 23, 45, 70, 11, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 45;

    int result = linearSearch(arr, n, target);
    if (result != -1) {
        cout << "Elemento " << target << " encontrado no índice " << result << endl;
    } else {
        cout << "Elemento " << target << " não encontrado no array" << endl;
    }

    return 0;
}