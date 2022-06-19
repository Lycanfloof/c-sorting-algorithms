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

int *arrayf_copy(size_t sz, int *pFirst, size_t nsz)
{
    int *ptr = calloc(nsz, sizeof(*pFirst));
    if (ptr != NULL)
    {
        for (size_t i = 0; i < sz; i++)
        {
            *(ptr + i) = *(pFirst + i);
        }
    }
    return ptr;
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

void rcinssort_iteration(size_t itr, size_t sz, int *pFirst, bool desc)
{
    bool cond = !desc ? *(pFirst + sz) < *(pFirst + itr) : *(pFirst + sz) > *(pFirst + itr);
    if (cond)
        m_left_push((pFirst + sz), sz - itr);
    else if (itr < sz)
        rcinssort_iteration(itr + 1, sz, pFirst, desc);
}

void rcinssort(size_t itr, size_t sz, int *pFirst, bool desc)
{
    if (itr >= sz)
    {
        return;
    }
    else
    {
        rcinssort_iteration(0, itr, pFirst, desc);
        rcinssort(itr + 1, sz, pFirst, desc);
    }
}

void arrayf_rcinssort(size_t sz, int *pFirst, bool desc)
{
    rcinssort(1, sz, pFirst, desc);
}

void merge(int *pFirst, int *pFstHalf, size_t n1, int *pScndHalf, size_t n2, bool desc)
{
    size_t fst = 0;
    size_t scnd = 0;
    while (fst < n1 || scnd < n2)
    {
        bool cond = !desc ? *(pFstHalf + fst) <= *(pScndHalf + scnd) : *(pFstHalf + fst) >= *(pScndHalf + scnd);
        if ((fst >= n1) || (!(scnd >= n2) && !cond))
        {
            *(pFirst + fst + scnd) = *(pScndHalf + scnd);
            scnd++;
        }
        else if ((scnd >= n2) || (!(fst >= n1) && cond))
        {
            *(pFirst + fst + scnd) = *(pFstHalf + fst);
            fst++;
        }
    }
}

bool arrayf_rcmgsort(size_t sz, int *pFirst, bool desc)
{
    if (sz > 1)
    {
        size_t n2 = sz / 2;
        size_t n1 = sz - n2;

        int *pFstHalf = arrayf_copy(n1, pFirst + 0, n1);
        if (pFstHalf == NULL)
            return false;

        int *pScndHalf = arrayf_copy(n2, pFirst + n1, n2);
        if (pScndHalf == NULL)
        {
            free(pFstHalf);
            return false;
        }

        bool r1 = arrayf_rcmgsort(n1, pFstHalf, desc);
        bool r2 = arrayf_rcmgsort(n2, pScndHalf, desc);

        if (!(r1 && r2))
        {
            return false;
        }

        merge(pFirst, pFstHalf, n1, pScndHalf, n2, desc);

        free(pFstHalf);
        pFstHalf = NULL;

        free(pScndHalf);
        pScndHalf = NULL;
    }
    return true;
}