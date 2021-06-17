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
    char strParse[256][256];
    int cnt = 0;
    int idx = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == ' ')
        {
            ++cnt;
            idx = 0;
        }
        else
        {
            strParse[cnt][idx++] = str[i];
        }
    }
    return strParse;
}

void run()
{
    struct passwd *currentUser = getpwuid(getuid());
    char currentPath[256] = "/home/";
    int lenPath = 0;
    strcat(currentPath, currentUser->pw_name);
    strcat(currentPath, "/");
    while (currentPath[lenPath++] != '\0'){};

    switch (fork())
    {
    case 0:{
        chdir(currentPath);
        break;
    }
    
    default:
    {
        wait(NULL);
        break;
    }
    }
    while (1)
    {
        int len = 0;
        char *str = NULL;
        printf("!!");
        display(currentPath, currentUser->pw_name);
        printf("!!");
        if (getline(&str, &len, stdin) == -1){
            printf("ERROR");
        };
        printf("!!");
        printf("!!%d!!", len);
        char strParse[256][256]; 
        strcat(strParse, parse(str));
        printf("!!%s!!", strParse[0]);
        if ((strncmp(strParse[0], "ls", 2) == 0))
        {
            ls(strParse);
        }
        else if ((strncmp(strParse[0], "cd", 2) == 0))
        {
            cd(strParse, &currentPath, &lenPath);
        }
    }
}

void cd(char **str, char **path, int *lenPath)
{
    if (strncmp(str[1], "..", 2) == 0 && str[1][2] == '\0')
    {
        (*path)[--*lenPath] = '\0';
        while((*path)[*lenPath - 1] != '/'){
            (*path)[--*lenPath] = '\0';
        }
        switch (fork())
        {
        case 0:
            chdir(*path);
            break;
        
        default:
            wait(NULL);
            break;
        }
    }
}


void ls(char **str)
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
        run();
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