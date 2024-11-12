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
    
    // Função que define a chave do nó
    void setKey(int key) {
    m_key = key;
}

};

Node *BuscaIndiceMin(Node *node) {
    // Se a árvore está vazia (nó nulo), retorna NULL
    if (node == NULL) {
        return node;
    }
    // Caminha para o nó mais à esquerda da árvore
    while (node->leftNode() != NULL) {
        node = node->leftNode();
    }
    // Retorna o nó com a chave mínima
    return node;
}

Node *ArvoreBuscaSucessor(Node *node) {
    if (node == NULL) {
        return node;
    }
    // Se o nó tem filho à direita, o sucessor é o nó com a chave mínima na subárvore direita
    if (node->rightNode() != NULL) {
        return BuscaIndiceMin(node->rightNode());
    }
    // Caso contrário, precisamos subir pela árvore até encontrar um nó que seja filho esquerdo de seu pai
    Node *parentNode = node->parentNode();
    while (parentNode != NULL && node == parentNode->rightNode()) {
        node = parentNode;
        parentNode = parentNode->parentNode();
    }
    // Retorna o sucessor (ou NULL se não houver sucessor)
    return parentNode;
}

//Dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘 crie um novo nó capaz de inserir  a chave mantendo as propriedades de BST.
Node *InsertArvoreBinaria(Node *root, int key) {
    if (root == NULL) {
        return new Node(key, 'A');  // Passando um valor padrão 'A' como dado
    }
    if (key < root->key()) {
        root->setLeftNode(InsertArvoreBinaria(root->leftNode(), key));
    } else {
        root->setRightNode(InsertArvoreBinaria(root->rightNode(), key));
    }
    return root;
}
//Aqui, a complexidade é ϴ(ℎ)


//Dada uma árvore binária de busca 𝐴 com altura ℎ e uma chave 𝑘 remova nó com esta chave mantendo as propriedades de BST.
Node *DeleteNodeArvoreBinaria(Node *root) {
    if (root->leftNode() == NULL && root->rightNode() == NULL) {
        // Se o nó não tem filhos, simplesmente deletamos
        delete root;
        root = NULL;
    } else if (root->leftNode() == NULL) {
        // Se só tem filho à direita, o nó à direita se torna o novo nó
        Node *newRoot = root->rightNode();
        delete root;
        root = newRoot;
    } else if (root->rightNode() == NULL) {
        // Se só tem filho à esquerda, o nó à esquerda se torna o novo nó
        Node *newRoot = root->leftNode();
        delete root;
        root = newRoot;
    } else {
        // Se o nó tem dois filhos, encontramos o sucessor e substituímos a chave
        Node *newRoot = ArvoreBuscaSucessor(root->rightNode());
        root->setKey(newRoot->key());  // Usamos a função setter aqui para definir a nova chave
        root->setRightNode(DeleteArvoreBinaria(root->rightNode(), newRoot->key()));
    }
    return root;
}
//Aqui, a complexidade é ϴ(ℎ)


Node *DeleteArvoreBinaria(Node *root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key()) {
        root->setLeftNode(DeleteArvoreBinaria(root->leftNode(), key));
    } else if (key > root->key()) {
        root->setRightNode(DeleteArvoreBinaria(root->rightNode(), key));
    } else {
        root = DeleteNodeArvoreBinaria(root);
    }
    return root;
}





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
