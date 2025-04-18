#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list structure
typedef struct {
    Node* head;
    int size;
} LinkedList;

// Initialize a linked list
LinkedList* createList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL; // Allocation failure
    list->head = NULL;
    list->size = 0;
    return list;
}

// Free all memory allocated for the linked list
void destroyList(LinkedList* list) {
    if (!list) return;

    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}

// Add an element to the beginning of the list
int addFirst(LinkedList* list, int value) {
    if (!list) return 0;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return 0; // Allocation failure

    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
    return 1;
}

// Add an element to the end of the list
int addLast(LinkedList* list, int value) {
    if (!list) return 0;

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return 0;

    newNode->data = value;
    newNode->next = NULL;

    if (!list->head) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
    return 1;
}

// Insert an element at a specific position
int insertAt(LinkedList* list, int position, int value) {
    if (!list || position < 0 || position > list->size) return 0;

    if (position == 0) return addFirst(list, value);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return 0;

    newNode->data = value;

    Node* current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;

    list->size++;
    return 1;
}

// Remove an element at a specific position
int removeAt(LinkedList* list, int position) {
    if (!list || position < 0 || position >= list->size) return 0;

    Node* current = list->head;

    if (position == 0) {
        list->head = current->next;
        free(current);
        list->size--;
        return 1;
    }

    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    Node* temp = current->next;
    current->next = temp->next;
    free(temp);

    list->size--;
    return 1;
}

// Find the first occurrence of a value
int find(LinkedList* list, int value) {
    if (!list) return -1;

    Node* current = list->head;
    int position = 0;

    while (current) {
        if (current->data == value) return position;
        current = current->next;
        position++;
    }
    return -1;
}

// Get the element at a specific position
int getAt(LinkedList* list, int position) {
    if (!list || position < 0 || position >= list->size) return -1;

    Node* current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

// Check if the list is empty
int isEmpty(LinkedList* list) {
    if (!list) return 1;
    return list->size == 0;
}

// Get the current size of the list
int size(LinkedList* list) {
    if (!list) return -1;
    return list->size;
}

// Clear the list
void clear(LinkedList* list) {
    if (!list) return;

    while (list->head) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
    list->size = 0;
}

// Print the list contents
void printList(LinkedList* list) {
    if (!list || !list->head) {
        printf("List is empty.\n");
        return;
    }

    Node* current = list->head;
    printf("Linked List:\nHead");

    while (current) {
        printf(" -> [%d]", current->data);
        current = current->next;
    }
    printf(" -> NULL\nSize: %d\n\n", list->size);
}

int main() {
    LinkedList* list = createList();

    addFirst(list, 20);
    addFirst(list, 10);
    addLast(list, 30);
    addLast(list, 40);
    printList(list);

    insertAt(list, 2, 25);
    printf("After inserting 25 at position 2:\n");
    printList(list);

    removeAt(list, 3);
    printf("After removing element at position 3:\n");
    printList(list);

    printf("Element at position 2: %d\n", getAt(list, 2));
    printf("Position of value 30: %d\n", find(list, 30));

    clear(list);
    printf("After clearing the list:\n");
    printList(list);

    destroyList(list);
    return 0;
}