#ifndef EFFICIENT_SORTS_H
#define EFFICIENT_SORTS_H

void quick_sort(int *s_arr,  int first,  int last);

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

static void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
#endif //EFFICIENT_SORTS_H
