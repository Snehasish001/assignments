#include <stdio.h>

int josephusArray(int n, int k)
{
    int arr[n][2];

    for(int i=0;i<n;i++)
    {
        arr[i][0] = i+1;  
        arr[i][1] = 1;     
    }

    int alive = n;
    int pos = 0;
    int count = 0;

    while(alive > 1)
    {
        if(arr[pos][1] == 1)
        {
            count++;

            if(count == k)
            {
                arr[pos][1] = 0;
                printf("Executed: %d\n", arr[pos][0]);

                alive--;
                count = 0;
            }
        }

        pos = (pos + 1) % n;
    }

    for(int i=0;i<n;i++)
    {
        if(arr[i][1] == 1)
            return arr[i][0];
    }

    return -1;
}

int main()
{
    int n,k;

    printf("Enter number of people: ");
    scanf("%d",&n);

    printf("Enter k: ");
    scanf("%d",&k);

    int survivor = josephusArray(n,k);

    printf("Freed Person = %d\n",survivor);

    return 0;
}