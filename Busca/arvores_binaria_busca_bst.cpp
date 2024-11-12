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


// Problema: dada uma árvore binária de busca 𝐴 com altura ℎ, encontre o nó cuja chave seja 𝑘.

// Solução recursiva:
Node * binaryTreeSearchRecursive(Node * node, int key) {
    // Caso base: se o nó for nulo ou se a chave do nó for igual à chave buscada, retorna o nó
    if (node == NULL || node->key() == key) {
        return node;
    }
    // Se a chave buscada for menor que a chave do nó, a busca continua no filho à esquerda
    if (node->key() > key) {
        return binaryTreeSearchRecursive(node->leftNode(), key);
    } else {
        // Caso contrário, a busca continua no filho à direita
        return binaryTreeSearchRecursive(node->rightNode(), key);
    }
}

// Complexidade: ϴ(h), onde h é a altura da árvore (tempo proporcional à altura)

// Solução iterativa:
Node * binaryTreeSearchIterative(Node * node, int key) {
    // Enquanto o nó não for nulo e a chave do nó não for a chave buscada, continua a busca
    while (node != NULL && node->key() != key) {
        // Se a chave buscada for menor que a chave do nó, busca no filho à esquerda
        if (node->key() > key) {
            node = node->leftNode();
        } else {
            // Caso contrário, busca no filho à direita
            node = node->rightNode();
        }
    }
    // Retorna o nó encontrado ou NULL caso não encontre a chave
    return node;
}

// Complexidade: ϴ(h), onde h é a altura da árvore (tempo proporcional à altura)


// Exercício: dada uma árvore binária de busca 𝐴 com altura ℎ, encontre o índice do nó com índice mínimo.

// Solução:
Node * binaryTreeSearchMin(Node * node) {
    // Se o nó for nulo, retorna nulo
    if (node == NULL) {
        return node;
    }
    // Percorre à esquerda até encontrar o nó mais à esquerda, que possui o menor valor
    while (node->leftNode() != NULL) {
        node = node->leftNode();
    }
    // Retorna o nó com o valor mínimo
    return node;
}

// Complexidade: ϴ(h), onde h é a altura da árvore (tempo proporcional à altura)


// Exercício: dada uma árvore binária de busca 𝐴 com altura ℎ, encontre o índice do nó com índice máximo.

// Solução:
Node * binaryTreeSearchMax(Node * node) {
    // Se o nó for nulo, retorna nulo
    if (node == NULL) {
        return node;
    }
    // Percorre à direita até encontrar o nó mais à direita, que possui o maior valor
    while (node->rightNode() != NULL) {
        node = node->rightNode();
    }
    // Retorna o nó com o valor máximo
    return node;
}

// Complexidade: ϴ(h), onde h é a altura da árvore (tempo proporcional à altura)


// Exercício: dado um nó 𝑛1 de uma árvore binária de busca 𝐴 com altura ℎ, encontre o nó 𝑛2 cujo índice é o sucessor na sequência ordenada.

// Solução:
Node* binaryTreeSearchSuccessor(Node *node) {
    if (node == NULL) {
        return NULL;
    }

    // Caso o nó tenha um filho à direita, o sucessor é o nó mais à esquerda da subárvore direita
    if (node->rightNode() != NULL) {
        return binaryTreeSearchMin(node->rightNode());
    }

    // Caso contrário, subimos até encontrar um nó que é filho esquerdo de seu pai
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->rightNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }

    return parentNode;
}


int main() {
    // Criando nós da árvore
    Node *n1 = new Node(1, 'a');
    Node *n2 = new Node(2, 'b');
    Node *n3 = new Node(3, 'c');
    Node *n4 = new Node(4, 'd');
    Node *n5 = new Node(5, 'e');
    Node *n6 = new Node(6, 'f');

    // Construindo a árvore
    n1->setLeftNode(n2);  // n1 (raiz) tem n2 como filho esquerdo
    n1->setRightNode(n3); // n1 (raiz) tem n3 como filho direito
    n2->setLeftNode(n4);  // n2 tem n4 como filho esquerdo
    n2->setRightNode(n5); // n2 tem n5 como filho direito
    n3->setRightNode(n6); // n3 tem n6 como filho direito

    // Define a raiz da árvore
    Node *root = n1;


    // Testando a busca recursiva
    Node* result = binaryTreeSearchRecursive(n1, 4);
    if (result != NULL) {
        cout << "Encontrado (Recursivo): " << result->key() << endl;
    } else {
        cout << "Nao encontrado (Recursivo)" << endl;
    }

    // Testando a busca iterativa
    result = binaryTreeSearchIterative(n1, 6);
    if (result != NULL) {
        cout << "Encontrado (Iterativo): " << result->key() << endl;
    } else {
        cout << "Nao encontrado (Iterativo)" << endl;
    }

    // Testando a busca pelo nó mínimo
    result = binaryTreeSearchMin(n1);
    if (result != NULL) {
        cout << "Minimo: " << result->key() << endl;
    }

    // Testando a busca pelo nó máximo
    result = binaryTreeSearchMax(n1);
    if (result != NULL) {
        cout << "Maximo: " << result->key() << endl;
    }

    // Testando a busca pelo sucessor
    Node* successor = binaryTreeSearchSuccessor(result);
    if (successor != NULL) {
        cout << "Sucessor de " << result->key() << ": " << successor->key() << endl;
    } else {
        cout << "Nao tem sucessor" << endl;
    }




    // Liberando a memória alocada
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
