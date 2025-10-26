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

// DFS Pré-ordem (raiz-esquerda-direita)
void printArvoreDFSPreOrdem(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // Imprime a chave do nó atual
    cout << node->key() << " ";
    
    // Recursivamente visita o nó à esquerda
    printArvoreDFSPreOrdem(node->leftNode());
    
    // Recursivamente visita o nó à direita
    printArvoreDFSPreOrdem(node->rightNode());
}

// DFS Em Ordem (esquerda-raiz-direita)
void printArvoreDFSEmOrdem(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // 1. Recursivamente visita o nó à esquerda
    printArvoreDFSEmOrdem(node->leftNode());
    
    // 2. Imprime a chave do nó atual
    cout << node->key() << " ";
    
    // 3. Recursivamente visita o nó à direita
    printArvoreDFSEmOrdem(node->rightNode());
}

// DFS Pós Ordem (esquerda - direita - raiz)
void printArvoreDFSPosOrdem(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // Recursivamente visita o nó à esquerda
    printArvoreDFSPosOrdem(node->leftNode());
    
    // Recursivamente visita o nó à direita
    printArvoreDFSPosOrdem(node->rightNode());
    
    // Imprime a chave do nó atual
    cout << node->key() << " ";
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

    // Imprimindo a árvore em pré-ordem usando DFS
    cout << "Chaves da arvore em DFS pré-ordem: ";
    printArvoreDFSPreOrdem(n1);  // A partir da raiz (n1)
    cout << endl;
    
    // Imprimindo a árvore em ordem usando DFS
    cout << "Chaves da arvore em DFS ordem: ";
    printArvoreDFSEmOrdem(n1);  // A partir da raiz (n1)
    cout << endl;
    
    // Imprimindo a árvore em pós ordem usando DFS
    cout << "Chaves da arvore em DFS pos ordem:";
    printArvoreDFSPosOrdem(n1);  // A partir da raiz (n1)
    cout << endl;

    // Liberando a memória alocada
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
