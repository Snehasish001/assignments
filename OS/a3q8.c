#include <stdio.h>

#define N 20

int pages[N] = {
    9, 10, 7, 12, 7, 6, 12, 6, 5, 4,
    3, 10, 11, 12, 4, 5, 6, 9, 4, 5
};

void FIFO(int frames)
{
    int frame[10];
    int faults = 0;
    int index = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    for (int i = 0; i < N; i++)
    {
        int found = 0;

        // Check if page already exists
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        // Page Fault
        if (!found)
        {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            faults++;
        }
    }

    printf("Frames = %d\n", frames);
    printf("Total Page Faults = %d\n\n", faults);
}

int main()
{
    printf("FIFO Page Replacement\n");
    printf("---------------------\n\n");

    FIFO(3);
    FIFO(4);

    return 0;
}