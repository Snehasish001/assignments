#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PRIORITY 10

typedef struct Node
{
    int val;
    struct Node *next;
}Node;

Node *front[PRIORITY];

/* Utility */

void init()
{
    for(int i=0;i<PRIORITY;i++)
        front[i]=NULL;
}

bool isEmpty()
{
    for(int i=0;i<PRIORITY;i++)
        if(front[i]!=NULL)
            return false;

    return true;
}

/* Enqueue */

void enqueue(int val,int priority)
{
    Node *newNode=(Node*)malloc(sizeof(Node));

    newNode->val=val;
    newNode->next=NULL;

    if(front[priority]==NULL)
    {
        front[priority]=newNode;
    }
    else
    {
        Node *ptr=front[priority];

        while(ptr->next)
            ptr=ptr->next;

        ptr->next=newNode;
    }

    printf("Enqueued Successfully.\n");
}

/* Peek */

int peek()
{
    if(isEmpty())
    {
        printf("Underflow\n");
        return -1;
    }

    for(int i=PRIORITY-1;i>=0;i--)
    {
        if(front[i]!=NULL)
            return front[i]->val;
    }

    return -1;
}

/* Dequeue */

int dequeue()
{
    if(isEmpty())
    {
        printf("Underflow\n");
        return -1;
    }

    for(int i=PRIORITY-1;i>=0;i--)
    {
        if(front[i]!=NULL)
        {
            Node *temp=front[i];

            int val=temp->val;

            front[i]=front[i]->next;

            free(temp);

            return val;
        }
    }

    return -1;
}

/* Display */

void display()
{
    if(isEmpty())
    {
        printf("Queue Empty\n");
        return;
    }

    printf("\n");

    for(int i=PRIORITY-1;i>=0;i--)
    {
        printf("Priority %d : ",i);

        Node *ptr=front[i];

        while(ptr)
        {
            printf("%d ",ptr->val);
            ptr=ptr->next;
        }

        printf("\n");
    }
}