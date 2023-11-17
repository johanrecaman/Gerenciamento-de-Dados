#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/header/editor.h"

void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s, %s\n", current->cpf, current->nome);
        current = current->next;
    }
}

void saveToFile(Node *head) {
    FILE *bin = fopen("output.bin", "wb");
    if (!bin) {
        perror("Error opening binary file for writing");
        exit(1);
    }

    Node *current = head;
    while (current != NULL) {
        if (fwrite(current->cpf, sizeof(char), sizeof(current->cpf), bin) != sizeof(current->cpf) ||
            fwrite(current->nome, sizeof(char), sizeof(current->nome), bin) != sizeof(current->nome)) {
            perror("Error writing to binary file");
            exit(1);
        }
        current = current->next;
    }

    fclose(bin);
}

void appendToList(Node **head) {
    Node *newNode = malloc(sizeof(Node));
    if (!newNode) {
        perror("Memory allocation error");
        exit(1);
    }

    printf("Enter CPF: ");
    scanf("%s", newNode->cpf);

    printf("Enter Name: ");
    scanf("%s", newNode->nome);

    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void deleteItem(Node **head, char *cpfToDelete) {
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL && strcmp(current->cpf, cpfToDelete) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("CPF not found in the list.\n");
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    printf("Item with CPF %s deleted successfully.\n", cpfToDelete);
    free(current);
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

    int option;

    while (1) {
        printf("\nWhat do you want to do?\n");
        printf("1 - Print list\n");
        printf("2 - Add\n");
        printf("3 - Delete Item\n");
        printf("4 - Exit\n");

        scanf("%d", &option);

        switch (option) {
            case 1:
                printList(head);
                printf("\nPress Enter to return to the menu.");
                getchar();
                getchar();
                break;
            case 2:
                appendToList(&head);
                printList(head);
                saveToFile(head);
                break;
            case 3:
                printf("Enter CPF to delete: ");
                char cpfToDelete[12];
                scanf("%s", cpfToDelete);
                deleteItem(&head, cpfToDelete);
                saveToFile(head);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}