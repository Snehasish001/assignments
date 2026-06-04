#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Create Node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// I. Create Linked List
Node* createList() {
    int n, data;
    Node *head = NULL, *tail = NULL;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter data: ");
        scanf("%d", &data);

        Node* newNode = createNode(data);

        if(head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    return head;
}

// II. Display List
void display(Node* head) {
    if(head == NULL) {
        printf("List is Empty\n");
        return;
    }

    printf("List: ");

    while(head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }

    printf("\n");
}

// III. Insert at Front
Node* insertFront(Node* head, int data) {
    Node* newNode = createNode(data);

    newNode->next = head;

    if(head != NULL)
        head->prev = newNode;

    return newNode;
}

// IV. Insert at End
Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);

    if(head == NULL)
        return newNode;

    Node* temp = head;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;

    return head;
}

// V. Insert after kth node
Node* insertAfterK(Node* head, int k, int data) {
    Node* temp = head;

    for(int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL) {
        printf("Invalid Position\n");
        return head;
    }

    Node* newNode = createNode(data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;

    return head;
}

// VI. Insert after value
Node* insertAfterValue(Node* head, int value, int data) {
    Node* temp = head;

    while(temp != NULL && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return head;
    }

    Node* newNode = createNode(data);

    newNode->next = temp->next;
    newNode->prev = temp;

    if(temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;

    return head;
}

// VII. Insert before kth node
Node* insertBeforeK(Node* head, int k, int data) {
    if(k == 1)
        return insertFront(head, data);

    Node* temp = head;

    for(int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL) {
        printf("Invalid Position\n");
        return head;
    }

    Node* newNode = createNode(data);

    newNode->next = temp;
    newNode->prev = temp->prev;

    temp->prev->next = newNode;
    temp->prev = newNode;

    return head;
}

// VIII. Insert before value
Node* insertBeforeValue(Node* head, int value, int data) {
    Node* temp = head;

    while(temp != NULL && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return head;
    }

    if(temp == head)
        return insertFront(head, data);

    Node* newNode = createNode(data);

    newNode->next = temp;
    newNode->prev = temp->prev;

    temp->prev->next = newNode;
    temp->prev = newNode;

    return head;
}

// IX. Delete First Node
Node* deleteFirst(Node* head) {
    if(head == NULL)
        return NULL;

    Node* temp = head;

    head = head->next;

    if(head != NULL)
        head->prev = NULL;

    free(temp);

    return head;
}

// X. Delete Last Node
Node* deleteLast(Node* head) {
    if(head == NULL)
        return NULL;

    if(head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* temp = head;

    while(temp->next != NULL)
        temp = temp->next;

    temp->prev->next = NULL;

    free(temp);

    return head;
}

// XI. Delete node after kth node
Node* deleteAfterK(Node* head, int k) {
    Node* temp = head;

    for(int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL || temp->next == NULL) {
        printf("Deletion not possible\n");
        return head;
    }

    Node* del = temp->next;

    temp->next = del->next;

    if(del->next != NULL)
        del->next->prev = temp;

    free(del);

    return head;
}

// XII. Delete node before kth node
Node* deleteBeforeK(Node* head, int k) {
    if(k <= 2) {
        printf("Deletion not possible\n");
        return head;
    }

    Node* temp = head;

    for(int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL || temp->prev == NULL) {
        printf("Deletion not possible\n");
        return head;
    }

    Node* del = temp->prev;

    if(del == head) {
        head = head->next;
        head->prev = NULL;
        free(del);
        return head;
    }

    del->prev->next = temp;
    temp->prev = del->prev;

    free(del);

    return head;
}

// XIII. Delete kth node
Node* deleteK(Node* head, int k) {
    if(k == 1)
        return deleteFirst(head);

    Node* temp = head;

    for(int i = 1; i < k && temp != NULL; i++)
        temp = temp->next;

    if(temp == NULL) {
        printf("Invalid Position\n");
        return head;
    }

    if(temp->next != NULL)
        temp->next->prev = temp->prev;

    temp->prev->next = temp->next;

    free(temp);

    return head;
}

// XIV. Delete node containing specified value
Node* deleteValue(Node* head, int value) {
    Node* temp = head;

    while(temp != NULL && temp->data != value)
        temp = temp->next;

    if(temp == NULL) {
        printf("Value not found\n");
        return head;
    }

    if(temp == head)
        return deleteFirst(head);

    if(temp->next != NULL)
        temp->next->prev = temp->prev;

    temp->prev->next = temp->next;

    free(temp);

    return head;
}

// XV. Reverse the List
Node* reverseList(Node* head) {
    Node *temp = NULL;
    Node *current = head;

    while(current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        current = current->prev;
    }

    if(temp != NULL)
        head = temp->prev;

    return head;
}

// Free List
void freeList(Node* head) {
    Node* temp;

    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    int choice, data, k, value;

    do {
        printf("\n===== DOUBLY LINKED LIST MENU =====\n");
        printf("1. Create List\n");
        printf("2. Display List\n");
        printf("3. Insert Front\n");
        printf("4. Insert End\n");
        printf("5. Insert After Kth Node\n");
        printf("6. Insert After Value\n");
        printf("7. Insert Before Kth Node\n");
        printf("8. Insert Before Value\n");
        printf("9. Delete First Node\n");
        printf("10. Delete Last Node\n");
        printf("11. Delete After Kth Node\n");
        printf("12. Delete Before Kth Node\n");
        printf("13. Delete Kth Node\n");
        printf("14. Delete Value\n");
        printf("15. Reverse List\n");
        printf("0. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                freeList(head);
                head = createList();
                break;

            case 2:
                display(head);
                break;

            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insertFront(head, data);
                break;

            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insertEnd(head, data);
                break;

            case 5:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                head = insertAfterK(head, k, data);
                break;

            case 6:
                printf("Enter value and data: ");
                scanf("%d%d", &value, &data);
                head = insertAfterValue(head, value, data);
                break;

            case 7:
                printf("Enter k and data: ");
                scanf("%d%d", &k, &data);
                head = insertBeforeK(head, k, data);
                break;

            case 8:
                printf("Enter value and data: ");
                scanf("%d%d", &value, &data);
                head = insertBeforeValue(head, value, data);
                break;

            case 9:
                head = deleteFirst(head);
                break;

            case 10:
                head = deleteLast(head);
                break;

            case 11:
                printf("Enter k: ");
                scanf("%d", &k);
                head = deleteAfterK(head, k);
                break;

            case 12:
                printf("Enter k: ");
                scanf("%d", &k);
                head = deleteBeforeK(head, k);
                break;

            case 13:
                printf("Enter k: ");
                scanf("%d", &k);
                head = deleteK(head, k);
                break;

            case 14:
                printf("Enter value: ");
                scanf("%d", &value);
                head = deleteValue(head, value);
                break;

            case 15:
                head = reverseList(head);
                printf("List Reversed Successfully\n");
                break;

            case 0:
                printf("Program Terminated.\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 0);

    freeList(head);

    return 0;
}