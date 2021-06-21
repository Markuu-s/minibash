#include "../include/Command.h"
bool find(const struct Command *x, char *finder)
{
    for (int i = 0; i < x->argc; ++i)
    {
        if (strcmp(x->argv[i], finder) == 0)
        {
            return true;
        }
    }
    return false;
}