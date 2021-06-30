#include "Command.h"

// const int START_CAPACITY = 2;
// const int ARRAY_INCREASE = 2;

void initCommands(struct Commands *x)
{
    x->capacity = 2;
    x->size = 0;
    x->commands = (struct Command *)malloc(sizeof(struct Command) * x->capacity);
}

void push_bask(struct Commands *x, struct Command* added)
{
    if (x->size == x->capacity)
    {
        x->capacity = (float)x->capacity * 2;
        x->commands = (struct Command *)realloc(x->commands, sizeof(struct Command) * x->capacity);
    }
    x->commands[x->size++] = *added;
}