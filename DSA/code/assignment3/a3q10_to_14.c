#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 10
#define QUEUE_COUNT 10

typedef struct Queue
{
    int queue[MAX];
    int front;
    int rear;
} Queue;


bool isEmpty(Queue *q)
{
    return q->front == -1;
}

bool isFull(Queue *q)
{
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int val)
{
    if (isFull(q))
    {
        printf("Overflow.\n");
        return;
    }

    if (isEmpty(q))
        q->front = 0;

    q->queue[++q->rear] = val;
}

int dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Underflow.\n");
        return INT_MIN;
    }

    int val = q->queue[q->front];

    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;

    return val;
}

int peek(Queue *q)
{
    if (isEmpty(q))
        return INT_MIN;

    return q->queue[q->front];
}

void printQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Empty.\n");
        return;
    }

    printf("Front = ");

    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->queue[i]);

    printf("= Rear\n");
}

void createQueue(Queue arr[], int n)
{
    arr[n].front = -1;
    arr[n].rear = -1;

    for (int i = 0; i < MAX; i++)
        arr[n].queue[i] = 0;
}



void appendQueue(Queue *y, Queue *x)
{
    while (!isEmpty(x))
    {
        if (isFull(y))
        {
            printf("Queue Y Overflow.\n");
            return;
        }

        enqueue(y, dequeue(x));
    }

    printf("Queue Appended Successfully.\n");
}

/* Equality Function */

bool eq(Queue *q1, Queue *q2)
{
    int size1 = 0;
    int size2 = 0;

    if (isEmpty(q1) && isEmpty(q2))
        return true;

    if (isEmpty(q1) || isEmpty(q2))
        return false;

    size1 = q1->rear - q1->front + 1;
    size2 = q2->rear - q2->front + 1;

    if (size1 != size2)
        return false;

    int i = q1->front;
    int j = q2->front;

    while (i <= q1->rear)
    {
        if (q1->queue[i] != q2->queue[j])
            return false;

        i++;
        j++;
    }

    return true;
}

/* Reverse Queue */

void reverseQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Empty.\n");
        return;
    }

    int temp[MAX];
    int count = 0;

    for (int i = q->front; i <= q->rear; i++)
        temp[count++] = q->queue[i];

    int left = 0;
    int right = count - 1;

    while (left < right)
    {
        int t = temp[left];
        temp[left] = temp[right];
        temp[right] = t;

        left++;
        right--;
    }

    q->front = 0;
    q->rear = count - 1;

    for (int i = 0; i < count; i++)
        q->queue[i] = temp[i];

    printf("Queue Reversed Successfully.\n");
}


void replace(Queue *q, int e, int x) {
    if (isEmpty(q)) {
        printf("Queue Empty.\n");
        return;
    }

    for (int i = q->front; i <= q->rear; i++) {
        if (q->queue[i] == e) {
            q->queue[i] = x;
        }
    }
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
        printf("\n=================================\n");
        printf("Current Queue : %d\n", current);
        printf("Total Queues  : %d\n", size);
        printf("=================================\n");

        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Print\n");
        printf("5. Create Queue\n");
        printf("6. Switch Queue\n");
        printf("7. Append Queue X to Y\n");
        printf("8. Compare Two Queues\n");
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
                val = dequeue(&arr[current]);

                if (val != INT_MIN)
                    printf("Deleted : %d\n", val);

                break;

            case 3:
                val = peek(&arr[current]);

                if (val != INT_MIN)
                    printf("Front : %d\n", val);

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
                printf("Enter Queue Number (0-%d): ", size - 1);
                scanf("%d", &val);

                if (val >= 0 && val < size)
                    current = val;
                else
                    printf("Invalid Queue Number.\n");

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
                printf("Enter the queue : ");
                scanf("%d",&p);

                printf("Enter the value : ");
                scanf("%d",&e);

                printf("Enter the new value : ");
                scanf("%d",&x);

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