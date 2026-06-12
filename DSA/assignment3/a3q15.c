#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue{
    int val;
    struct Queue *next;
}Queue;

Queue *front = NULL;
Queue *rear = NULL;

bool isEmpty() {
    return front == NULL;
}

void eq(int val) {
    Queue n = (Queue*)malloc(sizeof(Queue));
    n->val = val;
    n->next = NULL;

    if (front == NULL && rear == NULL) {
        front = n;
        rear = n;
    } else {
        n->next = rear;
        rear = n;
    }
}

Queue deq() {
    if (isEmpty()) {
        printf("Queue is Empty.\n");
        return;
    }
    Queue *n = front;
    if (front == rear) {
        front = NULL;
        rear = NULL;
    } else {
        Queue *t = rear;
        while (t->next != front) {
            t = t->next;
        }
        front = t;
        t->next = NULL;
    }
    return n;
}


void display() {
    
}

int main() {

    return 0;
}