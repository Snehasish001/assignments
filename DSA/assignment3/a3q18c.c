#include <stdio.h>
#include <stdbool.h>

#define PRIORITY 10
#define SIZE 10

int queue[PRIORITY][SIZE];
int rear[PRIORITY];

void init()
{
    for(int i=0;i<PRIORITY;i++)
        rear[i]=-1;
}

bool isEmpty()
{
    for(int i=0;i<PRIORITY;i++)
        if(rear[i]!=-1)
            return false;

    return true;
}

void enqueue(int val,int priority)
{
    if(rear[priority]==SIZE-1)
    {
        printf("Overflow\n");
        return;
    }

    rear[priority]++;

    queue[priority][rear[priority]]=val;

    printf("Enqueued Successfully.\n");
}

int peek()
{
    if(isEmpty())
    {
        printf("Underflow\n");
        return -1;
    }

    for(int i=PRIORITY-1;i>=0;i--)
    {
        if(rear[i]!=-1)
            return queue[i][0];
    }

    return -1;
}

int dequeue()
{
    if(isEmpty())
    {
        printf("Underflow\n");
        return -1;
    }

    for(int i=PRIORITY-1;i>=0;i--)
    {
        if(rear[i]!=-1)
        {
            int temp=queue[i][0];

            for(int j=0;j<rear[i];j++)
                queue[i][j]=queue[i][j+1];

            rear[i]--;

            return temp;
        }
    }

    return -1;
}

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

        for(int j=0;j<=rear[i];j++)
            printf("%d ",queue[i][j]);

        printf("\n");
    }
}