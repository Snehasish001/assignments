#include <stdio.h>

#define BLOCKS 5
#define PROCESSES 4

int main()
{
    // Static Input
    int blockSize[BLOCKS] = {100, 500, 200, 300, 600};
    int processSize[PROCESSES] = {212, 417, 112, 426};

    int allocation[PROCESSES];

    for (int i = 0; i < PROCESSES; i++)
        allocation[i] = -1;

    // Worst-Fit Allocation
    for (int i = 0; i < PROCESSES; i++)
    {
        int worst = -1;

        for (int j = 0; j < BLOCKS; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (worst == -1 || blockSize[j] > blockSize[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }

    // Output
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < PROCESSES; i++)
    {
        printf("P%d\t%d\t", i + 1, processSize[i]);

        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}