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
 






//Dada uma árvore binária de busca 𝐴 com altura ℎ encontre o índice do nó com índice máximo
 


 

int main() {
    // Criando nós da árvore (com uma estrutura de árvore binária de busca)
    Node *n8 = new Node(8, 'h');   // Raiz
    Node *n3 = new Node(3, 'c');   
    Node *n10 = new Node(10, 'j');
    Node *n1 = new Node(1, 'a');
    Node *n6 = new Node(6, 'f');
    Node *n14 = new Node(14, 'n');
    Node *n4 = new Node(4, 'd');
    Node *n7 = new Node(7, 'g');
    Node *n13 = new Node(13, 'm');

    // Construindo a árvore binária de busca corretamente
    n8->setLeftNode(n3);  // n8 (raiz) tem n3 como filho esquerdo
    n8->setRightNode(n10); // n8 tem n10 como filho direito
    n3->setLeftNode(n1);  // n3 tem n1 como filho esquerdo
    n3->setRightNode(n6); // n3 tem n6 como filho direito
    n6->setLeftNode(n4);  // n6 tem n4 como filho esquerdo
    n6->setRightNode(n7); // n6 tem n7 como filho direito
    n10->setRightNode(n14); // n10 tem n14 como filho direito
    n14->setLeftNode(n13);  // n14 tem n13 como filho esquerdo


    

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

