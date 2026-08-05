#include <stdio.h>

#define P 5
#define R 3

int main()
{
    int alloc[P][R] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    int max[P][R] = {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    int avail[R] = {3,3,2};

    int need[P][R];
    int finish[P] = {0};
    int safe[P];

    // Calculate Need Matrix
    for(int i=0;i<P;i++)
        for(int j=0;j<R;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int count = 0;

    while(count < P)
    {
        int found = 0;

        for(int i=0;i<P;i++)
        {
            if(!finish[i])
            {
                int j;

                for(j=0;j<R;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j==R)
                {
                    for(int k=0;k<R;k++)
                        avail[k] += alloc[i][k];

                    finish[i] = 1;
                    safe[count++] = i;
                    found = 1;
                }
            }
        }

        if(!found)
            break;
    }

    if(count == P)
    {
        printf("System is in SAFE state.\n");
        printf("Safe Sequence: ");

        for(int i=0;i<P;i++)
            printf("P%d ", safe[i]);

        printf("\n");
    }
    else
    {
        printf("System is NOT in SAFE state.\n");
    }

    return 0;
}