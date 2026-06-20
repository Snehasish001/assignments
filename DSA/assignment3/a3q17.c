#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


typedef struct node {
    int val;
    struct node *prev;
    struct node *next;
}node;

node *front = NULL;
node *rear = NULL;

void eq(int val, int ch) {
    node *newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed. Retry\n");
        return;  
    }
    newNode->val = val;
    if (front == NULL && rear == NULL) {
        newNode->next = NULL;
        newNode->prev = NULL;
        front = newNode;
        rear = newNode;
        return;
    } 

    if (ch == 0) {
        newNode->next = front;
        front->prev = newNode;
        newNode->prev = NULL;
        front = newNode;
    } else {
        rear->next = newNode;
        newNode->prev = rear;
        newNode->next = NULL;
        rear = newNode;
    }
    printf("Enqueue done\n");
}

int dq(int ch) {
    if (front == NULL && rear == NULL) {
        printf("Underflow");
        return -1;
    }
    int val;
    if (ch == 0) {
        val = front->val;
        if (front->next == NULL) {
            front = NULL;
            rear = NULL;
        } else {
            front = front->next;
            front->prev = NULL;
        }
    } else {
        val = rear->val;
        if (rear->prev == NULL) {
            rear = NULL;
            front = NULL;
        } else {
            rear = rear->prev;
            rear->next = NULL;
        }
    }
    return val;
}


void dis(int ch) {
    if (front == NULL && rear == NULL) {
        printf("Queue is empty\n");
        return;
    }
    if (ch == 0) {
        node *temp = front;
        while (temp != NULL) {
            printf("[%p | %d | %p] -> ", temp->prev, temp->val, temp->next);
            temp = temp->next;
        }
    } else {
        node *temp = rear;
        while (temp != NULL) {
            printf("[%p | %d | %p] -> ", temp->next, temp->val, temp->prev);
            temp = temp->prev;
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    int ch, val;
    bool f = true;
    int i = (rand() % 20) + 1;
    while (f) {
        if ((i--) == 0) {
            ch = 3;
        } else {
            ch = (rand() % 2) + 1;
        }
        printf("\n------------------------\n");
        printf("         Queue          \n");
        printf("------------------------\n");
        printf("1. enqueue\n");
        printf("2. dequeu\n");
        printf("3. exit\n>>>  %d\n",ch);

        switch (ch) {
            case 1:
                val = (rand() % 99) + 1;
                eq(val, 0);
                dis(0);
                dis(1);
                break;
            case 2:
                val = dq(1);
                if (val != -1) {
                    printf("Removed : %d\n", val);
                    dis(0);
                    dis(1);
                }
                break;
            default:
                f = false;
                break;

        }
    }
}