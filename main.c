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

char **parse(char *str)
{
    char *p = strtok(str, " ");
    char **res = NULL;
    int n_space = 0;
    while (p)
    {
        res = realloc(res, sizeof(char *) * ++n_space);

        if (res == NULL)
        {
            exit(EXIT_FAILURE);
        }
        res[n_space - 1] = p;

        p = strtok(NULL, " ");
    }
    res = realloc(res, sizeof(char *) * (n_space + 1));
    res[n_space] = 0;
    return res;
}

char *readLine()
{
    int lenStr = 0;
    char *str = NULL;
    getline(&str, &lenStr, stdin);
    return str;
}

void setHomePath(char **path, int *lenPath, char *userName)
{
    (*path) = (char *)malloc(sizeof(char) * 256);
    for (int i = 0; i < 256; ++i)
    {
        (*path)[i] = '\0';
    }
    strcat(*path, "/home/");
    strcat(*path, userName);
    strcat(*path, "/");
    for (; (*path)[*lenPath] != '\0'; ++*lenPath)
        ;
    chdir(*path);
}

void run()
{
    struct passwd *currentUser = getpwuid(getuid());
    char *currentPath = NULL;
    int lenPath = 0;
    setHomePath(&currentPath, &lenPath, currentUser->pw_name);
    while (1)
    {

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

        char **parseStr = parse(readLine());
        if ((strncmp(parseStr[0], "ls", 2) == 0))
        {
            ls(parseStr);
        }
        else if ((strncmp(parseStr[0], "cd", 2) == 0))
        {
            cd(parseStr, &currentPath, &lenPath);
        }
        else if (strncmp(parseStr[0], "help", 4) == 0)
        {
            help();
        }
    }
}

void cd(char **str, char **path, int *lenPath)
{
    if (strncmp(str[1], "..", 2) == 0 && *lenPath > 1)
    {
        (*path)[--*lenPath] = '\0';
        while ((*path)[*lenPath - 1] != '/')
        {
            (*path)[--*lenPath] = '\0';
        }
        chdir(*path);
    }
}

void help()
{
    printf(
        "\tcd [dir]\n"
        "\tls\n");
}

void ls(char **str)
{
    switch (fork())
    {
    case 0:
    {
        if (strncmp(str[1], "-l", 2) == 0)
        {
            execlp("ls", "ls", "-l", NULL);
        }
        else
        {
            execlp("ls", "ls", NULL, NULL);
        }
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
    run();
}