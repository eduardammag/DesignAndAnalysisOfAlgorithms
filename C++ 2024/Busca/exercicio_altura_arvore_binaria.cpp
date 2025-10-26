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
};



// Função para calcular a altura de um nó na árvore binária
int nodeHeight(Node *node) {
    // Verifica se o nó é nulo (caso base para árvore vazia ou subárvore vazia)
    if (node == NULL) {
        return -1; // Altura de árvore vazia é -1
    }
    
    // Chama recursivamente para calcular a altura da subárvore esquerda
    int leftHeight = nodeHeight(node->leftNode());

    // Chama recursivamente para calcular a altura da subárvore direita
    int rightHeight = nodeHeight(node->rightNode());

    // Verifica qual subárvore tem maior altura (esquerda ou direita)
    if (leftHeight > rightHeight) {
        // Se a altura da subárvore esquerda é maior, retorna leftHeight + 1 (contando o nó atual)
        return leftHeight + 1;
    } else {
        // Caso contrário, retorna rightHeight + 1 (contando o nó atual)
        return rightHeight + 1;
    }
}

int main() {
    // Criação dos nós da árvore
    Node *n1 = new Node(1, 'a');  // Nó raiz com chave 1 e dado 'a'
    Node *n2 = new Node(2, 'b');  // Nó filho esquerdo de n1 com chave 2 e dado 'b'
    Node *n3 = new Node(3, 'c');  // Nó filho direito de n1 com chave 3 e dado 'c'
    Node *n4 = new Node(4, 'd');  // Nó filho esquerdo de n2 com chave 4 e dado 'd'
    Node *n5 = new Node(5, 'e');  // Nó filho direito de n2 com chave 5 e dado 'e'
    Node *n6 = new Node(6, 'f');  // Nó filho direito de n3 com chave 6 e dado 'f'

    // Construção da árvore
    n1->setLeftNode(n2);  // Define n2 como filho esquerdo de n1
    n1->setRightNode(n3); // Define n3 como filho direito de n1
    n2->setLeftNode(n4);  // Define n4 como filho esquerdo de n2
    n2->setRightNode(n5); // Define n5 como filho direito de n2
    n3->setRightNode(n6); // Define n6 como filho direito de n3

    // Teste: Altura da árvore
    int height = nodeHeight(n1);
    cout << "Altura da arvore binaria: " << height << endl;

    // Liberação da memória
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
