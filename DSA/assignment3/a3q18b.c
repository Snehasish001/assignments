#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    int priority;
    struct Node *next;
} Node;

Node *front = NULL;

/* Utility */

bool isEmpty()
{
    return front == NULL;
}

/* Enqueue */

void enqueue(int val, int priority)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->val = val;
    newNode->priority = priority;
    newNode->next = front;

    front = newNode;

    printf("Enqueued Successfully.\n");
}

/* Peek */

Node peek()
{
    Node temp = {-1,-1,NULL};

    if(isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    Node *ptr = front;
    Node *max = front;

    while(ptr!=NULL)
    {
        if(ptr->priority > max->priority)
            max = ptr;

        ptr = ptr->next;
    }

    temp.val = max->val;
    temp.priority = max->priority;

    return temp;
}

/* Dequeue */

Node dequeue()
{
    Node temp = {-1,-1,NULL};

    if(isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    Node *ptr = front;
    Node *prev = NULL;

    Node *max = front;
    Node *maxPrev = NULL;

    while(ptr!=NULL)
    {
        if(ptr->priority > max->priority)
        {
            max = ptr;
            maxPrev = prev;
        }

        prev = ptr;
        ptr = ptr->next;
    }

    temp.val = max->val;
    temp.priority = max->priority;

    if(maxPrev==NULL)
        front = front->next;
    else
        maxPrev->next = max->next;

    free(max);

    return temp;
}

/* Display */

void display()
{
    if(isEmpty())
    {
        printf("Queue Empty\n");
        return;
    }

    Node *ptr = front;

    printf("Front = ");

    while(ptr)
    {
        printf("[%d|%d] ",ptr->val,ptr->priority);
        ptr=ptr->next;
    }

    printf("= Rear\n");
}