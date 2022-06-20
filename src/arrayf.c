#include "arrayf.h"

void arrayf_swap_and_push(size_t sz, int *pFirst, int *pElementA, int *pElementB)
{
    bool aout = pElementA < pFirst || pElementA >= (pFirst + sz);
    bool bout = pElementB < pFirst || pElementB >= (pFirst + sz);

    if (pElementA == pElementB || aout || bout)
        return;
    else if (pElementA < pElementB)
    {
        int tmp = *pElementA;

        for (size_t i = 0; pElementA + i < pElementB; i++)
        {
            *(pElementA + i) = *(pElementA + i + 1);
        }

        *pElementB = tmp;
    }
    else
    {
        int tmp = *pElementA;

        for (size_t i = 0; pElementA - i > pElementB; i++)
        {
            *(pElementA - i) = *(pElementA - i - 1);
        }

        *pElementB = tmp;
    }
}

void arrayf_swap(size_t sz, int *pFirst, int *pElementA, int *pElementB)
{
    bool aout = pElementA < pFirst || pElementA >= (pFirst + sz);
    bool bout = pElementB < pFirst || pElementB >= (pFirst + sz);

    if (pElementA == pElementB || aout || bout)
        return;
    else
    {
        int tmp = *pElementB;
        *pElementB = *pElementA;
        *pElementA = tmp;
    }
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
            arrayf_swap_and_push(sz, pFirst, (pFirst + sl), (pFirst + i));
        else
            arrayf_swap(sz, pFirst, (pFirst + sl), (pFirst + i));
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
                arrayf_swap_and_push(sz, pFirst, (pFirst + i), (pFirst + j));
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
                arrayf_swap(sz, pFirst, (pFirst + j), (pFirst + j + 1));
        }
    }
}

void rcbbsort_iteration(size_t itr, size_t sz, int *pFirst, bool desc)
{
    if (itr < sz - 1)
    {
        bool cond = !desc ? *(pFirst + itr) > *(pFirst + itr + 1) : *(pFirst + itr) < *(pFirst + itr + 1);
        if (cond)
            arrayf_swap(sz, pFirst, (pFirst + itr), (pFirst + itr + 1));
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
        arrayf_swap_and_push(sz + 1, pFirst, (pFirst + sz), (pFirst + itr));
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