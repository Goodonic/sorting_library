#ifndef EFFICIENT_SORTS_H
#define EFFICIENT_SORTS_H

void quick_sort(void *arr, int n, size_t elem_size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps);

void merge_sort(void *arr, int n, size_t elem_size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps);

void heap_sort(void *arr, int n, size_t elem_size,
               int (*cmp)(const void*, const void*),
               long *comparisons, long *swaps);

void tim_sort(void *arr, int n, size_t elem_size,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps);

void intro_sort(void *arr, int n, size_t elem_size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps);
#endif //EFFICIENT_SORTS_H
