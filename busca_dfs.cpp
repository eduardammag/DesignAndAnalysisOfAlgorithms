#include <iostream>
#include <stack>
using namespace std;

// Classe Node que representa um nó em uma árvore binária
class Node {
public:
    Node(int key, char data)
        : m_key(key), m_data(data), m_leftNode(nullptr), m_rightNode(nullptr) {}

    Node *leftNode() const { return m_leftNode; }
    void setLeftNode(Node *node) { m_leftNode = node; }

    Node *rightNode() const { return m_rightNode; }
    void setRightNode(Node *node) { m_rightNode = node; }

    int getKey() const { return m_key; }
    char getData() const { return m_data; }

private:
    int m_key;          // Chave do nó
    char m_data;        // Dado armazenado no nó
    Node *m_leftNode;   // Ponteiro para o filho à esquerda
    Node *m_rightNode;  // Ponteiro para o filho à direita
};

// Função de busca em profundidade (DFS) usando uma pilha
void dfs(Node *root, int searchKey) {
    if (root == nullptr) {
        return;
    }

    stack<Node *> s;  // Pilha para armazenar os nós a serem visitados
    s.push(root);

    while (!s.empty()) {
        Node *current = s.top();
        s.pop();

        // Processa o nó atual
        cout << "Visitando nó com chave: " << current->getKey() << " e dado: " << current->getData() << endl;

        // Verifica se encontramos a chave desejada
        if (current->getKey() == searchKey) {
            cout << "Chave " << searchKey << " encontrada!" << endl;
            return;
        }

        // Adiciona os filhos na pilha (primeiro o direito, depois o esquerdo para visitar a esquerda primeiro)
        if (current->rightNode() != nullptr) {
            s.push(current->rightNode());
        }
        if (current->leftNode() != nullptr) {
            s.push(current->leftNode());
        }
    }

    cout << "Chave " << searchKey << " não encontrada." << endl;
}

int main() {
    // Criação dos nós da árvore
    Node *n1 = new Node(1, 'a');
    Node *n2 = new Node(2, 'b');
    Node *n3 = new Node(3, 'c');
    Node *n4 = new Node(4, 'd');
    Node *n5 = new Node(5, 'e');
    Node *n6 = new Node(6, 'f');

    // Construção da árvore
    n1->setLeftNode(n2);
    n1->setRightNode(n3);
    n2->setLeftNode(n4);
    n2->setRightNode(n5);
    n3->setRightNode(n6);

    // Teste de busca DFS
    cout << "Busca em profundidade (DFS):" << endl;
    dfs(n1, 5);  // Procurando o nó com chave 5

    // Liberação da memória
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
