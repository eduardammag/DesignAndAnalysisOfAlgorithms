#include <iostream>

//Criando uma função que busca um valor 'x' no vetor 'v' de tamanho 'size

/* 

ERRO:No C++, quando você passa um array para uma função, 
ele é tratado como um ponteiro para o primeiro elemento do array, 
e a operação sizeof(v) não vai funcionar como esperado, 
pois retornará o tamanho de um ponteiro, e não o tamanho do array.

int busca(const int v[], int x){
    int size = sizeof(v)/sizeof(v[0]);
    for (int i =0; i<size; i++){
        if (v[i] == x){
            return i;
        }
    }
    return -1;
}

*/


int busca(const int v[], int size, int x){
    for (int i=0; i<size; i++){
        if (v[i]==x){
            return i; //Se x for encontrado, retorna o indice dele
        }
    }
    return -1; 
}

int main() {
    // Definição do array
    int v[] = {1, 2, 3, 4, 5};
    int size = sizeof(v) / sizeof(v[0]);  
    int x = 2;  // Valor que queremos procurar

    // Chama a função de busca
    int result = busca(v, size, x);

    // Verifica o resultado e imprime
    if (result != -1) {
        std::cout << "O valor " << x << " foi encontrado no indice " << result << "." << std::endl;
    } else {
        std::cout << "O valor " << x << " nao foi encontrado." << std::endl;
    }


    return 0;
}
