#include "simple_sorts.h"

void gnome_sort(void *arr, int n, size_t size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps)
{

  if (!arr || n <= 1 || !cmp) return;

  int i = 0;

  while (i < n)
  {
    if (i == 0)
      i++;
    else
    {
      (*comparisons)++;

      if (cmp(elem(arr, i, size), elem(arr, i - 1, size)) >= 0)
        i++;
      else
      {
        swap_bytes(elem(arr, i, size), elem(arr, i - 1, size), size, swaps);
        i--;
      }
    }
  }
}

void stooge_sort(void *arr, int left, int right, size_t size,
                 int (*cmp)(const void*, const void*),
                 long *comparisons, long *swaps)
{

  if (!arr || left >= right) return;

  (*comparisons)++;
  if (cmp(elem(arr, left, size), elem(arr, right, size)) > 0)
    swap_bytes(elem(arr, left, size), elem(arr, right, size), size, swaps);

  if (right - left + 1 > 2)
  {
    int t = (right - left + 1) / 3;

    stooge_sort(arr, left, right - t, size, cmp, comparisons, swaps);
    stooge_sort(arr, left + t, right, size, cmp, comparisons, swaps);
    stooge_sort(arr, left, right - t, size, cmp, comparisons, swaps);
  }
}