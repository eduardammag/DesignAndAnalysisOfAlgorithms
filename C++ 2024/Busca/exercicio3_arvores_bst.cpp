#include <iostream>
using namespace std;

// Definição da classe Node que representa um nó em uma árvore binária
class Node {
private:
    int m_key;
    char m_data;
    Node *m_leftNode;
    Node *m_rightNode;
    Node *m_parentNode;

public:
    Node(int key, char data) : m_key(key), m_data(data), m_leftNode(NULL), m_rightNode(NULL), m_parentNode(NULL) {}

    Node *leftNode() const { return m_leftNode; }
    Node *rightNode() const { return m_rightNode; }
    Node *parentNode() const { return m_parentNode; }

    void setLeftNode(Node *node) { m_leftNode = node; }
    void setRightNode(Node *node) { m_rightNode = node; }
    void setParentNode(Node *node) { m_parentNode = node; }
    void setKey(int newKey) { m_key = newKey; }

    int key() const { return m_key; }
    char data() const { return m_data; }
};

// Função que deleta o nó
Node *binaryTreeDeleteNode(Node *root);

Node *BuscaIndiceMin(Node *node) {
    if (node == NULL) return node;
    while (node->leftNode() != NULL) {
        node = node->leftNode();
    }
    return node;
}

Node * binaryTreeInsert(Node * root, int key, char data) {
    if (root == NULL) {
        return new Node(key, data);
    }
    if (key < root->key()) {
        root->setLeftNode(binaryTreeInsert(root->leftNode(), key, data));
    } else {
        root->setRightNode(binaryTreeInsert(root->rightNode(), key, data));
    }
    return root;
}

Node * binaryTreeDelete(Node * root, int key) {
    if (root == NULL) {
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
    if (root->leftNode() == NULL && root->rightNode() == NULL) {
        delete root;
        return NULL;
    } else if (root->leftNode() == NULL) {
        Node * newRoot = root->rightNode();
        delete root;
        return newRoot;
    } else if (root->rightNode() == NULL) {
        Node * newRoot = root->leftNode();
        delete root;
        return newRoot;
    } else {
        Node * successor = BuscaIndiceMin(root->rightNode());
        root->setKey(successor->key());
        root->setRightNode(binaryTreeDelete(root->rightNode(), successor->key()));
    }
    return root;
}

Node *BuscaIndiceMax(Node *node) {
    if (node == NULL) return node;
    while (node->rightNode() != NULL) {
        node = node->rightNode();
    }
    return node;
}

Node *ArvoreBuscaSucessor(Node *node) {
    if (node == NULL) return node;
    if (node->rightNode() != NULL) {
        return BuscaIndiceMin(node->rightNode());
    }
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->rightNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }
    return parentNode;
}

Node *ArvoreBuscaPredecessor(Node *node) {
    if (node == NULL) return node;
    if (node->leftNode() != NULL) {
        return BuscaIndiceMax(node->leftNode());
    }
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->leftNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }
    return parentNode;
}

void imprimirArvore(Node *node) {
    if (node == NULL) return;
    imprimirArvore(node->leftNode());
    cout << node->key() << " ";
    imprimirArvore(node->rightNode());
}

int main() {
    // Criando a árvore e inserindo nós iniciais
    Node *root = new Node(8, 'h');
    root = binaryTreeInsert(root, 3, 'c');
    root = binaryTreeInsert(root, 10, 'j');
    root = binaryTreeInsert(root, 1, 'a');
    root = binaryTreeInsert(root, 6, 'f');
    root = binaryTreeInsert(root, 14, 'n');
    root = binaryTreeInsert(root, 4, 'd');
    root = binaryTreeInsert(root, 7, 'g');
    root = binaryTreeInsert(root, 13, 'm');

    // Imprimindo a árvore inicial em ordem
    cout << "Árvore inicial em ordem: ";
    imprimirArvore(root);
    cout << endl;

    // Inserindo novos nós
    root = binaryTreeInsert(root, 5, 'e');
    root = binaryTreeInsert(root, 9, 'i');
    cout << "Árvore após inserção de 5 e 9: ";
    imprimirArvore(root);
    cout << endl;

    // Excluindo um nó com um filho
    root = binaryTreeDelete(root, 6);
    cout << "Árvore após remoção do nó com chave 6: ";
    imprimirArvore(root);
    cout << endl;

    // Excluindo um nó com dois filhos
    root = binaryTreeDelete(root, 3);
    cout << "Árvore após remoção do nó com chave 3: ";
    imprimirArvore(root);
    cout << endl;

    // Buscando o sucessor do nó com chave 8
    Node *sucessor = ArvoreBuscaSucessor(root);
    if (sucessor != NULL) {
        cout << "Sucessor do nó com chave 8: " << sucessor->key() << endl;
    } else {
        cout << "Não há sucessor para o nó com chave 8" << endl;
    }

    // Buscando o predecessor do nó com chave 8
    Node *predecessor = ArvoreBuscaPredecessor(root);
    if (predecessor != NULL) {
        cout << "Predecessor do nó com chave 8: " << predecessor->key() << endl;
    } else {
        cout << "Não há predecessor para o nó com chave 8" << endl;
    }

    // Excluindo a árvore inteira liberando a memória
    delete root;

    return 0;
}
