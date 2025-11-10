#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define URL_SIZE 100
#define HISTORY_FILE "history.txt"

//doubly linked list - nodes with broser history 
typedef struct Node {
    char url[URL_SIZE];
    struct Node* prev;
    struct Node* next;
} Node;

Node* current = NULL;
Node* createNode(char* url) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

//Function to visit a new website
void visitNewSite() {
    char url[URL_SIZE];
    printf("Enter URL: ");
    scanf("%s", url);
    Node* newNode = createNode(url);

    if (current == NULL) {
        current = newNode;
    } else {
        Node* temp = current->next;
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    printf("Visited: %s\n", current->url);
}

//Function to go back
void goBack() {
    if (current == NULL || current->prev == NULL) {
        printf("No previous page available.\n");
        return;
    }
    current = current->prev;
    printf("Moved back to: %s\n", current->url);
}

//Function to go forward
void goForward() {
    if (current == NULL || current->next == NULL) {
        printf("No forward page available.\n");
        return;
    }
    current = current->next;
    printf("Moved forward to: %s\n", current->url);
}

//Function to show browsing history
void showHistory() {
    if (current == NULL) {
        printf("No browsing history.\n");
        return;
    }

    Node* temp = current;
    while (temp->prev != NULL)
        temp = temp->prev;

    printf("\n=== Browsing History ===\n");
    while (temp != NULL) {
        if (temp == current)
            printf("-> %s (current)\n", temp->url);
        else
            printf("   %s\n", temp->url);
        temp = temp->next;
    }
    printf("========================\n");
}

// Function to clear/free memory
void clearHistory() {
    if (current == NULL) return;

    Node* temp = current;
    while (temp->prev != NULL)
        temp = temp->prev;

    while (temp != NULL) {
        Node* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
}

//Function to save browsing history to a file
void saveHistory() {
    FILE* file = fopen(HISTORY_FILE, "w");
    if (!file) {
        printf("Error saving history!\n");
        return;
    }

    Node* temp = current;
    while (temp && temp->prev != NULL)
        temp = temp->prev;

    while (temp != NULL) {
        fprintf(file, "%s\n", temp->url);
        temp = temp->next;
    }

    fclose(file);
    printf("History saved to '%s'.\n", HISTORY_FILE);
}

//Function to load history from a file
void loadHistory() {
    FILE* file = fopen(HISTORY_FILE, "r");
    if (!file) {
        printf("No saved history found. Starting fresh.\n");
        return;
    }

    char url[URL_SIZE];
    Node* last = NULL;

    while (fscanf(file, "%s", url) != EOF) {
        Node* newNode = createNode(url);
        if (current == NULL) {
            current = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
    fclose(file);

    if (current != NULL) {
        while (current->next != NULL)
            current = current->next;
    }

    printf("History loaded from '%s'.\n", HISTORY_FILE);
}

int main() {
    int choice;
    loadHistory(); 

    while (1) {
        printf("\n===== Browser History Simulator =====\n");
        printf("1. Visit a new website\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show history\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                visitNewSite();
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showHistory();
                break;
            case 5:
                saveHistory();
                clearHistory();
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
