#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 10

int stack[MAX];
int top = -1;

bool isEmpty() {
    return top == -1;
}

bool isFull() {
    return top == MAX - 1;
}

void push(int val) {
    if (isFull()) {
        printf("Overflow.\n");
        return;
    } 
    top++;
    stack[top] = val;
    printf("Insertion successfull.\n");
}

int pop() {
    if (isEmpty()) {
        printf("Underflow.\n");
        return 0;
    }
    int val = stack[top];
    stack[top] = 0;
    top--;
    return val;
}

int peek() {
    if (isEmpty()) {
        printf("Underflow.\n");
        return 0;
    }
    return stack[top];
}

void print() {
    printf("STACK TOP : ");
    for (int i = top; i >= 0; i--) {
        printf(" %d ", stack[i]);
    }
    printf("\n");
}

int main() {
    int ch, val;
    bool f = true;
    do {
        printf("Press\n1. push\n2. pop\n3. peek\n4. print\n5. exit\n>>> ");
        scanf("%d",&ch);

        switch (ch)
        {
        case 1:
            printf("Enter the value : ");
            scanf("%d",&val);
            push(val);
            print();
            break;
        
        case 2:
            val = pop();
            if (val != 0) printf("Pop : %d\n", val);
            print();
            break;

        case 3:
            val = peek();
            if (val != 0) printf("Peek : %d\n", val);
            print();
            break;
        
        case 4:
            print();
            break;

        case 5:
            f = false;
            break;

        default:
            printf("Wrong Input.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            break;
        }
    } while (f);
}