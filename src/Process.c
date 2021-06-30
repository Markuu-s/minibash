#include "Process.h"



void initVectorProcesses(struct VectorProcesses *x)
{
    x->capacity = 2;
    x->size = 0;
    x->processes = (struct Process *)malloc(sizeof(struct Process) * x->capacity);
}

void addBackProcess(struct VectorProcesses *x, struct Process *process)
{
    if (x->size == x->capacity)
    {
        x->capacity = (float)x->capacity * 2;
        x->processes = (struct Process *)realloc(x->processes, sizeof(struct Process) * x->capacity);
    }
    x->processes[x->size++] = *process;
}
