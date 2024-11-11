#include <iostream>
using namespace std;

// Classe Node que representa um nó em uma árvore binária
class Node {
public:
    // Construtor que inicializa um nó com uma chave (int) e um dado (char)
    Node(int key, char data)
        : m_key(key), m_data(data), m_leftNode(nullptr), m_rightNode(nullptr), m_parentNode(nullptr) {}

    // Função que retorna o ponteiro para o nó à esquerda
    Node *leftNode() const { return m_leftNode; }

    // Função que define o nó à esquerda
    void setLeftNode(Node *node) { m_leftNode = node; }

    // Função que retorna o ponteiro para o nó à direita
    Node *rightNode() const { return m_rightNode; }

    // Função que define o nó à direita
    void setRightNode(Node *node) { m_rightNode = node; }

    // Função que retorna o dado armazenado no nó
    char getData() const { return m_data; }

private:
    int m_key;          // Chave do nó
    char m_data;        // Dado armazenado no nó
    Node *m_leftNode;   // Ponteiro para o filho à esquerda
    Node *m_rightNode;  // Ponteiro para o filho à direita
    Node *m_parentNode; // Ponteiro para o nó pai (não utilizado aqui)
};

// Função de travessia em ordem (in-order traversal)
void inorderTraversal(Node *node) {
    if (node != nullptr) {
        inorderTraversal(node->leftNode()); // Percorre a subárvore esquerda
        cout << node->getData() << " ";     // Imprime o dado do nó atual
        inorderTraversal(node->rightNode()); // Percorre a subárvore direita
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

    // Define a raiz da árvore
    Node *rootNode = n1;

    // Teste: Travessia em ordem (In-Order Traversal)
    cout << "Travessia em ordem (in-order traversal) da árvore binária: ";
    inorderTraversal(rootNode);
    cout << endl;

    // Liberação da memória
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}

