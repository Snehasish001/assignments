#include <stdio.h>

#define N 20

int pages[N] = {
    9, 8, 11, 7, 12, 8, 7, 6, 8, 12,
    5, 4, 12, 3, 10, 11, 12, 4, 9, 4
};

void LRU(int frames)
{
    int frame[10];
    int lastUsed[10];
    int faults = 0;

    for (int i = 0; i < frames; i++)
    {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    for (int i = 0; i < N; i++)
    {
        int found = 0;

        // Check if page is already present
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                lastUsed[j] = i;
                break;
            }
        }

        // Page Fault
        if (!found)
        {
            int pos = 0;

            // Find empty frame
            for (int j = 0; j < frames; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    goto allocate;
                }
            }

            // Find Least Recently Used page
            pos = 0;
            for (int j = 1; j < frames; j++)
            {
                if (lastUsed[j] < lastUsed[pos])
                    pos = j;
            }

allocate:
            frame[pos] = pages[i];
            lastUsed[pos] = i;
            faults++;
        }
    }

    printf("Frames = %d\n", frames);
    printf("Total Page Faults = %d\n\n", faults);
}

int main()
{
    printf("LRU Page Replacement\n");
    printf("--------------------\n\n");

    LRU(4);
    LRU(5);

    return 0;
}