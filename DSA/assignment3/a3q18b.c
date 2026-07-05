#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    int priority;
    struct Node *next;
} Node;

Node *front = NULL;

bool isEmpty()
{
    return front == NULL;
}

void enqueue(int val, int priority)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Overflow (Memory Allocation Failed)\n");
        return;
    }

    newNode->val = val;
    newNode->priority = priority;
    
    newNode->next = front;
    front = newNode;

    printf("Enqueued Successfully.\n");
}

Node peek()
{
    Node temp = {-1, -1, NULL};

    if (isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    Node *ptr = front;
    Node *max = front;

    while (ptr != NULL)
    {
        if (ptr->priority > max->priority)
        {
            max = ptr;
        }
        ptr = ptr->next;
    }

    temp.val = max->val;
    temp.priority = max->priority;

    return temp;
}

Node dequeue()
{
    Node temp = {-1, -1, NULL};

    if (isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    Node *ptr = front;
    Node *prev = NULL;

    Node *max = front;
    Node *maxPrev = NULL;

    while (ptr != NULL)
    {
        if (ptr->priority > max->priority)
        {
            max = ptr;
            maxPrev = prev;
        }
        prev = ptr;
        ptr = ptr->next;
    }

    temp.val = max->val;
    temp.priority = max->priority;

    if (maxPrev == NULL)
    {
        front = front->next;
    }
    else
    {
        maxPrev->next = max->next; 
    }

    free(max);
    return temp;
}

void display()
{
    if (isEmpty())
    {
        printf("Queue Empty\n");
        return;
    }

    Node *ptr = front;

    printf("Front = ");
    while (ptr != NULL)
    {
        printf("[%d|%d] ", ptr->val, ptr->priority);
        ptr = ptr->next;
    }
    printf("= Rear\n");
}

int main()
{
    srand(time(NULL));
    int ch;
    int val;
    int priority;
    Node temp;

    while (1)
    {
        printf("\n-------------------------\n");
        printf("    Priority Queue (List)\n");
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
            priority = rand() % 10;
            printf("Enter Value : %d\n", val);
            printf("Enter Priority : %d\n", priority);

            enqueue(val, priority);
            display();
            break;

        case 2:
            temp = dequeue();

            if (temp.val != -1)
            {
                printf("Dequeued : [%d | %d]\n",
                       temp.val,
                       temp.priority);
            }
            display();
            break;

        case 3:
            temp = peek();

            if (temp.val != -1)
            {
                printf("Highest Priority Element : [%d | %d]\n",
                       temp.val,
                       temp.priority);
            }
            display();
            break;

        default:
            printf("Program terminating ... \n");
            return 0;
        }
    }
}