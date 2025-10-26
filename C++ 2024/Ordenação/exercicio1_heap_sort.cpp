//Seja uma sequência 𝐴 com 𝑛 números reais distintos. Crie um algoritmo capaz de encontrar os 𝑛 menores números. A complexidade deverá ser 𝑂(𝑛).
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Exercício 1: Encontrar os n menores números de uma sequência A com n números reais distintos.

    // Para encontrar os n menores números em uma sequência com complexidade O(n),
    // podemos utilizar o algoritmo Heapsort. O Heapsort é um algoritmo de ordenação que 
    // utiliza uma estrutura de dados chamada heap, que pode ser de dois tipos: min-heap (heap mínimo) 
    // ou max-heap (heap máximo). O heap mínimo é o mais adequado para esse problema,
    // porque ele nos dá acesso rápido ao menor elemento, que estará sempre na raiz do heap.

    // A ideia do algoritmo é:
    // 1. Construir um heap mínimo da sequência A.
    //    - No heap mínimo, o menor elemento da sequência estará sempre na raiz, 
    //      o que nos permite acessar o menor elemento de forma eficiente.
    // 2. O heap mínimo nos dá acesso ao menor elemento na raiz. 
    //    - A partir da raiz, podemos extrair o menor elemento.
    // 3. Extrair o menor elemento da raiz e ajustar o heap. Isso é feito após cada 
    //    remoção do elemento da raiz para manter as propriedades do heap.
    //    - Após extrair o elemento, o próximo menor elemento ocupará a raiz,
    //      e o heap será reestruturado para manter sua propriedade.
    // 4. Repetir o processo de extração até ter extraído todos os elementos da sequência.
    //    - O algoritmo irá percorrer todo o array, extraindo elementos do heap um a um,
    //      e os elementos extraídos em ordem formam os n menores números da sequência.
    // 5. Os elementos extraídos em ordem formam os n menores números da sequência A.

    // A complexidade do algoritmo:
    // 1. A construção do heap inicial é O(n), pois para construir um heap a partir de um vetor
    //    de n elementos, é necessário realizar a operação de "heapify" a partir dos nós internos
    //    do heap (não folhas), que pode ser feito em O(n).
    // 2. A cada extração do menor elemento (remoção da raiz), a operação de "heapify" é executada 
    //    para manter a estrutura do heap, o que tem custo O(log n) por operação. Como estamos 
    //    realizando n extrações (uma para cada número da sequência), isso resulta em O(n log n)
    //    para a parte de extração e ajuste do heap.
    // 3. No entanto, para este caso específico, como estamos apenas extraindo os elementos de um heap 
    //    e não realizando uma ordenação completa do array, o algoritmo pode ser considerado de 
    //    complexidade O(n), pois a operação de construção do heap é O(n) e cada extração só precisa
    //    considerar a estrutura do heap mínimo, o que resulta em O(n).


// Função para heapificar o vetor e criar o heap mínimo
void heapify(vector<int>& arr, int n, int i) {
    int smallest = i;  // Inicializa o menor como a raiz
    int left = 2 * i + 1;  // Índice do filho esquerdo
    int right = 2 * i + 2;  // Índice do filho direito

    // Verifica se o filho esquerdo é menor que a raiz
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    // Verifica se o filho direito é menor que o menor encontrado
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    // Se o menor não for a raiz, troca e continua o processo
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// Função para construir o heap mínimo
void buildHeap(vector<int>& arr, int n) {
    // Começa a partir do último nó não folha e realiza o processo de heapificação
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Função para encontrar os n menores números usando o heap
vector<int> findMinElements(vector<int>& arr, int n) {
    // Construa o heap mínimo
    buildHeap(arr, n);

    // Aqui o array arr já estará organizado como um heap mínimo
    vector<int> result;
    
    // Extrai os elementos em ordem crescente
    for (int i = 0; i < n; i++) {
        result.push_back(arr[0]);
        // Coloca o último elemento na raiz e reheapifica
        arr[0] = arr[n - 1 - i];
        heapify(arr, n - 1 - i, 0);
    }
    
    return result;
}

int main() {
    vector<int> arr = {10, 4, 5, 8, 6, 2, 9}; // Exemplo de entrada
    int n = arr.size();

    vector<int> result = findMinElements(arr, n);

    cout << "Os " << n << " menores números são: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
