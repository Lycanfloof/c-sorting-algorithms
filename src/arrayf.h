#ifndef ARRAYF_H
#define ARRAYF_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Inserts an element into some location in the array, pushing the other elements to the side.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  int * -> The address of the element to be moved.
 *  int * -> The address in which the element is gonna be inserted.
 */
void arrayf_swap_and_push(size_t, int *, int *, int *);

/*
 * Swaps two elements of the same array.
 *  size_t -> The size of the array.
 *  int * -> The address of the array.
 *  int * -> The address of the first element.
 *  int * -> The address of the second element.
 */
void arrayf_swap(size_t, int *, int *, int *);

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
 * Returns TRUE if the array got completely sorted, otherwise it returns FALSE.
 */
bool arrayf_rcmgsort(size_t, int *, bool);

#endif