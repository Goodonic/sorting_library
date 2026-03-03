#include "simple_sorts.h"

void shell_sort(void *arr, int n, size_t size,
                int (*cmp)(const void*, const void*),
                long *comparisons, long *swaps)
{

  if (!arr || n <= 1 || !cmp) return;

  for (int gap = n / 2; gap > 0; gap /= 2)
  {

    for (int i = gap; i < n; i++)
    {
      void *temp = malloc(size);
      memcpy(temp, elem(arr, i, size), size);

      int j = i;
      while (j >= gap)
      {
        (*comparisons)++;
        if (cmp(elem(arr, j - gap, size), temp) > 0)
        {
          memcpy(elem(arr, j, size), elem(arr, j - gap, size), size);
          j -= gap;
          if (swaps) (*swaps)++;
        }
        else break;
      }

      memcpy(elem(arr, j, size), temp, size);
      free(temp);
    }
  }
}