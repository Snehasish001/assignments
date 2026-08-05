#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        // Child Process
        printf("\n--- Child Process ---\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());

        printf("Child is executing...\n");

        exit(10);      // Exit status = 10
    }
    else
    {
        // Parent Process
        wait(&status);     // Wait for child to finish

        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());
        printf("Parent's Parent PID : %d\n", getppid());

        if (WIFEXITED(status))
        {
            printf("Child Exit Status : %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}