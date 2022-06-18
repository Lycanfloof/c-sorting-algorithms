#include "arrayf.h"

void m_left_push(int *pElement, size_t positions)
{
    if (positions == 0)
        return;
    int tmp = *pElement;
    for (int *ptr = pElement; ptr > (pElement - positions); ptr--)
    {
        *ptr = *(ptr - 1);
    }
    *(pElement - positions) = tmp;
}

void swap(int *pElementA, int *pElementB)
{
    if (pElementA == pElementB)
        return;
    int tmp = *pElementB;
    *pElementB = *pElementA;
    *pElementA = tmp;
}

void arrayf_selsort(size_t sz, int *pFirst, bool desc, bool stable)
{
    size_t i, j;
    for (i = 0; i < sz; i++)
    {
        size_t sl = i;
        for (j = sl + 1; j < sz; j++)
        {
            bool cond = !desc ? (*(pFirst + j) < *(pFirst + sl)) : (*(pFirst + j) > *(pFirst + sl));
            sl = cond ? j : sl;
        }
        if (stable)
            m_left_push((pFirst + sl), sl - i);
        else
            swap((pFirst + sl), (pFirst + i));
    }
}

void arrayf_inssort(size_t sz, int *pFirst, bool desc)
{
    size_t i, j;
    for (i = 1; i < sz; i++)
    {
        for (j = 0; j < i; j++)
        {
            bool cond = !desc ? *(pFirst + i) < *(pFirst + j) : *(pFirst + i) > *(pFirst + j);
            if (cond)
            {
                m_left_push((pFirst + i), i - j);
                break;
            }
        }
    }
}

void arrayf_bbsort(size_t sz, int *pFirst, bool desc)
{
    size_t i, j;
    for (i = sz - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            bool cond = !desc ? *(pFirst + j) > *(pFirst + j + 1) : *(pFirst + j) < *(pFirst + j + 1);
            if (cond)
                swap((pFirst + j), (pFirst + j + 1));
        }
    }
}

void rcbbsort_iteration(size_t itr, size_t sz, int *pFirst, bool desc)
{
    if (itr < sz - 1)
    {
        bool cond = !desc ? *(pFirst + itr) > *(pFirst + itr + 1) : *(pFirst + itr) < *(pFirst + itr + 1);
        if (cond)
            swap((pFirst + itr), (pFirst + itr + 1));
        rcbbsort_iteration(itr + 1, sz, pFirst, desc);
    }
}

void arrayf_rcbbsort(size_t sz, int *pFirst, bool desc)
{
    if (sz <= 1)
    {
        return;
    }
    else
    {
        rcbbsort_iteration(0, sz, pFirst, desc);
        arrayf_rcbbsort(sz - 1, pFirst, desc);
    }
}