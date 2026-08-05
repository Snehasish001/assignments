#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Static Input
    int request[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = 8;
    int head = 53;

    int totalSeek = 0;

    printf("FCFS Disk Scheduling\n");
    printf("--------------------\n");
    printf("Initial Head Position = %d\n\n", head);

    printf("Head Movement:\n");
    printf("%d", head);

    for(int i = 0; i < n; i++)
    {
        totalSeek += abs(request[i] - head);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Seek Time = %d\n", totalSeek);
    printf("Average Seek Time = %.2f\n", (float)totalSeek / n);

    return 0;
}