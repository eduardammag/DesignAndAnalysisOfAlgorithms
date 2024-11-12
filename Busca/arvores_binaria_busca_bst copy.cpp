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



 Exercício: dado um nó 𝑛1
 de uma árvore binária de busca 𝐴 com altura ℎ encontre o 
nó 𝑛2	
cujo índice é o predecessor da sequência ordenada.

 Node * binaryTreeSearchPredecessor(Node * node) {
 if (node == nullptr) {
 return node;
 }
 if (node->leftNode() != nullptr) {
 return binaryTreeSearchMax(node->leftNode());
 }
 Node * parentNode = node->parentNode();
 while (parentNode != nullptr && node == parentNode->leftNode()) {
 node = parentNode;
 parentNode = parentNode->parentNode();
 }
 return parentNode;

  Exercício: dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘 crie um 
novo nó capaz de inserir
 § Solução:
 a chave mantendo as propriedades de BST.

  Node * binaryTreeInsert(Node * root, int key) {
 if (root == nullptr) {
 return new Node(key);
 }
 if (key < root->key()) {
 root->setLeftNode(binaryTreeInsert(root->leftNode(), key));
 } else {
 root->setRightNode(binaryTreeInsert(root->rightNode(), key));
 }
 return root;

 Exercício: dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘 remova
 nó com esta chave mantendo as propriedades de BST.

 Node * binaryTreeDelete(Node * root, int key)
 {
 if (root == nullptr) {
 return root;
 }
 if (key < root->key()) {
 root->setLeftNode(binaryTreeDelete(root->leftNode(), key));
 } else if (key > root->key()) {
 root->setRightNode(binaryTreeDelete(root->rightNode(), key));
 } else {
 root = binaryTreeDeleteNode(root);
 }
 return root;
 }

Node * binaryTreeDeleteNode(Node * root) {
 if (root->leftNode() == nullptr && root->rightNode() == nullptr) {
 delete root;
 root = nullptr;
 } else if (root->leftNode() == nullptr) {
 Node * newRoot = root->rightNode();
 delete root;
 root = newRoot;
 }
 else if (root->rightNode() == nullptr) {
 Node * newRoot = root->leftNode();
 delete root;
 root = newRoot;
 } else {
 Node * newRoot = binaryTreeSearchSuccessor(root->rightNode());
 root->setKey(newRoot->key());
 root->setRightNode(binaryTreeDelete(root->rightNode(), newRoot->key()));
 }
 return root;

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
