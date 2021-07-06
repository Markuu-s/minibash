#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "Command.h"

void error(char *testMessange)
{
    printf("\n%s: \n", testMessange);
    exit(EXIT_FAILURE);
}

int main()
{
    int pfd1[2];

    if (pipe(pfd1) == -1)
    {
        error("Pfd1 error");
    }
    switch (fork())
    {
    case 0:
        close(pfd1[0]);
        dup2(pfd1[1], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
        break;

    default:
        break;
    }

    switch (fork())
    {
    case 0:
        close(pfd1[1]);
        dup2(pfd1[0], STDIN_FILENO);
        execlp("grep", "grep", "f", NULL);
        break;

    default:
        
        break;
    }
    wait(NULL);
    close(pfd1[0]);
    close(pfd1[1]);
}