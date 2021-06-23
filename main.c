#include "include/Command.h"
#include "include/executable.h"
#include "include/Process.h"
#include <errno.h>
// NDEBUG;
extern struct VectorProcesses processes;
extern struct Process foreground;

void pr(int r)
{
    printf("\nSIgnal handle\n");
}

int main()
{
    foreground.id = -1;
    signal(SIGINT, endForeground);
    printf("%s\n", strerror(errno));
    
    signal(SIGCHLD, endTask);
    //signal(SIGTERM, pr);

    struct passwd *currentUser = getpwuid(getuid());
    setHomePath(currentUser->pw_name);
    initVectorProcesses(&processes);

    while (1)
    {
        display(getCurrentDir(), currentUser->pw_name);
        char *str = readLine();
        if (str == NULL)
        {
            break;
        }
        struct Command parseStr = parse(str);

        if (parseStr.command == NULL)
        {
            continue;
        }

        if ((strcmp(parseStr.command, "ls") == 0))
        {
            ls(&parseStr.argv);
        }
        else if ((strcmp(parseStr.command, "cd") == 0))
        {
            cd(&parseStr.argv);
        }
        else if (strcmp(parseStr.command, "help") == 0)
        {
            help();
        }
        else if (strcmp(parseStr.command, "quit") == 0)
        {
            quit();
        }
        else
        {
            undefProcess(&parseStr);
        }

        clearCommand(&parseStr);
    }
    // free(currentUser);
}