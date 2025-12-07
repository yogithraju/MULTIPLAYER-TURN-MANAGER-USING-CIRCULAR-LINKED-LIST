#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[50];
    struct Node *next;
} Node;

Node *head = NULL;

// Create a new node
Node* createNode(char name[]) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;
    return newNode;
}

// Add player
void addPlayer(char name[]) {
    Node *newNode = createNode(name);

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
        return;
    }

    Node *temp = head;
    while (temp->next != head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = head;
}

// Remove player
void removePlayer(char name[]) {
    if (head == NULL) {
        printf("No players to remove!\n");
        return;
    }

    Node *temp = head, *prev = NULL;

    // If removing head
    if (strcmp(head->name, name) == 0) {
        while (temp->next != head)
            temp = temp->next;

        if (temp == head) {  // Only 1 node
            free(head);
            head = NULL;
            return;
        }

        temp->next = head->next;
        Node *del = head;
        head = head->next;
        free(del);
        return;
    }

    // Removing middle/last node
    temp = head->next;
    prev = head;

    while (temp != head) {
        if (strcmp(temp->name, name) == 0) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Player not found!\n");
}

// Display players
void displayPlayers() {
    if (head == NULL) {
        printf("No players in the game!\n");
        return;
    }

    Node *temp = head;
    printf("\nPlayers: ");
    do {
        printf("%s -> ", temp->name);
        temp = temp->next;
    } while (temp != head);
    printf("(back to start)\n");
}

// Turn manager
void startTurns(int rounds) {
    if (head == NULL) {
        printf("Add players first!\n");
        return;
    }

    Node *current = head;
    printf("\nStarting Turns...\n");
    int i;
    for ( i = 1; i <= rounds; i++) {
        printf("Round %d - Player: %s\n", i, current->name);
        current = current->next;
    }
}

// MAIN MENU
int main() {
    int choice, rounds;
    char name[50];

    while (1) {
        printf("\n=== TURN MANAGER MENU ===\n");
        printf("1. Add Player\n");
        printf("2. Remove Player\n");
        printf("3. Display Players\n");
        printf("4. Start Turns\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter player name: ");
                scanf("%s", name);
                addPlayer(name);
                break;

            case 2:
                printf("Enter player name to remove: ");
                scanf("%s", name);
                removePlayer(name);
                break;

            case 3:
                displayPlayers();
                break;

            case 4:
                printf("Enter number of turns to simulate: ");
                scanf("%d", &rounds);
                startTurns(rounds);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}

