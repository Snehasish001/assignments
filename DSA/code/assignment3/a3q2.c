#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 10          
#define STACK_COUNT 10  

typedef struct stack {
    int stack[MAX];
    int top;
} stack;

bool isEmpty(stack *s) {
    return s->top == -1;
}

bool isFull(stack *s) {
    return s->top == MAX - 1;
}

void push(stack *s, int val) {
    if (isFull(s)) {
        printf("Overflow.\n");
        return;
    }

    s->stack[++(s->top)] = val;
    printf("Insertion successful.\n");
}

int pop(stack *s) {
    if (isEmpty(s)) {
        printf("Underflow.\n");
        return INT_MIN;
    }

    int val = s->stack[s->top];
    s->stack[s->top] = 0;
    s->top--;

    return val;
}

int peek(stack *s) {
    if (isEmpty(s)) {
        printf("Underflow.\n");
        return INT_MIN;
    }

    return s->stack[s->top];
}

void print(stack *s) {
    printf("STACK TOP : ");
    for (int i = s->top; i >= 0; i--) {
        printf(" %d ", s->stack[i]);
    }
    printf("\n");
}

void create(stack arr[], int n) {
    arr[n].top = -1;

    for (int i = 0; i < MAX; i++) {
        arr[n].stack[i] = 0;
    }
}

int main() {
    int ch, val;
    bool f = true;

    stack arr[STACK_COUNT];

    int size = 1;  
    int n = 0;     

    create(arr, 0);

    do {
        printf("\n=================================\n");
        printf("Current Stack : %d\n", n);
        printf("Total Stacks  : %d\n", size);
        printf("=================================\n");

        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Print\n");
        printf("5. Create New Stack\n");
        printf("6. Switch Stack\n");
        printf("7. Exit\n");
        printf(">>> ");

        scanf("%d", &ch);

        switch (ch) {

        case 1:
            printf("Enter value : ");
            scanf("%d", &val);

            push(&arr[n], val);
            break;

        case 2:
            val = pop(&arr[n]);

            if (val != INT_MIN)
                printf("Popped : %d\n", val);

            break;

        case 3:
            val = peek(&arr[n]);

            if (val != INT_MIN)
                printf("Top Element : %d\n", val);

            break;

        case 4:
            print(&arr[n]);
            break;

        case 5:
            if (size >= STACK_COUNT) {
                printf("Maximum stack limit reached.\n");
                break;
            }

            create(arr, size);

            printf("Stack %d created successfully.\n", size);

            size++;
            n = size - 1;
            break;

        case 6:
            printf("Available stacks: 0 to %d\n", size - 1);
            printf("Enter stack number : ");
            scanf("%d", &val);

            if (val >= 0 && val < size) {
                n = val;
                printf("Switched to stack %d.\n", n);
            } else {
                printf("Invalid stack number.\n");
            }

            break;

        case 7:
            f = false;
            break;

        default:
            printf("Wrong Input.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            break;
        }

    } while (f);

    printf("Program terminated.\n");

    return 0;
}