#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define LIMIT 1000000
#define CHILDREN 10

int isPrime(int n)
{
    if (n < 2)
        return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

int main()
{
    int range = LIMIT / CHILDREN;

    for (int i = 0; i < CHILDREN; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            int start = i * range + 1;
            int end = (i + 1) * range;
            int count = 0;

            for (int j = start; j <= end; j++)
                if (isPrime(j))
                    count++;

            printf("Child %2d | PID: %5d | Range: %6d - %7d | Primes: %d\n",
                   i + 1, getpid(), start, end, count);

            exit(0);
        }
    }

    // Parent waits for all children
    for (int i = 0; i < CHILDREN; i++)
        wait(NULL);

    printf("\nParent: All child processes have finished.\n");

    return 0;
}