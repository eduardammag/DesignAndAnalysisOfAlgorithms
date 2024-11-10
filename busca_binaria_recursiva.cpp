#include <iostream>

// Função de busca binária recursiva
int buscaRecursiva(int vetor[], int indiceEsquerdo, int indiceDireito, int valor) {
    int indiceMeio = (indiceEsquerdo + indiceDireito) / 2;
    int valorMeio = vetor[indiceMeio];

    if (valorMeio == valor) {
        return indiceMeio;  // Valor encontrado
    }

    if (indiceEsquerdo >= indiceDireito) {
        return -1;  // Caso base: valor não encontrado
    }

    if (valor > valorMeio) {
        return buscaRecursiva(vetor, indiceMeio + 1, indiceDireito, valor);
    } else {
        return buscaRecursiva(vetor, indiceEsquerdo, indiceMeio - 1, valor);
    }
}

int main() {
    
    
    // Definição de um vetor ordenado
    int vetor[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int valorProcurado = 7;

    // Uso da função recursiva
    int resultadoRecursivo = buscaRecursiva(vetor, 0, tamanho - 1, valorProcurado);

    // Exibição dos resultados
    if (resultadoRecursivo != -1) {
        std::cout << "Recursiva: Valor " << valorProcurado << " encontrado no índice " << resultadoRecursivo << std::endl;
    } else {
        std::cout << "Recursiva: Valor " << valorProcurado << " não encontrado" << std::endl;
    }

   

    return 0;
}
