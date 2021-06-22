#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
struct Process
{
    pid_t id;
    bool isWork;
};

struct VectorProcesses{
    int capacity;
    int size;
    struct Process* processes;
};

void initVectorProcesses(struct VectorProcesses *x);

void addBackProcess(struct VectorProcesses *x, struct Process* process);

#endif // PROCESS_H