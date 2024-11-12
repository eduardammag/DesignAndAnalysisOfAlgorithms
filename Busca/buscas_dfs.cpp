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
void printTreeDFSPreorder(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // 1. Imprime a chave do nó atual
    cout << node->key() << " ";
    
    // 2. Recursivamente visita o nó à esquerda
    printTreeDFSPreorder(node->leftNode());
    
    // 3. Recursivamente visita o nó à direita
    printTreeDFSPreorder(node->rightNode());
}

// Função que imprime a árvore em ordem "inorder" usando DFS (em ordem)
void printTreeDFSInorder(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // 1. Recursivamente visita o nó à esquerda
    printTreeDFSInorder(node->leftNode());
    
    // 2. Imprime a chave do nó atual
    cout << node->key() << " ";
    
    // 3. Recursivamente visita o nó à direita
    printTreeDFSInorder(node->rightNode());
}

// Função que imprime a árvore em ordem "postorder" usando DFS (pós-ordem)
void printTreeDFSPostorder(Node *node) {
    // Caso base: se o nó atual é nulo, não há nada para fazer, então retorna
    if (node == NULL) {
        return;
    }
    
    // 1. Recursivamente visita o nó à esquerda
    printTreeDFSPostorder(node->leftNode());
    
    // 2. Recursivamente visita o nó à direita
    printTreeDFSPostorder(node->rightNode());
    
    // 3. Imprime a chave do nó atual
    cout << node->key() << " ";
}

// Função auxiliar para calcular a altura de um nó
int nodeHeight(Node *node) {
    if (node == NULL) {
        return -1;
    }
    int leftHeight = nodeHeight(node->leftNode());
    int rightHeight = nodeHeight(node->rightNode());
    return max(leftHeight, rightHeight) + 1;
}

// Função que imprime um nível específico da árvore (para BFS)
void printLevel(Node *node, int level) {
    if (node == NULL) {
        return;
    }
    if (level == 1) {
        cout << node->key() << " ";
    } else if (level > 1) {
        printLevel(node->leftNode(), level - 1);
        printLevel(node->rightNode(), level - 1);
    }

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

    // Imprimindo a árvore em ordem "inorder" usando DFS
    cout << "Chaves da arvore em ordem (DFS inorder): ";
    printTreeDFSInorder(n1);  // A partir da raiz (n1)
    cout << endl;

    // Imprimindo a árvore em ordem "postorder" usando DFS
    cout << "Chaves da arvore em pos-ordem (DFS postorder): ";
    printTreeDFSPostorder(n1);  // A partir da raiz (n1)
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
