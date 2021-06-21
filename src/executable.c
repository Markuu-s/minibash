#include "../include/executable.h"
void display(char *path, char *user)
{
    printf("%s:%s$ ", user, path);
}

struct Command parse(char *str)
{
    char *p = strtok(str, " ");
    struct Command returned = {};

    if (p)
    {
        returned.command = malloc(sizeof(char *));
        if (returned.command == NULL)
        {
            exit(EXIT_FAILURE);
        }
        returned.command = p;
        p = strtok(NULL, " ");
    }

    int n_space = 0;
    returned.argv = realloc(returned.argv, sizeof(char *) * ++n_space);
    returned.argv[n_space - 1] = returned.command;
    while (p)
    {
        returned.argv = realloc(returned.argv, sizeof(char *) * ++n_space);

        if (returned.argv == NULL)
        {
            exit(EXIT_FAILURE);
        }
        returned.argv[n_space - 1] = p;
        p = strtok(NULL, " ");
    }
    returned.argv = realloc(returned.argv, sizeof(char *) * n_space + 1);
    returned.argv[n_space] = NULL;
    returned.argc = n_space;
    return returned;
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

void setHomePath(char *userName)
{
    char *path = malloc(sizeof(char) * PATH_MAX);
    for (int i = 0; i < 256; ++i)
    {
        path[i] = '\0';
    }
    strcat(path, "/home/");
    strcat(path, userName);
    
    chdir(path);
}

void help()
{
    printf(
        "cd [dir]\n"
        "ls [-l]\n");
}

void ls(char ***argv)
{
    int status;
    switch (fork())
    {
    case -1:
        exit(EXIT_FAILURE);
    case 0:
        execvp("ls", *argv);
    default:
        wait(&status);
        break;
    }
}

bool dirExists(const char **path)
{
    struct stat info;

    if (stat(*path, &info) != 0)
        return false;
    else if (info.st_mode & S_IFDIR)
        return true;
    else
        return false;
}

void cd(char ***argv)
{
    if ((*argv)[1] == NULL)
        return;
    if (chdir((*argv)[1]) != 0)
    {
        printf("cd: %s: No such file or directory\n", (*argv)[1]);
    }
}

char *getCurrentDir()
{
    char *pathName = malloc(sizeof(char) * PATH_MAX);
    char *error = getwd(pathName);
    if (error == NULL)
    {
        printf("Error: couldn`t get current path\n");
    }
    return pathName;
}

void clearCommand(struct Command *x){
    for(int i = 0; i < x->argc - 1; ++i){ // Last element is NULL
        free(x->argv[i]);
    }
}