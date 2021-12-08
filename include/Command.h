#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

/**
 * @brief struct for storage commands
 * @param argv is commands
 * @param argc is count of commands
 * @param shadow is flag, which points that it command foreaground procces or background
 */
typedef struct
{
    char **argv;
    int argc;
    bool shadow;
} Command;

#endif // COMMAND_H