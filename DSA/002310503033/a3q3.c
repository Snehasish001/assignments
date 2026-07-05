#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 30

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
    for (int i = MAX - 1; i >= 0; i--) {
        printf("| %d |\n-----\n", stack[i]);
    }
}


int main() {
    FILE *fp;
    int num;


    fp = fopen("data.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    while (fscanf(fp, "%d", &num) == 1) {
        push(num);
    }

    fclose(fp);

    printf("Numbers in reverse order:\n");

    while (!isEmpty()) {
        printf("%d ", pop());
    }

    printf("\n");

    return 0;
}