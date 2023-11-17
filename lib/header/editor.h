#ifndef EDITOR_H
#define EDITOR_H

typedef struct Node {
    char cpf[12];
    char nome[100];
    struct Node *next;
} Node;

void printList(Node *head);
void appendToList(Node **head);
void saveToFile(Node *head);


#endif