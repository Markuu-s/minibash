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

void worker(struct Commands *argv)
{
    int pfd1[2];
    int pfd2[2];

    pipe(pfd1);
    pipe(pfd2);

    for (int i = 0; i < argv->size; ++i)
    {
        pid_t pid;
        switch (pid = fork())
        {
        case 0:
            if (i == 0)
            {
                close(pfd2[0]);
                close(pfd2[1]);

                close(pfd1[0]);
                dup2(pfd1[1], STDOUT_FILENO);

                //close(pfd1[1]);
            }
            if (i + 1 == argv->size)
            {
                if (i % 2 != 0)
                {
                    close(pfd1[1]);
                    close(pfd2[0]);
                    close(pfd2[1]);

                    dup2(pfd1[0], STDIN_FILENO);

                    //close(pfd1[0]);
                }
                else
                {
                    close(pfd1[0]);
                    close(pfd1[1]);
                    close(pfd2[1]);

                    dup2(pfd2[0], STDIN_FILENO);
                    //close(pfd2[0]);
                }
            }
            else
            {
                if (i % 2 == 0)
                {
                    close(pfd1[0]);
                    close(pfd2[1]);

                    dup2(pfd1[1], STDOUT_FILENO);
                    dup2(pfd2[0], STDIN_FILENO);

                    //close(pfd1[1]);
                    //close(pfd2[0]);
                }
                else
                {

                    close(pfd1[1]);
                    close(pfd2[0]);

                    dup2(pfd1[0], STDIN_FILENO);
                    dup2(pfd2[1], STDOUT_FILENO);

                    //close(pfd1[0]);
                    //close(pfd2[1]);
                }
            }

            execvp(argv->commands[i].argv[0], argv->commands[i].argv);  
        default:
            
            break;
        }
    }

    wait(NULL);
    close(pfd1[0]);
    close(pfd1[1]);
    close(pfd2[0]);
    close(pfd2[1]);
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
    second.argv[0] = "tee";
    second.argv[1] = "/dev/fd/2";
    second.argv[2] = (char *)NULL;
    push_bask(&a, &second);

    struct Command third;
    third.argc = 2;
    third.argv = (char **)malloc(sizeof(char *) * (second.argc + 1));
    third.argv[0] = "grep";
    third.argv[1] = "f";
    third.argv[2] = (char *)NULL;
    push_bask(&a, &third);

    push_bask(&a, &second);

    struct Command r;
    r.argc = 2;
    r.argv = (char **)malloc(sizeof(char *) * (second.argc + 1));
    r.argv[0] = "grep";
    r.argv[1] = "i";
    r.argv[2] = (char *)NULL;
    push_bask(&a, &r);
    worker(&a);
}