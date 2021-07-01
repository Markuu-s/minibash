#include "Vector.h"

void init_vector(Vector *v, size_t sizeOfdata)
{
    v->capacity = START_SIZE;
    v->size = 0;
    v->sizeOfData = sizeOfdata;
    v->data = (void **)malloc(v->capacity * sizeof(void *));
}