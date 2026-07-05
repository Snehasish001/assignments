#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

Node *top = NULL;


void push(int val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return;
    }

    newNode->val = val;
    newNode->next = top;
    top = newNode;
}


Node *pop()
{
    if (top == NULL)
    {
        printf("Stack Underflow.\n");
        return NULL;
    }

    Node *temp = top;
    top = top->next;
    temp->next = NULL;

    return temp;
}


Node *peek()
{
    return top;
}


void display()
{
    if (top == NULL)
    {
        printf("Stack Empty.\n");
        return;
    }

    Node *temp = top;

    printf("\n");
    while (temp != NULL)
    {
        printf("-------\n");
        printf("|  %d  |\n", temp->val);
        temp = temp->next;
    }
    printf("-------\n");
}


void freeStack()
{
    Node *temp;

    while (top != NULL)
    {
        temp = top;
        top = top->next;
        free(temp);
    }
}

int main()
{
    int ch, val;
    bool running = true;
    Node *t;

    while (running)
    {
        printf("\n===== STACK USING LINKED LIST =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter Choice : ");

        if (scanf("%d", &ch) != 1)
        {
            printf("Invalid Input.\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue;
        }

        switch (ch)
        {
        case 1:
            printf("Enter Value : ");
            scanf("%d", &val);

            push(val);

            printf("After Push:\n");
            display();
            break;

        case 2:
            t = pop();

            if (t != NULL)
            {
                printf("Popped Element : %d\n", t->val);
                free(t);
            }
            break;

        case 3:
            t = peek();

            if (t != NULL)
                printf("Top Element : %d\n", t->val);
            else
                printf("Stack Empty.\n");

            break;

        case 4:
            display();
            break;

        case 5:
            running = false;
            freeStack();
            printf("Program Terminated.\n");
            break;

        default:
            printf("Wrong Choice.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }

    return 0;
}