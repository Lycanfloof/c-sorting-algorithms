#include <stdio.h>

#include "arrayf.h"

bool testA(void (*func)(size_t, int *, bool), size_t sz, int *a, int *b, bool desc)
{
    bool isEqual = true;

    func(sz, a, desc);

    for (size_t i = 0; i < sz; i++)
    {
        if (*(a + i) != *(b + i))
        {
            isEqual = false;
            break;
        }
    }

    return isEqual;
}

void testA01(void (*func)(size_t, int *, bool))
{
    int a[] = {1793, 2073, 7079, 1965, 4141, 3559, 4126, 271, 5170, 5379, 3271, 248};
    int b[] = {248, 271, 1793, 1965, 2073, 3271, 3559, 4126, 4141, 5170, 5379, 7079};
    int c[] = {7079, 5379, 5170, 4141, 4126, 3559, 3271, 2073, 1965, 1793, 271, 248};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r1 = testA(func, sz, a, b, false);
    bool r2 = testA(func, sz, a, c, true);

    printf("Result: %s\n", r1 && r2 ? "passed" : "failed");
}

void testA02(void (*func)(size_t, int *, bool))
{
    int a[] = {2923, 6450, 8519, 1761, 5941, 1796, 9159, 1479, 638, 5007, 8438, 7575};
    int c[] = {9159, 8519, 8438, 7575, 6450, 5941, 5007, 2923, 1796, 1761, 1479, 638};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r2 = testA(func, sz, a, c, true);

    printf("Result: %s\n", r2 ? "passed" : "failed");
}

void testA03(void (*func)(size_t, int *, bool))
{
    int a[] = {7587, 4367, 8541, 8606, 6435, 9186, 2366, 6282, 2252, 2164, 1997, 7080};
    int c[] = {1997, 2164, 2252, 2366, 4367, 6282, 6435, 7080, 7587, 8541, 8606, 9186};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r2 = testA(func, sz, a, c, false);

    printf("Result: %s\n", r2 ? "passed" : "failed");
}

void make_testA(int count, void (*func[])(size_t, int *, bool))
{
    for (int i = 0; i < count; i++)
    {
        printf("\n%d:\n", i + 1);
        testA01(*(func + i));
        testA02(*(func + i));
        testA03(*(func + i));
    }
}

bool testB(bool (*func)(size_t, int *, bool), size_t sz, int *a, int *b, bool desc)
{
    bool isEqual = true;

    func(sz, a, desc);

    for (size_t i = 0; i < sz; i++)
    {
        if (*(a + i) != *(b + i))
        {
            isEqual = false;
            break;
        }
    }

    return isEqual;
}

void testB01(bool (*func)(size_t, int *, bool))
{
    int a[] = {1793, 2073, 7079, 1965, 4141, 3559, 4126, 271, 5170, 5379, 3271, 248};
    int b[] = {248, 271, 1793, 1965, 2073, 3271, 3559, 4126, 4141, 5170, 5379, 7079};
    int c[] = {7079, 5379, 5170, 4141, 4126, 3559, 3271, 2073, 1965, 1793, 271, 248};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r1 = testB(func, sz, a, b, false);
    bool r2 = testB(func, sz, a, c, true);

    printf("Result: %s\n", r1 && r2 ? "passed" : "failed");
}

void testB02(bool (*func)(size_t, int *, bool))
{
    int a[] = {2923, 6450, 8519, 1761, 5941, 1796, 9159, 1479, 638, 5007, 8438, 7575};
    int c[] = {9159, 8519, 8438, 7575, 6450, 5941, 5007, 2923, 1796, 1761, 1479, 638};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r2 = testB(func, sz, a, c, true);

    printf("Result: %s\n", r2 ? "passed" : "failed");
}

void testB03(bool (*func)(size_t, int *, bool))
{
    int a[] = {7587, 4367, 8541, 8606, 6435, 9186, 2366, 6282, 2252, 2164, 1997, 7080};
    int c[] = {1997, 2164, 2252, 2366, 4367, 6282, 6435, 7080, 7587, 8541, 8606, 9186};

    size_t sz = sizeof(a) / sizeof(*a);

    bool r2 = testB(func, sz, a, c, false);

    printf("Result: %s\n", r2 ? "passed" : "failed");
}

void make_testB()
{
    printf("\n5:\n");
    testB01(arrayf_rcmgsort);
    testB02(arrayf_rcmgsort);
    testB03(arrayf_rcmgsort);
}

int main(void)
{
    void (*func[])(size_t, int *, bool) = {arrayf_bbsort, arrayf_inssort, arrayf_rcbbsort, arrayf_rcinssort};

    make_testA(4, func);
    make_testB();
    
    return 0;
}