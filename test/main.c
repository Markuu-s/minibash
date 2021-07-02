#include "Vector.h"
#include <stdio.h>

int main()
{
    Vector a;
    init_vector(&a, sizeof(int));

    Vector b;
    init_vector(&b, sizeof(char));

    int val = 4;
    push_back(&a, &val);
    val = 5;
    push_back(&a, &val);

    for (int i = 0; i < a.size; ++i)
    {
        printf("%d\n", *(int *)a.data[i]);
    }

    val = 4;
    push_back(&b, &val);
    val = 5;
    push_back(&b, &val);

    for (int i = 0; i < a.size; ++i)
    {
        printf("%d\n", *(int *)get(&b, i));
    }

    for (int i = 0; i < a.size; ++i)
    {
        int temp = 0;
        set(&a, i, &temp);
    }

    printf("\n\n\n");
    for (int i = 0; i < a.size; ++i)
    {
        printf("%d\n", *(int *)get(&a, i));
    }

    freeVector(&a);
    freeVector(&b);
}