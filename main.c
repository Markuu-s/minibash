#include "lib/Command.h"
#include "lib/Executable.h"
#include "lib/Process.h"
#include <errno.h>
// NDEBUG;
extern struct VectorProcesses processes;
extern struct Process foreground;

int main()
{
    foreground.id = -1;
    foreground.finish = true;
    signal(SIGINT, endForeground);
    signal(SIGCHLD, endTask);

    struct passwd *currentUser = getpwuid(getuid());
    setHomePath(currentUser->pw_name);
    initVectorProcesses(&processes);

    bool run = true;

    while (run)
    {
        display(getCurrentDir(), currentUser->pw_name);
        char *str = readLine();
        if (str == NULL)
        {
            break;
        }
        struct Command parseStr = parse(str);

        if (parseStr.argv[0] == NULL)
        {
            continue;
        }

        if ((strcmp(parseStr.argv[0], "ls") == 0))
        {
            ls(&parseStr.argv);
        }
        else if ((strcmp(parseStr.argv[0], "cd") == 0))
        {
            cd(&parseStr.argv);
        }
        else if (strcmp(parseStr.argv[0], "help") == 0)
        {
            help();
        }
        else if (strcmp(parseStr.argv[0], "quit") == 0)
        {
            quit();
            run = false;
        }
        else
        {
            undefProcess(&parseStr);
        }

        clearCommand(&parseStr);
        free(str);
    }
    
}