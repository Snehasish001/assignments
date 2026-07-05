#include <stdio.h>
#include <stdbool.h>

#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

bool isEmpty()
{
    return front == -1;
}

bool isFull()
{
    return rear == MAX - 1;
}

void enqueue(int val)
{
    if (isFull())
    {
        printf("Queue Overflow\n");
        return;
    }

    if (isEmpty())
        front = 0;

    queue[++rear] = val;

    printf("%d inserted successfully.\n", val);
}

int dequeue()
{
    if (isEmpty())
    {
        printf("Queue Underflow\n");
        return -1;
    }

    int val = queue[front];

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }

    return val;
}

int peek()
{
    if (isEmpty())
    {
        printf("Queue Empty\n");
        return -1;
    }

    return queue[front];
}

void display()
{
    if (isEmpty())
    {
        printf("Queue Empty\n");
        return;
    }

    printf("Queue: ");

    for (int i = front; i <= rear; i++)
    {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

int main()
{
    int ch, val;

    do
    {
        printf("\n===== QUEUE USING ARRAY =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &val);
                enqueue(val);
                break;

            case 2:
                val = dequeue();
                if (val != -1)
                    printf("Deleted Element: %d\n", val);
                break;

            case 3:
                val = peek();
                if (val != -1)
                    printf("Front Element: %d\n", val);
                break;

            case 4:
                display();
                break;

            case 5:
                printf("Program Terminated.\n");
                break;

            default:
                printf("Invalid Choice.\n");
        }

    } while (ch != 5);

    return 0;
}