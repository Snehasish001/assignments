#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

Node* createCircle(int n)
{
    Node *head=NULL,*temp,*newNode;

    for(int i=1;i<=n;i++)
    {
        newNode=(Node*)malloc(sizeof(Node));

        newNode->data=i;
        newNode->next=NULL;

        if(head==NULL)
        {
            head=newNode;
            temp=newNode;
        }
        else
        {
            temp->next=newNode;
            temp=newNode;
        }
    }

    temp->next=head;

    return head;
}

int josephusCLL(int n,int k)
{
    Node* head=createCircle(n);

    Node *ptr=head;
    Node *prev=NULL;

    while(ptr->next!=ptr)
    {
        for(int i=1;i<k;i++)
        {
            prev=ptr;
            ptr=ptr->next;
        }

        printf("Executed: %d\n",ptr->data);

        prev->next=ptr->next;

        Node* del=ptr;

        ptr=ptr->next;

        free(del);
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

    printf("Freed Person = %d\n",josephusCLL(n,k));

    return 0;
}