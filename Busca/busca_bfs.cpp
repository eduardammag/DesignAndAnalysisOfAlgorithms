#include <iostream>
#include <queue>  // Inclui a biblioteca de fila para BFS
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

// Função que imprime a árvore usando BFS (busca em largura) com complexidade ϴ(n²)
void printTreeBFS(Node *root) {
    int depth = nodeHeight(root) + 1;
    for (int i = 0; i < depth; i++) {
        printLevel(root, i + 1);
    }
}

// Função que imprime a árvore usando BFS com uma fila (versão otimizada) com complexidade ϴ(n)
void printTreeBFSWithQueue(Node *root) {
    if (root == NULL) {
        return;
    }
    queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node *node = queue.front();
        cout << node->key() << " ";
        queue.pop();
        if (node->leftNode()) {
            queue.push(node->leftNode());
        }
        if (node->rightNode()) {
            queue.push(node->rightNode());
        }
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

    // Imprimindo a árvore usando BFS (busca em largura)
    cout << "Chaves da árvore em ordem de nível (BFS): ";
    printTreeBFS(n1);  // A partir da raiz (n1)
    cout << endl;

    // Imprimindo a árvore usando BFS com fila (otimizada)
    cout << "Chaves da árvore em ordem de nível (BFS com fila): ";
    printTreeBFSWithQueue(n1);  // A partir da raiz (n1)
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
