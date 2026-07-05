#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define PRIORITY 10

typedef struct Node {
    int val;
    struct Node *next;
} Node;
Node *front[PRIORITY];
void init() {
    for(int i = 0; i < PRIORITY; i++)
        front[i] = NULL;
}
bool isEmpty() {
    for(int i = 0; i < PRIORITY; i++)
        if(front[i] != NULL)
            return false;

    return true;
}
void enqueue(int val, int priority) {
    if (priority < 0 || priority >= PRIORITY) {
        printf("Invalid Priority Level\n");
        return;
    }

    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Overflow (Memory Allocation Failed)\n");
        return;
    }

    newNode->val = val;
    newNode->next = NULL;
    if(front[priority] == NULL) {
        front[priority] = newNode;
    } else {
        Node *ptr = front[priority];

        while(ptr->next)
            ptr = ptr->next;

        ptr->next = newNode;
    }

    printf("Enqueued Successfully.\n");
}

int peek() {
    if(isEmpty()) {
        printf("Underflow\n");
        return -1;
    }

    for(int i = PRIORITY - 1; i >= 0; i--) {
        if(front[i] != NULL)
            return front[i]->val;
    }
    return -1;
}

int dequeue()
{
    if(isEmpty()) {
        printf("Underflow\n");
        return -1;
    }

    for(int i = PRIORITY - 1; i >= 0; i--) {
        if(front[i] != NULL) {
            Node *temp = front[i];
            int val = temp->val;
            front[i] = front[i]->next;
            free(temp);
            return val;
        }
    }
    return -1;
}

void display() {
    if(isEmpty()) {
        printf("Queue Empty\n");
        return;
    }

    printf("\n--- Current Queue State ---");
    for(int i = PRIORITY - 1; i >= 0; i--) {
        if (front[i] != NULL) {
            printf("\nPriority %d : ", i);
            Node *ptr = front[i];
            while(ptr) {
                printf("[%d] -> ", ptr->val);
                ptr = ptr->next;
            }
            printf("NULL");
        }
    }
    printf("\n---------------------------\n");
}

int main()
{
    srand(time(NULL));
    init();
    
    int ch;
    int val;
    int priority;
    int temp;

    while (1) {
        printf("\n-------------------------\n");
        printf(" Priority Queue (Array of Lists)\n");
        printf("-------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Exit\n");
        printf(">>>  ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            val = rand() % 100;
            priority = rand() % 5; 
            printf("Enter Value : %d\n", val);
            printf("Enter Priority : %d\n", priority);

            enqueue(val, priority);
            display();
            break;

        case 2:
            temp = dequeue();

            if (temp != -1)
            {
                printf("Dequeued Value : %d\n", temp);
            }
            display();
            break;

        case 3:
            temp = peek();

            if (temp != -1)
            {
                printf("Highest Priority Front Element : %d\n", temp);
            }
            display();
            break;

        default:
            printf("Program terminating ... \n");
            return 0;
        }
    }
}