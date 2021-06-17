#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int idata = 111;

int main()
{
    pid_t childPid = -1123;
    int istack = 222;
    switch (childPid = fork())
    {
    case -1:
    {
        exit(EXIT_FAILURE);
        break;
    }
    case 0:
    {
        idata *= 3;
        istack *= 3;
        break;
    }
    default:
        break;
    }
    int status;
    
    printf("PID=%d %s idata=%d istack=%d\n", getpid(), (childPid == 0) ? "child" : "parent", idata, istack);

    exit(EXIT_SUCCESS);
}