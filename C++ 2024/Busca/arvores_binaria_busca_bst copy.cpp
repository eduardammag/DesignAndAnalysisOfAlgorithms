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



// Exercício 1: Dado um nó 𝑛1 de uma árvore binária de busca 𝐴 com altura ℎ, encontre o nó 𝑛2 cujo índice é o predecessor na sequência ordenada.
Node *binaryTreeSearchPredecessor(Node *node) {
    // Caso base: se o nó for nulo, retorna nulo
    if (node == nullptr) {
        return node;
    }

    // Se o nó tem um filho à esquerda, o predecessor será o nó com o maior valor na subárvore esquerda
    if (node->leftNode() != nullptr) {
        return binaryTreeSearchMax(node->leftNode());
    }

    // Caso contrário, o predecessor é o nó pai, mas apenas se o nó atual for o filho direito do pai
    Node *parentNode = node->parentNode();
    while (parentNode != nullptr && node == parentNode->leftNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }

    // Retorna o nó pai (predecessor na sequência ordenada)
    return parentNode;
}

// Função auxiliar para encontrar o nó com o maior valor na subárvore esquerda
Node *binaryTreeSearchMax(Node *node) {
    while (node != nullptr && node->rightNode() != nullptr) {
        node = node->rightNode();
    }
    return node;
}


// Exercício 2: Dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘, crie um novo nó capaz de inserir a chave mantendo as propriedades de BST.
Node *binaryTreeInsert(Node *root, int key) {
    // Caso base: se a árvore estiver vazia, cria um novo nó e retorna
    if (root == nullptr) {
        return new Node(key, ' ');  // ' ' é um valor genérico para o dado, pode ser alterado conforme necessário
    }

    // Se a chave for menor que a chave do nó, a inserção vai para a subárvore esquerda
    if (key < root->key()) {
        root->setLeftNode(binaryTreeInsert(root->leftNode(), key));
    } else {
        // Caso contrário, a inserção vai para a subárvore direita
        root->setRightNode(binaryTreeInsert(root->rightNode(), key));
    }

    return root;
}

// Exercício 3: Dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘, remova o nó com esta chave mantendo as propriedades de BST.
Node *binaryTreeDelete(Node *root, int key) {
    // Caso base: se o nó for nulo, retorna nulo
    if (root == nullptr) {
        return root;
    }

    // Se a chave buscada for menor que a chave do nó, a remoção acontece na subárvore esquerda
    if (key < root->key()) {
        root->setLeftNode(binaryTreeDelete(root->leftNode(), key));
    } else if (key > root->key()) {
        // Se a chave buscada for maior que a chave do nó, a remoção acontece na subárvore direita
        root->setRightNode(binaryTreeDelete(root->rightNode(), key));
    } else {
        // Caso o nó a ser removido tenha sido encontrado
        root = binaryTreeDeleteNode(root);
    }

    return root;
}

// Função para remover um nó específico, mantendo as propriedades da árvore binária de busca
Node *binaryTreeDeleteNode(Node *root) {
    // Caso 1: O nó não tem filhos (é uma folha), simplesmente apaga o nó
    if (root->leftNode() == nullptr && root->rightNode() == nullptr) {
        delete root;
        root = nullptr;
    }
    // Caso 2: O nó tem apenas o filho à direita
    else if (root->leftNode() == nullptr) {
        Node *newRoot = root->rightNode();
        delete root;
        root = newRoot;
    }
    // Caso 3: O nó tem apenas o filho à esquerda
    else if (root->rightNode() == nullptr) {
        Node *newRoot = root->leftNode();
        delete root;
        root = newRoot;
    }
    // Caso 4: O nó tem ambos os filhos (esquerdo e direito)
    else {
        // Encontra o sucessor (menor valor da subárvore direita) e substitui a chave do nó
        Node *newRoot = binaryTreeSearchSuccessor(root->rightNode());
        root->setKey(newRoot->key());
        // Remove o nó sucessor da subárvore direita
        root->setRightNode(binaryTreeDelete(root->rightNode(), newRoot->key()));
    }
    return root;
}

// Função auxiliar para encontrar o sucessor de um nó
Node *binaryTreeSearchSuccessor(Node *node) {
    // Se o nó tem um filho à direita, o sucessor é o nó com o menor valor na subárvore direita
    if (node->rightNode() != nullptr) {
        return binaryTreeSearchMin(node->rightNode());
    }

    // Caso contrário, o sucessor é o nó pai, mas apenas se o nó atual for o filho esquerdo do pai
    Node *parentNode = node->parentNode();
    while (parentNode != nullptr && node == parentNode->rightNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }

    return parentNode;
}

// Função auxiliar para encontrar o nó com o menor valor na subárvore esquerda
Node *binaryTreeSearchMin(Node *node) {
    while (node != nullptr && node->leftNode() != nullptr) {
        node = node->leftNode();
    }
    return node;
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


    // Liberando a memória alocada
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
