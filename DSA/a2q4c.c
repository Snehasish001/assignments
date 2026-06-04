#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
}Node;

Node* createCDLL(int n)
{
    Node *head=NULL,*last=NULL,*newNode;

    for(int i=1;i<=n;i++)
    {
        newNode=(Node*)malloc(sizeof(Node));

        newNode->data=i;

        if(head==NULL)
        {
            head=newNode;
            last=newNode;
        }
        else
        {
            last->next=newNode;
            newNode->prev=last;
            last=newNode;
        }
    }

    head->prev=last;
    last->next=head;

    return head;
}

int josephusCDLL(int n,int k)
{
    Node* ptr=createCDLL(n);

    int count=n;

    while(count>1)
    {
        for(int i=1;i<k;i++)
            ptr=ptr->next;

        printf("Executed: %d\n",ptr->data);

        ptr->prev->next=ptr->next;
        ptr->next->prev=ptr->prev;

        Node* del=ptr;

        ptr=ptr->next;

        free(del);

        count--;
    }

    int survivor=ptr->data;

    free(ptr);

    return survivor;
}

int main()
{
    int n,k;

    printf("Enter n: ");
    scanf("%d",&n);

    printf("Enter k: ");
    scanf("%d",&k);

    printf("Freed Person = %d\n",josephusCDLL(n,k));

    return 0;
}