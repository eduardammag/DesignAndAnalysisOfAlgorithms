#include <iostream>
using namespace std;

// Definindo a estrutura do nó
struct Node {
    int data;
    Node* next;
};

// Função para inserir um nó no final da lista encadeada
void append(Node** head_ref, int new_data) {
    Node* new_node = new Node();
    Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = nullptr;

    if (*head_ref == nullptr) {
        *head_ref = new_node;
        return;
    }

    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = new_node;
}

// Função para exibir a lista encadeada
void printList(Node* node) {
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

// Função de bubble sort para a lista encadeada
void bubbleSort(Node* head) {
    if (head == nullptr) return;

    bool swapped;
    Node* ptr1;
    Node* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Troca os dados dos nós
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Função principal
int main() {
    Node* head = nullptr;

    // Inserindo valores na lista encadeada
    append(&head, 64);
    append(&head, 34);
    append(&head, 25);
    append(&head, 12);
    append(&head, 22);
    append(&head, 11);
    append(&head, 90);

    cout << "Lista antes do Bubble Sort: ";
    printList(head);

    bubbleSort(head);

    cout << "Lista depois do Bubble Sort: ";
    printList(head);

    return 0;
}

