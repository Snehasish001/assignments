#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int isPalindrome(char str[])
{
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j)
    {
        if (str[i] != str[j])
            return 0;
        i++;
        j--;
    }
    return 1;
}

int main()
{
    int p1[2], p2[2];
    pipe(p1);   // Parent -> Child
    pipe(p2);   // Child -> Parent

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child
        char str[100], result[10];

        while (1)
        {
            read(p1[0], str, sizeof(str));

            if (strcmp(str, "quit") == 0)
                break;

            if (isPalindrome(str))
                strcpy(result, "YES");
            else
                strcpy(result, "NO");

            write(p2[1], result, sizeof(result));
        }
    }
    else
    {
        // Parent
        char str[100], result[10];

        while (1)
        {
            printf("Enter string: ");
            scanf("%s", str);

            write(p1[1], str, sizeof(str));

            if (strcmp(str, "quit") == 0)
                break;

            read(p2[0], result, sizeof(result));
            printf("Child says: %s\n\n", result);
        }

        wait(NULL);
    }

    return 0;
}