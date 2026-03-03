#include "simple_sorts.h"

void bubble_sort(void *arr, int n, size_t size,
                 int (*cmp)(const void*, const void*),
                 long *comparisons, long *swaps)
{

  if (!arr || n <= 1 || !cmp) return;

  int start = 0;
  int end = n - 1;
  int swapped = 1;

  while (swapped)
  {
    swapped = 0;
    int new_end = start;

    for (int i = start; i < end; i++)
    {
      (*comparisons)++;
      if (cmp(elem(arr, i, size), elem(arr, i + 1, size)) > 0)
      {
        swap_bytes(elem(arr, i, size), elem(arr, i + 1, size), size, swaps);
        swapped = 1;
        new_end = i;
      }
    }

    end = new_end;
    if (!swapped) break;

    swapped = 0;
    int new_start = end;

    for (int i = end; i > start; i--)
    {
      (*comparisons)++;
      if (cmp(elem(arr, i - 1, size), elem(arr, i, size)) > 0)
      {
        swap_bytes(elem(arr, i - 1, size), elem(arr, i, size), size, swaps);
        swapped = 1;
        new_start = i;
      }
    }
    start = new_start;
  }
}