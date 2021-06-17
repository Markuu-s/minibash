#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pwd.h>
#include <string.h>

void display(char *path, char *user)
{
    printf("%s:%s$ ", user, path);
}

void parse()
{
    struct passwd *currentUser = getpwuid(getuid());
    char currentPath[256] = "/home/";
    strcat(currentPath, currentUser->pw_name);
    strcat(currentPath, "/");
    while (1)
    {
        char str[256];
        switch (fork())
        {
        case 0:
        {
            display(currentPath, currentUser->pw_name);
            break;
        }

        default:
        {
            wait(NULL);
            break;
        }
        }
        scanf("%s", str);

        if ((strncmp(str, "ls", 2) == 0))
        {
            ls(currentPath, NULL);
        } else if((strncmp(str, "cd", 2) == 0)){
            
        }
    }
}

void ls(char *path, char **flags)
{
    switch (fork())
    {
    case 0:
    {
        execlp("ls", "ls", NULL, NULL);
        break;
    }

    default:
    {
        wait(NULL);
        break;
    }
    }
}

int main()
{
    switch (fork())
    {
    case 0:
    {
        parse();
        exit(EXIT_SUCCESS);
        break;
    }
    default:
    {
        wait(NULL);
        break;
    }
    }
    exit(EXIT_SUCCESS);
}