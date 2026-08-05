#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 30

char stack[MAX];
int top = -1;


bool isEmpty()
{
    return top == -1;
}

bool isFull()
{
    return top == MAX - 1;
}

void push(char val)
{
    if (isFull())
    {
        printf("Stack Overflow.\n");
        return;
    }

    stack[++top] = val;
}

char pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow.\n");
        return '\0';
    }

    return stack[top--];
}

char peek()
{
    if (isEmpty())
    {
        return '\0';
    }

    return stack[top];
}

int precedence(char op)
{
    switch (op)
    {
        case '^':
            return 3;

        case '*':
        case '/':
        case '%':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}

void infixToPostfix(char infix[], char postfix[])
{
    int i = 0;
    int j = 0;
    char ch;

    while ((ch = infix[i]) != '\0')
    {
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }

        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (!isEmpty() && peek() != '(')
            {
                postfix[j++] = pop();
            }

            if (!isEmpty() && peek() == '(')
            {
                pop(); 
            }
        }

        else
        {
            while (!isEmpty() &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }

        i++;
    }

    while (!isEmpty())
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}


int main()
{
    char infix[100];
    char postfix[100];

    printf("Enter Infix Expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Infix   : %s\n", infix);
    printf("Postfix : %s\n", postfix);

    return 0;
}