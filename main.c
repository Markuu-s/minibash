#include "include/Command.h"
#include "include/executable.h"

int main()
{
    struct passwd *currentUser = getpwuid(getuid());
    setHomePath(currentUser->pw_name);
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
        }

        free(str);
    }
    free(currentUser);
}