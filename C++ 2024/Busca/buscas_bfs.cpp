// Exercício: dada uma árvore binária 𝐴 imprima a chave de todos os nós através da busca em largura

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
int AlturaNo(Node *node) {
    if (node == NULL) {
        return -1;
    }
    int leftHeight = AlturaNo(node->leftNode());
    int rightHeight = AlturaNo(node->rightNode());
    return max(leftHeight, rightHeight) + 1;
}

// Função que imprime um nível específico da árvore (para BFS)
void printLevel(Node *node, int level) {
    
    // Caso base: se o nó for nulo, não há nada a ser impresso
    if (node == NULL) {
        return;
    }

    // Se o nível atual for 1, significa que chegamos ao nível desejado, então imprimimos a chave do nó atual
    if (level == 1) {
        cout << node->key() << " ";
    } 
    //O nível 1 representa o próprio nó a partir do qual a função é chamada, e os níveis seguintes correspondem aos nós filhos em relação ao nó passado.
    
    // Caso contrário, continuamos a busca descendo na árvore
    // Chamamos a função recursivamente para os nós filhos (esquerda e direita) e diminuímos o nível em 1 a cada chamada
    else if (level > 1) {
        printLevel(node->leftNode(), level - 1);  // Nó esquerdo
        printLevel(node->rightNode(), level - 1); // Nó direito
    }
}

// Função que imprime a árvore usando BFS (busca em largura) com complexidade ϴ(n²)
void printArvoreBFS(Node *root) {
    // Calcula a altura da árvore, o que define a profundidade (ou número de níveis) da árvore.
    // A função AlturaNo(root) retorna a altura da árvore a partir da raiz, e somamos 1 para
    // considerar o nível da raiz como parte da profundidade total.
    int depth = AlturaNo(root) +1 ;

    // Loop que percorre todos os níveis da árvore, do nível 1 (raiz) até o último nível (folhas).
    // A variável 'i' começa de 0 e vai até a profundidade total - 1. Como os níveis na árvore são
    // numerados a partir de 1 na função printLevel, usamos 'i + 1' para imprimir corretamente os níveis.
    for (int i = 0; i < depth; i++) {
        printLevel(root, i + 1);  // Chama a função que imprime todos os nós do nível 'i + 1'
    }
}

// Função que imprime a árvore usando BFS com uma fila (versão otimizada) com complexidade ϴ(n)
void printArvoreBFSOtimizadaFila(Node *root) {
    if (root == NULL) {
        return;  
    }

    // Cria uma fila de ponteiros para nós (Node*) para realizar a travessia em largura (BFS).
    // A fila vai armazenar temporariamente os nós da árvore à medida que percorremos nível por nível.
    queue<Node*> queue;

    // Começamos pela raiz da árvore, então o primeiro nó a ser processado é a raiz (root).
    // Inserimos a raiz na fila.
    queue.push(root);

    // Enquanto a fila não estiver vazia (ou seja, ainda houver nós para processar),
    // continuamos a processar os nós nível por nível.
    while (!queue.empty()) {

        // Obtemos o nó na frente da fila (ou seja, o nó a ser processado no momento).
        Node *node = queue.front();

        // Imprime a chave do nó atual.
        cout << node->key() << " ";

        // Removemos o nó da frente da fila, pois ele já foi processado.
        queue.pop();

        // Se o nó atual tiver um filho à esquerda (leftNode), colocamos esse filho na fila.
        // Isso garante que vamos processar o filho esquerdo em algum momento futuro.
        if (node->leftNode()) {
            queue.push(node->leftNode());
        }

        // Se o nó atual tiver um filho à direita (rightNode), também colocamos esse filho na fila.
        // Assim, o filho direito será processado após todos os nós no nível atual.
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

// Imprimindo a altura de uma arvore
    cout << "Altura da arvore: ";
    cout<< AlturaNo(n1);  // A partir da raiz (n1)
    cout << endl;    
    
    // Imprimindo a altura de um nó qualquer
    cout << "Altura de um no qualquer: ";
    cout<< AlturaNo(n3);
    cout << endl;   
    
    // Imprimindo um nível da árvore
    //Se você sempre quiser cobrir toda a árvore binária, então o ponto de partida deve ser a raiz
    cout << "Nivel a partir de n1(raiz): ";
    printLevel(n1,2);
    cout << endl;     

    // Imprimindo um nível incompleto
    cout << "Nivel do no n3: ";
    printLevel(n3,2);
    cout << endl;   

    // Imprimindo a árvore usando BFS (busca em largura)
    cout << "Chaves da arvore em ordem de nivel (BFS): ";
    printArvoreBFS(n1);  // A partir da raiz (n1)
    cout << endl;

    // Imprimindo a árvore usando BFS com fila (otimizada)
    cout << "Chaves da arvore em ordem de nivel (BFS com fila): ";
    printArvoreBFSOtimizadaFila(n1);  // A partir da raiz (n1)
    cout << endl;


    //OBS: não pode usar void e cout na mesma linha. Só chama a função.
    // Liberando a memória alocada
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    delete n6;

    return 0;
}
