#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include "ConstVariable.h"
#include <stdio.h>
struct Command
{
    char **argv;
    int argc;
    bool shadow;
};

struct Commands
{
    struct Command *commands;
    int size, capacity;
};

void initCommands(struct Commands *x);

void push_bask(struct Commands *x, struct Command* added);


#endif // COMMAND_H