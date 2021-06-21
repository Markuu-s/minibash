#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdio.h>
struct Command
{
    char *command;
    char **argv;
    int argc;
};

bool find(const struct Command *x, char *finder);

#endif // COMMAND_H