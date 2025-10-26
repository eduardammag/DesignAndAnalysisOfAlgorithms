//Crie um algoritmo capaz de intercalar os elementos de 𝑚 sequências de forma ordenada. 
//As sequências de entrada já estão ordenadas, e o algoritmo deverá apresentar uma complexidade 𝑂(𝑛𝑙𝑜𝑔(𝑚)), sendo 𝑛 o número total de elementos. 
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Exercício 2: Criar um algoritmo capaz de intercalar m sequências de forma ordenada.
    // As sequências de entrada já estão ordenadas, e o algoritmo deve apresentar uma complexidade O(n log m),
    // sendo n o número total de elementos (soma de todos os elementos das m sequências) e m o número de sequências.

    // Para resolver esse problema, a abordagem mais eficiente envolve o uso de uma estrutura de dados chamada heap,
    // mais especificamente um Min-Heap (ou heap mínimo). O Min-Heap nos permite sempre acessar o menor 
    // elemento de forma eficiente. O algoritmo pode ser descrito da seguinte maneira:

    // Algoritmo para intercalar m sequências ordenadas:
    // 1. Inicialize um Min-Heap (ou priority_queue no C++).
    // 2. Insira o primeiro elemento de cada sequência no Min-Heap.
    //    - Para cada sequência, guardamos o elemento e também a sequência de onde ele veio e sua posição dentro dessa sequência.
    // 3. Extraia o menor elemento do Min-Heap. Esse será o menor entre todos os primeiros elementos das m sequências.
    // 4. Após extrair um elemento, insira o próximo elemento da mesma sequência do qual o elemento foi extraído.
    //    - Isso garante que sempre tenhamos o próximo menor elemento da sequência.
    // 5. Repita os passos 3 e 4 até que todos os elementos de todas as sequências sejam extraídos.
    // 6. O resultado será a intercalada dos m arrays, com todos os elementos ordenados.

    // Complexidade do algoritmo:
    // 1. Para cada um dos m arrays, inicializamos o Min-Heap com o primeiro elemento, o que tem custo O(m).
    // 2. A cada extração do Min-Heap, retiramos o menor elemento, o que tem custo O(log m).
    // 3. Como estamos processando todos os n elementos de todas as m sequências, o número total de operações
    //    de extração e inserção no Min-Heap é O(n log m), onde n é o número total de elementos de todas as sequências
    //    e m é o número de sequências.
    // 4. Portanto, a complexidade total do algoritmo é O(n log m).


// Função para intercalar m sequências já ordenadas
vector<int> mergeKSortedSequences(vector<vector<int>>& sequences) {
    // Min-heap para armazenar os elementos e suas origens (índices de sequência e posição)
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> minHeap;

    // Inicializa o heap com o primeiro elemento de cada sequência
    for (int i = 0; i < sequences.size(); i++) {
        if (!sequences[i].empty()) {
            minHeap.push({sequences[i][0], {i, 0}});
        }
    }

    vector<int> mergedResult;
    
    while (!minHeap.empty()) {
        // Extrai o menor elemento do heap
        auto top = minHeap.top();
        minHeap.pop();
        
        int val = top.first;        // Valor extraído
        int seqIndex = top.second.first; // Índice da sequência
        int eleIndex = top.second.second; // Índice do elemento na sequência

        // Adiciona o valor ao resultado final
        mergedResult.push_back(val);

        // Se houver mais elementos na sequência de onde o elemento foi extraído, coloca o próximo no heap
        if (eleIndex + 1 < sequences[seqIndex].size()) {
            minHeap.push({sequences[seqIndex][eleIndex + 1], {seqIndex, eleIndex + 1}});
        }
    }

    return mergedResult;
}

int main() {
    // Exemplo com 3 sequências ordenadas
    vector<vector<int>> sequences = {
        {1, 5, 9},
        {2, 6, 10},
        {3, 7, 11}
    };

    vector<int> result = mergeKSortedSequences(sequences);

    cout << "Sequência intercalada ordenada: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
