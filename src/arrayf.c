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
            {
                swap((pFirst + j), (pFirst + j + 1));
            }
        }
    }
}