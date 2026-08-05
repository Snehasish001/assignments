#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define PRIORITY 10
#define SIZE 10

int queue[PRIORITY][SIZE];
int rear[PRIORITY];

void init() {
    for(int i = 0; i < PRIORITY; i++)
        rear[i] = -1;
}

bool isEmpty() {
    for(int i = 0; i < PRIORITY; i++)
        if(rear[i] != -1)
            return false;

    return true;
}

void enqueue(int val, int priority) {
    if (priority < 0 || priority >= PRIORITY) {
        printf("Invalid Priority Level\n");
        return;
    }

    if(rear[priority] == SIZE - 1) {
        printf("Overflow\n");
        return;
    }

    rear[priority]++;
    queue[priority][rear[priority]] = val;

    printf("Enqueued Successfully.\n");
}

int peek() {
    if(isEmpty()) {
        printf("Underflow\n");
        return -1;
    }

    for(int i = PRIORITY - 1; i >= 0; i--) {
        if(rear[i] != -1)
            return queue[i][0];
    }

    return -1;
}

int dequeue() {
    if(isEmpty()) {
        printf("Underflow\n");
        return -1;
    }

    for(int i = PRIORITY - 1; i >= 0; i--) {
        if(rear[i] != -1) {
            int temp = queue[i][0];

            for(int j = 0; j < rear[i]; j++)
                queue[i][j] = queue[i][j + 1];

            rear[i]--;

            return temp;
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
        if (rear[i] != -1) {
            printf("\nPriority %d : ", i);
            for(int j = 0; j <= rear[i]; j++)
                printf("[%d] ", queue[i][j]);
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

    while (1)
    {
        printf("\n-------------------------\n");
        printf("  Priority Queue (2D Array)\n");
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