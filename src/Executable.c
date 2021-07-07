#include "Executable.h"

char *getCurrentName()
{
    struct passwd *userInfo = getpwuid(getuid());
    char *userName = malloc(sizeof(char) * LOGIN_NAME_MAX);
    strcpy(userName, userInfo->pw_name);
    if (userName == NULL)
    {
        userName = (char *)malloc(sizeof(char) * 256);
        strcpy(userName, "Undefined user");
    }
    return userName;
}

void display()
{
    char *userName = getCurrentName();
    char *pathName = malloc(sizeof(char) * PATH_MAX);
    char *error = getcwd(pathName, PATH_MAX);
    if (error == NULL)
    {
        strcpy(pathName, "Undefined path");
    }

    printf("%s:%s$ ", userName, pathName);
    free(userName);
    free(pathName);
}

void setHomePath()
{
    char *path = malloc(sizeof(char) * PATH_MAX);
    for (int i = 0; i < 256; ++i)
    {
        path[i] = '\0';
    }
    strcat(path, "/home/");

    char *userName = getCurrentName();
    strcat(path, userName);

    chdir(path);
    free(path);
    free(userName);
}

char *readLine()
{
    size_t lenStr = 0;
    char *str = NULL;
    ssize_t str_len = 0;
    if ((str_len = getline(&str, &lenStr, stdin)) == -1)
    {
        free(str);
        return NULL;
    }
    if (str[str_len - 1] == '\n')
    {
        str[str_len - 1] = '\0';
    }
    return str;
}

Vector parse(char *str)
{
    char *p = strtok(str, " ");
    Vector returned;
    init_vector(&returned, sizeof(Command));

    while (p)
    {
        Command temp;
        temp.shadow = false;
        temp.argv = NULL;

        int n_space = 0;
        while (p)
        {
            char *partStr = strdup(p);
            p = strtok(NULL, " ");

            if (strcmp("|", partStr) == 0)
            {
                free(partStr);
                break;
            }

            temp.argv = realloc(temp.argv, sizeof(char *) * ++n_space);
            temp.argv[n_space - 1] = partStr;
        }

        if (n_space > 0 && strcmp(temp.argv[n_space - 1], "&") == 0)
        {
            temp.shadow = true;
            temp.argv[n_space - 1] = NULL;
        }
        else
        {
            temp.argv = realloc(temp.argv, sizeof(char *) * ++n_space);
            temp.argv[n_space - 1] = NULL;
            temp.argc = n_space;
        }

        push_back(&returned, &temp);
    }
    return returned;
}

void ls(char **argv)
{
    pid_t pid;
    switch (pid = fork())
    {
    case -1:
        exit(EXIT_FAILURE);
    case 0:
        execvp("ls", argv);
    default:
        waitpid(pid, NULL, 0);
        break;
    }
}

void cd(char **argv)
{
    if (argv[1] == NULL)
        return;
    if (chdir(argv[1]) != 0)
    {
        printf("cd: %s: No such file or directory\n", argv[1]);
    }
}