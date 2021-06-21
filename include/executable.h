#ifndef EXECUTABLE_H
#define EXECUTABLE_H
#include <unistd.h>
#include <stdio.h> // printf()
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <pwd.h>
#include <string.h>
#include "Command.h"

void display(char *path, char *user);
struct Command parse(char *str);
char *readLine();
void setHomePath(char *userName);
void help();
void ls(char ***argv);
bool dirExists(const char **path);
void cd(char ***argv);
char *getCurrentDir();
void clearCommand(struct Command *x);

#endif // EXECUTABLE_H