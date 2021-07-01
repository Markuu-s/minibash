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
