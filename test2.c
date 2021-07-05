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

void Pipes(struct Commands *argv)
{
    int pfd[2];

    if (pipe(pfd) == -1)
    {
        error("Pipe doesn`t work");
    }

    switch (fork())
    {
    case -1:
        error("Fork doesn`t work");
    case 0:
        if (close(pfd[0]) == -1)
        {
            error("Close #1 doesn`t work");
        }

        if (dup2(pfd[1], STDOUT_FILENO) == -1)
        {
            error("Dup2 #1 doesn`t work");
        }
        if (close(pfd[1]) == -1)
        {
            error("Close #2 doesn`t work");
        }

        if (execvp(argv->commands[0].argv[0], argv->commands[0].argv) == -1)
        {
            error("Execvp doesn`t work");
        }
        error("Execvp doesn`t work");

    default:
        break;
    }

    for (int i = 1; i < argv->size - 1; ++i)
    {
        switch (fork())
        {
        case -1:
            error("Fork doesn`t work");
        case 0:
            if (close(pfd[1]) == -1)
            {
                error("Close #1 doesn`t work");
            }

            if (dup2(pfd[0], STDIN_FILENO) == -1)
            {
                error("Dup2 #2 doesn`t work");
            }
            if (close(pfd[0]) == -1)
            {
                error("Close #2 doesn`t work");
            }

            if (dup2(pfd[1], STDOUT_FILENO) == -1)
            {
                error("Dup2 #3 doesn`t work");
            }
            if (close(pfd[1]) == -1)
            {
                error("Close #2 doesn`t work");
            }

            if (execvp(argv->commands[i].argv[0], argv->commands[i].argv) == -1)
            {
                error("Execvp doesn`t work");
            }
            error("Execvp doesn`t work");

        default:
            break;
        }
    }

    switch (fork())
    {
    case -1:
        error("Fork doesn`t work");
    case 0:
        if (close(pfd[1]) == -1)
        {
            error("Close #1 doesn`t work");
        }

        if (dup2(pfd[0], STDIN_FILENO) == -1)
        {
            error("Dup2 #4 doesn`t work");
        }
        if (close(pfd[0]) == -1)
        {
            error("Close #2 doesn`t work");
        }

        if (execvp(argv->commands[argv->size - 1].argv[0], argv->commands[argv->size - 1].argv) == -1)
        {
            error("Execvp doesn`t work");
        }
        error("Execvp doesn`t work");

    default:
        break;
    }

    if (close(pfd[0]) == -1)
        error("close 5");
    if (close(pfd[1]) == -1)
        error("close 6");
    if (wait(NULL) == -1)
        error("wait 1");
    if (wait(NULL) == -1)
        error("wait 2");

    wait(NULL);
}

void Pipes2(struct Commands *argv)
{
    int pfd1[2];
    int pfd2[2];
    if (pipe(pfd1) == -1)
    {
        error("Pfd1 error");
    }

    if (pipe(pfd2) == -1)
    {
        error("Pfd2 error");
    }

    for (int i = 0; i < argv->size; ++i)
    {
        pid_t pid;
        switch (pid = fork())
        {
        case 0:
            if (i == 0)
            {
                close(pfd1[0]);
                close(pfd2[0]);
                close(pfd2[1]);

                if (dup2(pfd1[1], STDOUT_FILENO) == -1)
                {
                    error("Dup2 #1 doesn`t work");
                }
                close(pfd1[1]);
            }
            else if (i + 1 != argv->size)
            {
                close(pfd1[i % 2]);
                close(pfd2[(i % 2 + 1) % 2]);
                if (dup2(pfd1[(i % 2 + 1) % 2], ((i % 2 == 1) ? STDIN_FILENO : STDOUT_FILENO)) == -1)
                {
                    error("Dup2 #2 doesn`t work");
                }
                if (dup2(pfd2[i % 2], ((i % 2 == 1) ? STDIN_FILENO : STDOUT_FILENO)) == -1)
                {
                    error("Dup2 #3 doesn`t work");
                }
                close(pfd1[(i % 2 + 1) % 2]);
                close(pfd2[i % 2]);
            }
            else
            {
                if (i % 2 == 0)
                {
                    close(pfd1[0]);
                    close(pfd1[1]);
                    close(pfd2[1]);
                    if (dup2(pfd2[0], STDIN_FILENO) == -1)
                    {
                        error("Dup2 #4 doesn`t work");
                    }
                    close(pfd2[0]);
                }
                else
                {
                    close(pfd1[1]);
                    close(pfd2[0]);
                    close(pfd2[1]);
                    if (dup2(pfd1[0], STDIN_FILENO) == -1)
                    {
                        error("Dup2 #5 doesn`t work");
                    }
                    close(pfd1[0]);
                }

                if (execvp(argv->commands[i].argv[0], argv->commands[i].argv) == -1)
                {
                    error("execvp");
                }
            }
        default:
            waitpid(pid, NULL, 0);
            
        }
    }
}
int main()
{
    struct Commands a;
    initCommands(&a);

    struct Command first;
    first.argc = 2;
    first.argv = (char **)malloc(sizeof(char *) * (first.argc + 1));
    first.argv[0] = "ls";
    first.argv[1] = "-l";
    first.argv[2] = (char *)NULL;
    push_bask(&a, &first);

    struct Command second;
    second.argc = 2;
    second.argv = (char **)malloc(sizeof(char *) * (second.argc + 1));
    second.argv[0] = "grep";
    second.argv[1] = "f";
    second.argv[2] = (char *)NULL;
    push_bask(&a, &second);

    struct Command third;
    third.argc = 2;
    third.argv = (char **)malloc(sizeof(char *) * (second.argc + 1));
    third.argv[0] = "grep";
    third.argv[1] = "f";
    third.argv[2] = (char *)NULL;
    //push_bask(&a, &third);

    struct Command r;
    r.argc = 2;
    r.argv = (char **)malloc(sizeof(char *) * (second.argc + 1));
    r.argv[0] = "grep";
    r.argv[1] = "i";
    r.argv[2] = (char *)NULL;
    //push_bask(&a, &r);
    Pipes2(&a);
}