#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define MAX 199

void sort(int a[], int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
}

void SCAN(int req[], int n, int head)
{
    int a[20];

    for(int i=0;i<n;i++)
        a[i]=req[i];

    sort(a,n);

    int pos=0;

    while(pos<n && a[pos]<head)
        pos++;

    int seek=0,temp=head;

    // Move towards higher cylinders
    for(int i=pos;i<n;i++)
    {
        seek+=abs(a[i]-temp);
        temp=a[i];
    }

    if(temp!=MAX)
    {
        seek+=abs(MAX-temp);
        temp=MAX;
    }

    // Reverse direction
    for(int i=pos-1;i>=0;i--)
    {
        seek+=abs(temp-a[i]);
        temp=a[i];
    }

    printf("SCAN  : Total Seek=%d  Avg=%.2f\n",
            seek,(float)seek/n);
}

void CSCAN(int req[], int n, int head)
{
    int a[20];

    for(int i=0;i<n;i++)
        a[i]=req[i];

    sort(a,n);

    int pos=0;

    while(pos<n && a[pos]<head)
        pos++;

    int seek=0,temp=head;

    for(int i=pos;i<n;i++)
    {
        seek+=abs(a[i]-temp);
        temp=a[i];
    }

    if(temp!=MAX)
    {
        seek+=MAX-temp;
        temp=MAX;
    }

    seek+=MAX;
    temp=0;

    for(int i=0;i<pos;i++)
    {
        seek+=abs(a[i]-temp);
        temp=a[i];
    }

    printf("CSCAN : Total Seek=%d  Avg=%.2f\n",
            seek,(float)seek/n);
}

void randomList(int a[])
{
    for(int i=0;i<N;i++)
        a[i]=rand()%200;
}

void endList(int a[])
{
    for(int i=0;i<N;i++)
        a[i]=rand()%40;
}

void centerList(int a[])
{
    for(int i=0;i<N;i++)
        a[i]=80+rand()%41;
}

void printList(int a[])
{
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);
    printf("\n");
}

int main()
{
    srand(time(NULL));

    int req[N];
    int head=100;

    printf("Initial Head = %d\n\n",head);

    // Three Random Lists
    for(int i=1;i<=3;i++)
    {
        printf("Random List %d:\n",i);

        randomList(req);

        printList(req);

        SCAN(req,N,head);
        CSCAN(req,N,head);

        printf("\n");
    }

    // One End
    printf("Requests Near One End:\n");

    endList(req);

    printList(req);

    SCAN(req,N,head);
    CSCAN(req,N,head);

    printf("\n");

    // Centre
    printf("Requests Near Centre:\n");

    centerList(req);

    printList(req);

    SCAN(req,N,head);
    CSCAN(req,N,head);

    return 0;
}