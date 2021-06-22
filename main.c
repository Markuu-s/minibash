#include "include/Command.h"
#include "include/executable.h"
#include "include/Process.h"

int main()
{
    struct passwd *currentUser = getpwuid(getuid());
    setHomePath(currentUser->pw_name);
    struct VectorProcesses processes;
    initVectorProcesses(&processes);

    while (1)
    {
        display(getCurrentDir(), currentUser->pw_name);
        char *str = readLine();
        struct Command parseStr = parse(str);

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
        } else {
            undefProcess(&parseStr, &processes);
        }

        free(str);
    }
    free(currentUser);
}