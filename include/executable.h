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

/*
    Display information about user and current
    directory on terminal
*/
void display(char *path, char *user);

/*
    Parse string into command and arguments.
*/
struct Command parse(char *str);

/*
    Read line from terminal
*/
char *readLine();

/*
    Set home path as default. /home/USERNAME
*/
void setHomePath(char *userName);

/*
    List of available commands
*/  
void help();

/*
    Command is ls. Show information in folders
*/
void ls(char ***argv);

/*
    Command is cd. Navigate in folders
*/
void cd(char ***argv);

/*
    Get string of current directory
*/
char *getCurrentDir();

/*
    Free memory of struct Command
*/
void clearCommand(struct Command *x);

#endif // EXECUTABLE_H