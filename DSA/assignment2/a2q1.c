#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node;

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

//1. create
Node* create(int val) {
    Node* head = (Node*)malloc(sizeof(Node));

    if (head == NULL) {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }

    head->next = NULL;
    head->val = val;
    return head;
}

//2. print
void print(Node* head) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return;
    }
    Node* temp = head;
    printf("[%p] -> ", temp);
    while (temp != NULL)
    {
        if (temp->next == NULL) {
            printf("[%d | %p]", temp->val, temp->next);
        } else {
            printf("[%d | %p] -> ", temp->val, temp->next);
        }
        temp = temp->next;
    }
    printf("\n");
}

//3. insert at front
Node* insertFront(Node* head, int val) {
    if (head == NULL) return create(val);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = head;
    head = newNode;
    return head;
}

//4. insert at end
Node* insertEnd(Node* head, int val) {
    if (head == NULL) return create(val);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = NULL;
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

//5. insert after kth node
Node* insertAfter(Node* head, int val, int pos) {
    if (pos == 0 && head == NULL) return create(val);
    if (pos == 0 && head != NULL) return insertFront(head, val);

    Node* temp = head;
    int flag = 0;
    while (temp != NULL) {
        pos--;
        if (pos == 0) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (!flag) {
        printf("Insertion Failed. Position out of range.\n");
        return head;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

//6. insert a node after value
Node* insertAfterValue(Node* head, int val, int pos) {
    Node* temp = head;
    int flag = 0;
    while (temp != NULL) {
        if (temp->val == pos) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (!flag) {
        printf("Value does not matched.\n");
        return head;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

//7. insert before kth node
Node* insertBefore(Node* head, int val, int pos) {
    if (head == NULL && pos == 1) return create(val);
    if (head == NULL) {
        printf("Insertion Failed.\n");
        return head;
    }
    if (pos == 1) return insertFront(head, val);
    Node* temp = head;
    int flag = 0;
    pos -= 2;
    while (temp != NULL) {
        pos--;
        if (pos == 0) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (!flag || temp == NULL) {
        printf("Insertion Failed. Position out of Bound.\n");
        return head;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

//8. insert a node before value
Node* insertBeforeValue(Node* head, int val, int pos) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return head;
    }
    if (head->val == pos) return insertFront(head, val);
    Node* temp = head;
    int flag = 0;
    while (temp->next != NULL) {
        if (temp->next->val == pos) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (!flag) {
        printf("Value does not matched.\n");
        return head;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory Allocation Failed.\n");
        return head;
    }
    newNode->val = val;
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

//9. delete first node
Node* deleteFront(Node* head) {
    if (head == NULL) return head;
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

//10. delete the last node
Node* deleteEnd(Node* head) {
    if (head == NULL) return head;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    Node* temp = head;
    while(temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}

//11. delete a node after kth
Node* deleteAfterKth(Node* head, int pos) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return head;
    }
    Node* temp = head;
    while (temp != NULL && pos > 1) {
        temp = temp->next;
        pos--;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Deletion Failed. Position out of Bound.\n");
        return head;
    }
    Node* t = temp->next;
    temp->next = temp->next->next;
    free(t);
    return head;
}

//12. delete a node before kth node
Node* deleteBeforeKth(Node* head, int pos) {
    if (head == NULL || pos <= 1) {
        printf("Deletion Failed.\n");
        return head;
    }
    if (pos == 2) return deleteFront(head);
    Node* temp = head;
    while (temp != NULL && pos > 3) {
        temp = temp->next;
        pos--;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Deletion Failed. Position out of Bound.\n");
        return head;
    }
    Node* t = temp->next;
    temp->next = temp->next->next;
    free(t);
    return head;
}

//13. delete kth node
Node* deleteKth(Node* head, int pos) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return head;
    }
    if (pos == 1) return deleteFront(head);
    Node* temp = head;
    while (temp != NULL && pos > 2) {
        temp = temp->next;
        pos--;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Deletion Failed. Position out of Bound.\n");
        return head;
    }
    Node* t = temp->next;
    temp->next = temp->next->next;
    free(t);
    return head;
}

//14. delete Node value
Node* deleteNodeValue(Node* head, int val) {
    if (head == NULL) {
        printf("List is Empty.\n");
        return head;
    }
    if (head->val == val) return deleteFront(head);
    Node* temp = head;
    int flag = 0;
    while (temp->next != NULL) {
        if (temp->next->val == val) {
            flag = 1;
            break;
        }
        temp = temp->next;
    }
    if (!flag) {
        printf("Deletion Failed. Value does not matched.\n");
        return head;
    }
    Node* t = temp->next;
    temp->next = temp->next->next;
    free(t);
    return head;
}

//15. reverse
Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

//16. sort
Node* sort(Node* head) {
    if (head == NULL) return head;
    Node* i;
    Node* j;
    for (i = head; i != NULL; i = i->next) {
        Node* min = i;
        for (j = i->next; j != NULL; j = j->next) {
            if (j->val < min->val) {
                min = j;
            }
        }
        if (min != i) {
            int temp = i->val;
            i->val = min->val;
            min->val = temp;
        }
    }
    return head;
}
//17. search
int search(Node* head, int val) {
    Node* temp = head;
    int pos = -1;
    while (temp != NULL) {
        pos++;
        if (temp->val == val) {
            return pos;
        }
        temp = temp->next;
    }
    return -1;
}


//18. merge in sorted
Node* merge(Node* head1, Node* head2) {
    if (head1 == NULL) return sort(head2);
    if (head2 == NULL) return sort(head1);

    head1 = sort(head1);
    head2 = sort(head2);

    Node* temp1;
    Node* temp2 = head2;

    while (temp2 != NULL) {

        Node* nextNode = temp2->next;
        if (temp2->val < head1->val) {
            temp2->next = head1;
            head1 = temp2;
        } else {
            temp1 = head1;
            while (temp1->next != NULL && temp1->next->val < temp2->val) {
                temp1 = temp1->next;
            }

            temp2->next = temp1->next;
            temp1->next = temp2;
        }

        temp2 = nextNode;
    }

    return head1;
}

//19. concatenate 
Node* concatenate(Node* head1, Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1; 
    Node* temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;
    return head1;
}

//20. equal
int isEqual(Node* head1, Node* head2) {
    int flag = 1;
    if (head1 == head2) return flag;
    while (head1 != NULL && head2 != NULL) {
        if (head1->val != head2->val) {
            flag = 0;
            break;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    
    if (flag == 1 && head1 == head2) {
        return flag;
    } else {
        return 0;
    }
}

//helper
Node* createAnother() {
    int size, val;
    Node* head = NULL;
    printf("Enter the size : ");
    scanf("%d",&size);
    for (int i = 1; i <= size; i++) {
        printf("Enter %dth element : ", i);
        scanf("%d",&val);
        head = insertEnd(head, val);
    }
    return head;
}


int main()
{
    int flag = 1;
    int choice, val, pos;
    Node *head = NULL, *head1 = NULL;

    do {
        printf("\n=================================\nPress\n");
        printf("1. create\n");
        printf("2. print\n");
        printf("3. insert at front\n");
        printf("4. insert at end\n");
        printf("5. insert after kth node\n");
        printf("6. insert a node after value\n");
        printf("7. insert before kth node\n");
        printf("8. insert a node before value\n");
        printf("9. delete first node\n");
        printf("10. delete the last node\n");
        printf("11. delete a node after the kth node\n");
        printf("12. delete a node before kth node\n");
        printf("13. delete the kth node\n");
        printf("14. delete the node with value\n");
        printf("15. reverse\n");
        printf("16. sort\n");
        printf("17. search\n");
        printf("18. merge\n");
        printf("19. concatenate\n");
        printf("20. Equal\n");
        printf("21. exit\n");
        printf("\n=================================\n>>> ");

        if (scanf("%d", &choice) != 1) {
            printf("\nError: Please enter a valid numerical option.\n\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter the value : ");
            scanf("%d",&val);
            head = create(val);
            print(head);
            break;

        case 2:
            print(head);
            break;

        case 3:
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertFront(head, val);
            print(head);
            break;

        case 4:
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertEnd(head, val);
            print(head);
            break;

        case 5:
            printf("Enter the position (after) : ");
            scanf("%d",&pos);
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertAfter(head, val, pos);
            print(head);
            break;

        case 6:
            print(head);
            printf("Enter the position value : ");
            scanf("%d",&pos);
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertAfterValue(head, val, pos);
            print(head);
            break;

        case 7:
            printf("Enter the position (before) : ");
            scanf("%d",&pos);
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertBefore(head, val, pos);
            print(head);
            break;

        case 8:
            print(head);
            printf("Enter the position value : ");
            scanf("%d",&pos);
            printf("Enter the value : ");
            scanf("%d",&val);
            head = insertBeforeValue(head, val, pos);
            print(head);
            break;

        case 9:
            head = deleteFront(head);
            print(head);
            break;

        case 10:
            head = deleteEnd(head);
            print(head);
            break;

        case 11:
            printf("Enter kth position : ");
            scanf("%d",&pos);
            head = deleteAfterKth(head, pos);
            print(head);
            break;

        case 12:
            printf("Enter kth position : ");
            scanf("%d",&pos);
            head = deleteBeforeKth(head, pos);
            print(head);
            break;

        case 13:
            printf("Enter kth position : ");
            scanf("%d",&pos);
            head = deleteKth(head, pos);
            print(head);
            break;

        case 14:
            printf("Enter value : ");
            scanf("%d",&val);
            head = deleteNodeValue(head, val);
            print(head);
            break;

        case 15:
            head = reverse(head);
            print(head);
            break;

        case 16:
            head = sort(head);
            print(head);
            break;

        case 17:
            printf("Enter the val : ");
            scanf("%d",&val);
            pos = search(head, val);

            if (pos != -1) {
                printf("Item found at %d index.",pos);
            } else {
                printf("Item not found.");
            }
            break;

        case 18:
            head1 = createAnother();
            head = merge(head, head1);
            print(head);
            break;

        case 19:
            head1 = createAnother();
            printf("Before concatenation : \n");
            print(head);
            print(head1);
            head = concatenate(head, head1);
            printf("After concatenation : \n");
            print(head);
            break;

        case 20:
            head1 = createAnother();
            print(head);
            print(head1);
            if (isEqual(head, head1)) {
                printf("Equal.");
            } else {
                printf("Unequal.");
            }
            break;

        case 21:
            flag = 0;
            break;

        default:
            printf("Wrong Input.\n");
            break;
        }

    } while (flag == 1);

    freeList(head1);
    freeList(head);
    return 0;
}