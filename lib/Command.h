#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdio.h>
struct Command
{
    char **argv;
    int argc;
    bool shadow;
};


#endif // COMMAND_H