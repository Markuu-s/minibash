#include "../include/executable.h"
#include "../include/Process.h"
#include "../include/Command.h"
struct VectorProcesses processes;
void display(char *path, char *user)
{
    printf("%s:%s$ ", user, path);
}

struct Command parse(char *str)
{
    char *p = strtok(str, " ");
    struct Command returned = {};
    returned.shadow = false;

    int n_space = 0;
    if (p)
    {
        returned.command = strdup(p);
        returned.argv = realloc(returned.argv, sizeof(char *) * ++n_space);
        returned.argv[n_space - 1] = returned.command;
    }

    p = strtok(NULL, " ");
    while (p)
    {

        returned.argv = realloc(returned.argv, sizeof(char *) * ++n_space);
        if (returned.argv == NULL)
        {
            exit(EXIT_FAILURE);
        }

        returned.argv[n_space - 1] = strdup(p);
        p = strtok(NULL, " ");
    }

    if (n_space > 0 && strcmp(returned.argv[n_space - 1], "&") == 0)
    {
        returned.shadow = true;
        returned.argv[n_space - 1] = NULL;
    }
    else
    {
        returned.argv = realloc(returned.argv, sizeof(char *) * ++n_space);
        returned.argv[n_space - 1] = NULL;
        returned.argc = n_space;
    }

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
    printf("\n!!!%d!!!\n!!!%d!!!\n", str_len, lenStr);
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
    pid_t child;
    switch (child = fork())
    {
    case -1:
        exit(EXIT_FAILURE);
    case 0:
        execvp("ls", *argv);
    default:
        waitpid(child, NULL, NULL);
        break;
    }
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

void clearCommand(struct Command *x)
{
    free(x->argv[0]);
}

struct Process foreground;
void undefProcess(struct Command *command)
{
    pid_t pid;
    switch (pid = fork())
    {
    case 0:
        if (execvp(command->argv[0], command->argv) == -1)
        {
            printf("Error: couldn`t execute");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);

    default:
        if (command->shadow)
        {
            struct Process *temp = (struct Process *)malloc(sizeof(struct Process) * 1);
            temp[0].id = pid;
            temp[0].finish = false;
            addBackProcess(&processes, &*temp);
        }
        else
        {
            foreground.id = pid;
            int status;
            //wait(NULL);
            waitpid(pid, &status, 0);
        }
        break;
    }
}

void endForeground(int sigInt)
{
    printf("\n!!!\n");
    if (foreground.id != -1)
    {
        kill(foreground.id, SIGTERM);
        foreground.finish = true;
    }
}

void endTask(int sigInt)
{
    pid_t pid = waitpid(-1, NULL, 0);
    if (pid == foreground.id)
    {
        foreground.finish = true;
    }
    else
    {
        for (int i = 0; i < processes.size; ++i)
        {
            if (processes.processes[i].id == pid)
            {
                processes.processes[i].finish = true;
                break;
            }
        }
    }
}

void quit()
{
    if (!foreground.finish){
        kill(foreground.id, SIGTERM);
        foreground.finish = true;
    }

    for(int i = 0; i < processes.size; ++i){
        if (!processes.processes[i].finish){
            kill(processes.processes[i].id, SIGTERM);
            processes.processes[i].finish = true;
        }
    }
}
