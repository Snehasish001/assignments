#include <stdio.h>

#define TOTAL_BLOCKS 20

int main()
{
    // 0 = Free, 1 = Allocated
    int memory[TOTAL_BLOCKS] = {0};

    // Static Input
    int indexBlock = 5;
    int fileBlocks[] = {2, 7, 10, 15};
    int n = 4;

    // Check if index block is free
    if (memory[indexBlock] == 1)
    {
        printf("Index Block %d is already allocated.\n", indexBlock);
        return 0;
    }

    memory[indexBlock] = 1;

    // Allocate data blocks
    for (int i = 0; i < n; i++)
    {
        if (memory[fileBlocks[i]] == 0)
            memory[fileBlocks[i]] = 1;
        else
        {
            printf("Block %d is already allocated.\n", fileBlocks[i]);
            return 0;
        }
    }

    // Display Allocation
    printf("Indexed File Allocation\n");
    printf("-----------------------\n");
    printf("Index Block : %d\n", indexBlock);

    printf("Data Blocks : ");
    for (int i = 0; i < n; i++)
        printf("%d ", fileBlocks[i]);

    printf("\n");

    return 0;
}