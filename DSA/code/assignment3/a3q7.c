#include <stdio.h>
#include <ctype.h>

#define MAX 30

int stack[MAX];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(int val)
{
    if (isFull())
    {
        printf("Stack Overflow\n");
        return;
    }

    stack[++top] = val;
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return stack[top--];
}

int evaluatePostfix(char exp[])
{
    int i = 0;

    while (exp[i] != '\0')
    {
        char ch = exp[i];

        if (isdigit(ch))
        {
            push(ch - '0');
        } 
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            int val1 = pop();
            int val2 = pop();

            switch (ch)
            {
                case '+':
                    push(val2 + val1);
                    break;

                case '-':
                    push(val2 - val1);
                    break;

                case '*':
                    push(val2 * val1);
                    break;

                case '/':
                    push(val2 / val1);
                    break;
            }
        }

        i++;
    }

    return pop();
}

int main()
{
    char postfix[100];

    printf("Enter Postfix Expression: ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);

    printf("Result = %d\n", result);

    return 0;
}