#include "include/Command.h"
#include "include/executable.h"

int main()
{
    struct passwd *currentUser = getpwuid(getuid());
    setHomePath(currentUser->pw_name);
    while (1)
    {
        display(getCurrentDir(), currentUser->pw_name);

        struct Command parseStr = parse(readLine());

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

        clearCommand(&parseStr);
    }
    free(currentUser);
}