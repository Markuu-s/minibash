#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdlib.h>
#include <memory.h>

#define START_SIZE 4
#define INCREASE_CAPACITY 2

/**
 * @brief Data storage of any type
 * @param data is storage of data
 * @param size is actually size of storage
 * @param capacity is reserved memory
 * @param sizeOfData is sizeof(type)
 */
typedef struct
{
    void *data;
    int size;
    int capacity;
    size_t sizeOfData;
} Vector;

#endif // VECTOR_H