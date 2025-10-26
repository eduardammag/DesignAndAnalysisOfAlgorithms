#include <iostream>
using namespace std;

// Definição da classe Node que representa um nó em uma árvore binária
class Node {

private:
    int m_key;              // Chave única do nó (geralmente usada para ordenação ou identificação)
    char m_data;            // Dado armazenado no nó (pode ser qualquer tipo, aqui é um char)
    Node *m_leftNode;       // Ponteiro para o nó à esquerda (filho esquerdo)
    Node *m_rightNode;      // Ponteiro para o nó à direita (filho direito)
    Node *m_parentNode;     // Ponteiro para o nó pai    

public:
    // Construtor da classe Node, inicializa os membros com os valores fornecidos
    Node(int key, char data) : 
        m_key(key),                // Inicializa a chave do nó com o valor passado (key)
        m_data(data),              // Inicializa o dado armazenado no nó com o valor passado (data)
        m_leftNode(NULL),          // Inicializa o ponteiro para o filho esquerdo como NULL
        m_rightNode(NULL),         // Inicializa o ponteiro para o filho direito como NULL
        m_parentNode(NULL) {}      // Inicializa o ponteiro para o nó pai como NULL
    
    // Função que retorna o ponteiro para o nó à esquerda
    Node *leftNode() const{ 
        return m_leftNode; 
        } 

    // Função que retorna o ponteiro para o nó à direita
    Node *rightNode() const{
        return m_rightNode; 
        }     
    
    // Função que retorna o ponteiro para o nó pai
    Node *parentNode() const{
        return m_parentNode; 
        }
   
    // Função que define o nó à esquerda 
    void setLeftNode(Node *node) {
        m_leftNode = node;        
    }
    
    // Função que define o nó à direita 
    void setRightNode(Node *node) {
        m_rightNode = node;       
    }
      
    // Função que define o nó pai
    void setParentNode(Node *node){ 
        m_parentNode = node; 
        }

    // Função que retorna a chave do nó
    int key() const {
        return m_key;
    }
};

//Dada uma árvore binária de busca 𝐴 com altura ℎ encontre o índice do nó com índice mínimo
Node *BuscaIndiceMin(Node *node) {
    // Se a árvore está vazia (nó nulo), retorna NULL
    if (node == NULL) {
        return node;
    }
    // Caminha para o nó mais à esquerda da árvore
    while (node->leftNode() != NULL) {
        node = node->leftNode();
    }
    // Retorna o nó com a chave mínima
    return node;
}

//Dada uma árvore binária de busca 𝐴 com altura ℎ encontre o índice do nó com índice máximo
Node *BuscaIndiceMax(Node *node) {
    // Se a árvore está vazia (nó nulo), retorna NULL
    if (node == NULL) {
        return node;
    }
    // Caminha para o nó mais à direita da árvore
    while (node->rightNode() != NULL) {
        node = node->rightNode();
    }
    // Retorna o nó com a chave máxima
    return node;
}


//Dado um nó 𝑛1  de uma árvore binária de busca 𝐴 com altura ℎ encontre o nó 𝑛2	cujo índice é o sucessor da sequência ordenada.

// Função que encontra o sucessor de um nó em uma árvore binária de busca (BST)
Node *ArvoreBuscaSucessor(Node *node) {
    if (node == NULL) {
        return node;
    }
    // Se o nó tem filho à direita, o sucessor é o nó com a chave mínima na subárvore direita
    if (node->rightNode() != NULL) {
        return BuscaIndiceMin(node->rightNode());
    }
    // Caso contrário, precisamos subir pela árvore até encontrar um nó que seja filho esquerdo de seu pai
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->rightNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }
    // Retorna o sucessor (ou NULL se não houver sucessor)
    return parentNode;
}

//Dado um nó 𝑛1  de uma árvore binária de busca 𝐴 com altura ℎ encontre o nó 𝑛2 cujo índice é o predecessor da sequência ordenada.
Node *ArvoreBuscaPredecessor(Node *node) {
    // Se o nó for nulo, retorna NULL (caso base)
    if (node == NULL) {
        return node;
    }
    // Se o nó tem filho à esquerda, o predecessor é o nó com a chave máxima na subárvore esquerda
    if (node->leftNode() != NULL) {
        return BuscaIndiceMax(node->leftNode());
    }
    // Caso contrário, precisamos subir pela árvore até encontrar um nó que seja filho direito de seu pai
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->leftNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }
    // Retorna o predecessor (ou NULL se não houver predecessor)
    return parentNode;
}


int main() {
    // Criando nós da árvore
    Node *n8 = new Node(8, 'h');   // Raiz
    Node *n3 = new Node(3, 'c');   
    Node *n10 = new Node(10, 'j');
    Node *n1 = new Node(1, 'a');
    Node *n6 = new Node(6, 'f');
    Node *n14 = new Node(14, 'n');
    Node *n4 = new Node(4, 'd');
    Node *n7 = new Node(7, 'g');
    Node *n13 = new Node(13, 'm');

    // Construindo a árvore binária de busca
    n8->setLeftNode(n3);  
    n8->setRightNode(n10);
    n3->setLeftNode(n1);  
    n3->setRightNode(n6);
    n6->setLeftNode(n4);  
    n6->setRightNode(n7); 
    n10->setRightNode(n14);
    n14->setLeftNode(n13);

    // Testando a função que encontra o nó com a chave mínima
    Node *minNode = BuscaIndiceMin(n8);
    if (minNode != NULL) {
        cout << "No com a chave minima: " << minNode->key() << endl;
    } else {
        cout << "Arvore esta vazia!" << endl;
    }

    // Testando a função que encontra o nó com a chave máxima
    Node *maxNode = BuscaIndiceMax(n8);
    if (maxNode != NULL) {
        cout << "No com a chave maxima: " << maxNode->key() << endl;
    } else {
        cout << "Arvore esta vazia!" << endl;
    }

    // Testando a busca pelo sucessor
    Node *sucessor = ArvoreBuscaSucessor(n6); // Sucessor de 6
    if (sucessor != NULL) {
        cout << "Sucessor de " << n6->key() << ": " << sucessor->key() << endl;
    } else {
        cout << "Sucessor de " << n6->key() << " nao encontrado!" << endl;
    }

    // Testando a busca pelo predecessor
    Node *predecessor = ArvoreBuscaPredecessor(n6); // Predecessor de 6
    if (predecessor != NULL) {
        cout << "Predecessor de " << n6->key() << ": " << predecessor->key() << endl;
    } else {
        cout << "Predecessor de " << n6->key() << " nao encontrado!" << endl;
    }

    // Liberando a memória alocada
    delete n8;
    delete n3;
    delete n10;
    delete n1;
    delete n6;
    delete n14;
    delete n4;
    delete n7;
    delete n13;

    return 0;
}
