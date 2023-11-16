#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char cpf[12];
    char nome[100];
    struct Node *next;
} Node;

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s, %s\n", current->cpf, current->nome);
        current = current->next;
    }
}

int main() {
    FILE *bin;
    Node *head = NULL;
    Node *current = NULL;

    bin = fopen("output.bin", "rb");
    if (!bin) {
        perror("Error opening binary file");
        return 1;
    }

    while (1) {
        Node *newNode = malloc(sizeof(Node));
        if (!newNode) {
            perror("Memory allocation error");
            return 1;
        }

        if (fread(newNode->cpf, sizeof(char), sizeof(newNode->cpf), bin) != sizeof(newNode->cpf) ||
            fread(newNode->nome, sizeof(char), sizeof(newNode->nome), bin) != sizeof(newNode->nome)) {
            free(newNode);
            break; 
        }

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    fclose(bin);

    printList(head);

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}