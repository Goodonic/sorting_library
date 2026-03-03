#include "simple_sorts.h"

static int binary_search_position(void *arr, int left, int right,
                                  void *key, size_t size,
                                  int (*cmp)(const void*, const void*),
                                  long *comparisons)
{

  while (left <= right)
  {
    int mid = left + (right - left) / 2;

    if (comparisons) (*comparisons)++;

    if (cmp(key, elem(arr, mid, size)) < 0)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

void insertion_sort(void *arr, int n, size_t size,
                    int (*cmp)(const void*, const void*),
                    long *comparisons, long *swaps)
{

  if (!arr || n <= 1 || !cmp) return;

  for (int i = 1; i < n; i++)
  {
    void *key = malloc(size);
    if (!key) return;

    memcpy(key, elem(arr, i, size), size);

    int pos = binary_search_position(arr, 0, i - 1, key, size, cmp, comparisons);

    memmove(elem(arr, pos + 1, size), elem(arr, pos, size), (i - pos) * size);

    memcpy(elem(arr, pos, size), key, size);

    free(key);

    if (swaps) (*swaps)++;
  }
}