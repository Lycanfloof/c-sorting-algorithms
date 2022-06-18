#include <stdio.h>

#include "arrayf.h"

int main(void)
{
    int a[] = {9, 9, 8, 8, 7, 7, 6, 6, 1, 1};
    size_t sz = sizeof(a) / sizeof(*a);

    arrayf_selsort(sz, a, false, true);

    for (int i = 0; i < sz; i++)
    {
        printf("a[%d]: %d\n", i, *(a + i));
    }

    arrayf_selsort(sz, a, true, true);

    for (int i = 0; i < sz; i++)
    {
        printf("\na[%d]: %d", i, *(a + i));
    }

    return 0;
}