#include <stdio.h>
#include <stdbool.h>

#define MAX 5

int front = -1, rear = -1;
int queue[MAX];


bool isEmpty()
{
    return front == -1;
}

bool isFull()
{
    return (rear + 1) % MAX == front;
}

void enqueue(int val)
{
    if (isFull()) {
        printf("Overflow\n");
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    queue[rear] = val;
    printf("Element Added\n");
}

int dequeue()
{
    if (isEmpty()) {
        printf("Underflow\n");
        return -1;
    }

    int val = queue[front];

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }

    return val;
}

int peek()
{
    if (isEmpty()) {
        printf("Queue Empty\n");
        return -1;
    }

    return queue[front];
}

void display()
{
    if (isEmpty()) {
        printf("Queue Empty\n");
        return;
    }

    printf("Front = ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }

    printf("= Rear\n");
}

int main()
{
    int ch, val;
    bool running = true;

    while (running)
    {
        printf("\n----------------------------------\n");
        printf("         Circular Queue\n");
        printf("----------------------------------\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf(">>> ");

        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter Value : ");
            scanf("%d", &val);

            enqueue(val);
            break;

        case 2:
            val = dequeue();

            if (val != -1) printf("Dequeued : %d\n", val);
            break;

        case 3:
            val = peek();

            if (val != -1) printf("Front Element : %d\n", val);
            break;

        case 4:
            display();
            break;

        case 5:
            running = false;
            break;

        default:
        {
            printf("Wrong Input\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
        }
    }

    return 0;
}