
#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

/**
 * @brief This struct contains information about proccess
 * 
 */
typedef struct
{
    pid_t id;
    bool finish;
} Process;

#endif // PROCESS_H