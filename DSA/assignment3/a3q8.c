#include <stdio.h>
#include <stdbool.h>

#define MAX 100

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

void push(char ch)
{
    if (isFull())
    {
        printf("Stack Overflow\n");
        return;
    }

    stack[++top] = ch;
}

char pop()
{
    if (isEmpty())
    {
        return '\0';
    }

    return stack[top--];
}

char peek()
{
    if (isEmpty())
        return '\0';

    return stack[top];
}

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isBalanced(char exp[])
{
    int i = 0;

    while (exp[i] != '\0')
    {
        char ch = exp[i];

        if (ch == '(' || ch == '{' || ch == '[')
        {
            push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (isEmpty())
                return false;

            char open = pop();

            if (!isMatching(open, ch))
                return false;
        }

        i++;
    }

    return isEmpty();
}

int main()
{
    char exp[100];

    printf("Enter Expression: ");
    scanf("%s", exp);

    if (isBalanced(exp))
        printf("Balanced Expression\n");
    else
        printf("Not Balanced Expression\n");

    return 0;
}