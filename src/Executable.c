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

void setHomePath(){
    char *path = malloc(sizeof(char) * PATH_MAX);
    for (int i = 0; i < 256; ++i)
    {
        path[i] = '\0';
    }
    strcat(path, "/home/");

    char *userName = getCurrentName();

    chdir(path);
    free(path);
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