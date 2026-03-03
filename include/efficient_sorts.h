#ifndef EFFICIENT_SORTS_H
#define EFFICIENT_SORTS_H
#include <c++/cstddef>

void quick_sort(int *s_arr,  int first,  int last);

void merge_sort(int a[], size_t n, int option);

void heap_sort(int arr[], int n);

void tim_sort(void *arr, int n, size_t elem_size,
              int (*cmp)(const void*, const void*),
              long *comparisons, long *swaps);

void intro_sort(void *arr, int n, size_t elem_size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps);

static void swap(int *a, int *b)
{
  const int t = *a;
  *a = *b;
  *b = t;
}
#endif //EFFICIENT_SORTS_H
