#ifndef ARRAYF_H
#define ARRAYF_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Copies an array into another location in memory.
 *  size_t -> The size of the array to be copied.
 *  int * -> The array to be copied.
 *  size_t -> The size of the new array in memory.
 */
int *arrayf_copy(size_t, int *, size_t);

/*
 * (STABLE | UNSTABLE)
 * Sorts the given array with Selection Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 *  bool -> Execute stable algorithm? (true | false).
 */
void arrayf_selsort(size_t, int *, bool, bool);

/*
 * (STABLE)
 * Sorts the given array with Insertion Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 */
void arrayf_inssort(size_t, int *, bool);

/*
 * (STABLE)
 * Sorts the given array with Bubble Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 */
void arrayf_bbsort(size_t, int *, bool);

/*
 * (STABLE)
 * Sorts the given array with recursive Bubble Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 */
void arrayf_rcbbsort(size_t, int *, bool);

/*
 * (STABLE)
 * Sorts the given array with recursive Insertion Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 */
void arrayf_rcinssort(size_t, int *, bool);

/*
 * (STABLE)
 * Sorts the given array with recursive Merge Sort.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  bool -> Sort in descending order? (true | false).
 */
bool arrayf_rcmgsort(size_t, int *, bool);

#endif