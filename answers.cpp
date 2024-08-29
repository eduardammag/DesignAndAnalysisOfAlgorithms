#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

// Questão 1: Encontrar o nó com índice mínimo
int find_minimum(Node* node) {
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->key;
}

// Questão 2: Encontrar o nó com índice máximo
int find_maximum(Node* node) {
    Node* current = node;
    while (current->right != NULL) {
        current = current->right;
    }
    return current->key;
}

// Questão 3: Encontrar o sucessor de um nó
Node* find_successor(Node* root, Node* node) {
    if (node->right) {
        Node* current = node->right;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node* successor = NULL;
    Node* current = root;
    while (current != NULL) {
        if (node->key < current->key) {
            successor = current;
            current = current->left;
        } else if (node->key > current->key) {
            current = current->right;
        } else {
            break;
        }
    }
    return successor;
}

// Questão 4: Encontrar o predecessor de um nó
Node* find_predecessor(Node* root, Node* node) {
    if (node->left) {
        Node* current = node->left;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    }

    Node* predecessor = NULL;
    Node* current = root;
    while (current != NULL) {
        if (node->key > current->key) {
            predecessor = current;
            current = current->right;
        } else if (node->key < current->key) {
            current = current->left;
        } else {
            break;
        }
    }
    return predecessor;
}

// Questão 5: Inserir uma chave mantendo as propriedades da BST
Node* insert(Node* node, int key) {
    if (node == NULL) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else {
        node->right = insert(node->right, key);
    }

    return node;
}

// Questão 6: Remover um nó mantendo as propriedades da BST
Node* remove(Node* node, int key) {
    if (node == NULL) return node;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (node->left == NULL) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == NULL) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = node->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }

        node->key = temp->key;
        node->right = remove(node->right, temp->key);
    }
    return node;
}
