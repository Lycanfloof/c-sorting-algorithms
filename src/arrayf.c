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
        size_t max = sz <= nsz ? sz : nsz;
        for (size_t i = 0; i < max; i++)
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

bool merge(size_t l, size_t m, size_t r, int *pFirst, bool desc)
{
    bool sorted = false;

    int *larr = arrayf_copy(m - l + 1, pFirst + l, m - l + 1);
    int *rarr = arrayf_copy(r - m, pFirst + m + 1, r - m);

    if (larr != NULL && rarr != NULL)
    {
        size_t inx = l;
        size_t linx = 0;
        size_t rinx = 0;

        while (linx < m - l + 1 || rinx < r - m)
        {
            bool cond = !desc ? *(larr + linx) <= *(rarr + rinx) : *(larr + linx) >= *(rarr + rinx);
            if ((rinx >= r - m) || (!(linx >= m - l + 1) && cond))
            {
                *(pFirst + inx) = *(larr + linx);
                inx++;
                linx++;
            }
            else if ((linx >= m - l + 1) || (!(rinx >= r - m) && !cond))
            {
                *(pFirst + inx) = *(rarr + rinx);
                inx++;
                rinx++;
            }
        }

        sorted = true;
    }

    if (larr != NULL)
        free(larr);
    if (rarr != NULL)
        free(rarr);

    return sorted;
}

bool rcmgsort(size_t l, size_t r, int *pFirst, bool desc)
{
    if (l < r)
    {
        size_t m = (l + r) / 2;
        bool r1 = rcmgsort(l, m, pFirst, desc);
        bool r2 = rcmgsort(m + 1, r, pFirst, desc);
        bool r3 = merge(l, m, r, pFirst, desc);
        return r1 && r2 && r3;
    }
    else
    {
        return true;
    }
}

bool arrayf_rcmgsort(size_t sz, int *pFirst, bool desc)
{
    return rcmgsort(0, sz - 1, pFirst, desc);
}