#include "simple_sorts.h"

void selection_sort(void *arr, int n, size_t size,
                    int (*cmp)(const void*, const void*),
                    long *comparisons, long *swaps)
{

  if (!arr || n <= 1 || !cmp) return;

  int left = 0;
  int right = n - 1;

  while (left < right)
  {

    int min = left;
    int max = left;

    for (int i = left; i <= right; i++)
    {

      if (comparisons) (*comparisons)++;
      if (cmp(elem(arr, i, size), elem(arr, min, size)) < 0)
        min = i;

      if (comparisons) (*comparisons)++;
      if (cmp(elem(arr, i, size), elem(arr, max, size)) > 0)
        max = i;
    }

    swap_bytes(elem(arr, left, size), elem(arr, min, size), size, swaps);

    if (max == left) max = min;

    swap_bytes(elem(arr, right, size), elem(arr, max, size), size, swaps);

    left++;
    right--;
  }
}