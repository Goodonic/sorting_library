#include "../../../include/efficient_sorts.h"
#include <math.h>

#define INSERTION_SORT_THRESHOLD 16

static void insertion_sort(int a[], const int first, const int last) {
  for (int i = first + 1; i <= last; ++i) {
    const int key = a[i];
    int j = i - 1;
    while (j >= first && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
}

static int hoare_partition(int a[], const int first, const int last) {
  const int pivot = a[first + (last - first) / 2];
  int i = first - 1;
  int j = last + 1;
  while (1) {
    do { ++i; } while (a[i] < pivot);
    do { --j; } while (a[j] > pivot);
    if (i >= j) return j;
    swap(&a[i], &a[j]);
  }
}
/**
 * @brief Рекурсивная часть Introsort.
 *
 * Если подмассив короткий (<= INSERTION_SORT_THRESHOLD) –
 * используется Insertion‑Sort (O(n²), но k ≤ 16 → очень быстро).
 *
 * Если глубина рекурсии превысила `maxDepth` –
 * переключаемся на Heap‑Sort, тем самым гарантируя O(n log n)
 * даже в худшем случае Quick‑Sort.
 *
 * Иначе – обычный Quick‑Sort с Hoare‑partition.
 *
 * @param a          массив
 * @param first      индекс левого конца (включительно)
 * @param last       индекс правого конца (включительно)
 * @param maxDepth   оставшееся допустимое количество уровней рекурсии
 */
static void introsort_rec(int a[], const int first, const int last, const int maxDepth) {
  const int size = last - first + 1;

  if (size <= INSERTION_SORT_THRESHOLD) {
    insertion_sort(a, first, last);
    return;
  }

  if (maxDepth == 0) {
    heap_sort(a + first, size);
    return;
  }

  const int p = hoare_partition(a, first, last);
  introsort_rec(a, first, p, maxDepth - 1);
  introsort_rec(a, p + 1, last, maxDepth - 1);
}

void introsort(int a[], int n) {
  if (n <= 1) return;
  const int maxDepth = (int) (2 * floor(log2(n)));
  introsort_rec(a, 0, n - 1, maxDepth);
}
