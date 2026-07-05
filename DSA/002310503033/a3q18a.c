#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX 10

typedef struct
{
    int val;
    int priority;
} Node;

Node queue[MAX];
int front = -1;
int rear = -1;

/* Utility Functions */

bool isEmpty()
{
    return front == -1;
}

bool isFull()
{
    return rear == MAX - 1;
}

/* Enqueue */

void enqueue(int val, int priority)
{
    if (isFull())
    {
        printf("Overflow\n");
        return;
    }

    if (isEmpty())
    {
        front = rear = 0;
    }
    else
    {
        rear++;
    }

    queue[rear].val = val;
    queue[rear].priority = priority;

    printf("Enqueued Successfully.\n");
}

/* Peek Highest Priority */

Node peek()
{
    Node temp = {-1, -1};

    if (isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    int maxIndex = front;

    for (int i = front + 1; i <= rear; i++)
    {
        if (queue[i].priority > queue[maxIndex].priority)
        {
            maxIndex = i;
        }
    }

    return queue[maxIndex];
}

/* Dequeue Highest Priority */

Node dequeue()
{
    Node temp = {-1, -1};

    if (isEmpty())
    {
        printf("Underflow\n");
        return temp;
    }

    int maxIndex = front;

    for (int i = front + 1; i <= rear; i++)
    {
        if (queue[i].priority > queue[maxIndex].priority)
        {
            maxIndex = i;
        }
    }

    temp = queue[maxIndex];

    for (int i = maxIndex; i < rear; i++)
    {
        queue[i] = queue[i + 1];
    }

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        rear--;
    }

    return temp;
}

/* Display */

void display()
{
    if (isEmpty())
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Front = ");

    for (int i = front; i <= rear; i++)
    {
        printf("[%d|%d] ",
               queue[i].val,
               queue[i].priority);
    }

    printf("= Rear\n");
}

/* Main */

int main()
{
    srand(time(NULL));
    int ch;
    int val;
    int priority;
    Node temp;
    int i = 30;
    while (1)
    {
        i--;
        if (i == 0) {
            ch = 4;
        } else {
            ch = (rand() % 3) + 1;
        }
        printf("\n-------------------------\n");
        printf("      Priority Queue\n");
        printf("-------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Exit\n");
        printf(">>>  %d\n", ch);

        switch (ch)
        {
        case 1:
            val = rand() % 100;
            priority = rand() % 10;
            printf("Enter Value : %d\n");
            printf("Enter Priority : %d\n");

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
            printf("Wrong Input\n");
            return 0;
        }
    }
}