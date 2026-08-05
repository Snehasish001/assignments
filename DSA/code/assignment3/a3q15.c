#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_COUNT 10

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;


bool isEmpty(Queue *q)
{
    return q->front == NULL;
}

void enqueue(Queue *q, int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return;
    }

    newNode->data = val;
    newNode->next = NULL;

    if (isEmpty(q))
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Underflow.\n");
        return -1;
    }

    Node *temp = q->front;
    int val = temp->data;

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);

    return val;
}

int peek(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Empty.\n");
        return -1;
    }

    return q->front->data;
}

void printQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Empty.\n");
        return;
    }

    Node *temp = q->front;

    printf("Front = ");

    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("= Rear\n");
}

void createQueue(Queue arr[], int n)
{
    arr[n].front = NULL;
    arr[n].rear = NULL;
}

void appendQueue(Queue *y, Queue *x)
{
    if (isEmpty(x))
    {
        printf("Source Queue Empty.\n");
        return;
    }

    if (isEmpty(y))
    {
        y->front = x->front;
        y->rear = x->rear;
    }
    else
    {
        y->rear->next = x->front;
        y->rear = x->rear;
    }

    x->front = NULL;
    x->rear = NULL;

    printf("Queue Appended Successfully.\n");
}

bool eq(Queue *q1, Queue *q2)
{
    Node *p = q1->front;
    Node *q = q2->front;

    while (p != NULL && q != NULL)
    {
        if (p->data != q->data)
            return false;

        p = p->next;
        q = q->next;
    }

    return (p == NULL && q == NULL);
}

void reverseQueue(Queue *q)
{
    if (isEmpty(q))
        return;

    Node *prev = NULL;
    Node *curr = q->front;
    Node *next = NULL;

    q->rear = q->front;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    q->front = prev;

    printf("Queue Reversed Successfully.\n");
}

void replace(Queue *q, int e, int x)
{
    Node *temp = q->front;

    while (temp != NULL)
    {
        if (temp->data == e)
            temp->data = x;

        temp = temp->next;
    }

    printf("Replacement Done.\n");
}

int main()
{
    Queue arr[QUEUE_COUNT];

    int size = 1;
    int current = 0;

    createQueue(arr, 0);

    int ch, val;
    bool running = true;

    while (running)
    {
        printf("\n============================\n");
        printf("Current Queue : %d\n", current);
        printf("Total Queues  : %d\n", size);
        printf("============================\n");

        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Print\n");
        printf("5. Create Queue\n");
        printf("6. Switch Queue\n");
        printf("7. Append Queue X to Y\n");
        printf("8. Compare Queues\n");
        printf("9. Reverse Queue\n");
        printf("10. Replace\n");
        printf("11. Exit\n");
        printf(">>> ");

        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Value : ");
            scanf("%d", &val);
            enqueue(&arr[current], val);
            break;

        case 2:
            printf("Deleted : %d\n",
                   dequeue(&arr[current]));
            break;

        case 3:
            printf("Front : %d\n",
                   peek(&arr[current]));
            break;

        case 4:
            printQueue(&arr[current]);
            break;

        case 5:
            if (size >= QUEUE_COUNT)
            {
                printf("Maximum Queue Limit Reached.\n");
                break;
            }

            createQueue(arr, size);
            printf("Queue %d Created.\n", size);
            size++;
            break;

        case 6:
            printf("Queue Number (0-%d): ",
                   size - 1);
            scanf("%d", &val);

            if (val >= 0 && val < size)
                current = val;
            else
                printf("Invalid Queue.\n");

            break;

        case 7:
        {
            int x, y;

            printf("Source Queue X : ");
            scanf("%d", &x);

            printf("Destination Queue Y : ");
            scanf("%d", &y);

            if (x >= 0 && x < size &&
                y >= 0 && y < size)
            {
                appendQueue(&arr[y], &arr[x]);
            }

            break;
        }

        case 8:
        {
            int q1, q2;

            printf("Queue 1 : ");
            scanf("%d", &q1);

            printf("Queue 2 : ");
            scanf("%d", &q2);

            if (eq(&arr[q1], &arr[q2]))
                printf("Queues are Equal.\n");
            else
                printf("Queues are Not Equal.\n");

            break;
        }

        case 9:
            reverseQueue(&arr[current]);
            break;

        case 10:
        {
            int p, e, x;

            printf("Queue Number : ");
            scanf("%d", &p);

            printf("Element : ");
            scanf("%d", &e);

            printf("New Value : ");
            scanf("%d", &x);

            replace(&arr[p], e, x);

            break;
        }

        case 11:
            running = false;
            break;

        default:
            printf("Wrong Input.\n");
        }
    }

    return 0;
}