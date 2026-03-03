#include <stdio.h>
#include <stdlib.h>
#include "../../../include/efficient_sorts.h"

// Поиск наименьшего длинны упорядоченного подмассива
int GetMinrun(int n) {
  int r = 0;
  while (n >= 64) {
    r |= n & 1;
    n >>= 1;
  }
  return r + n;
}

static void insertion_sort(int a[], const int lo, const int hi)
{
  for (int i = lo + 1; i <= hi; ++i) {
    const int key = a[i];
    int j = i - 1;
    while (j >= lo && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
}

static void merge(int a[], const int left, const int mid, const int right)
{
  const int n1 = mid - left + 1;
  const int n2 = right - mid;

  int *L = malloc(n1 * sizeof *L);
  int *R = malloc(n2 * sizeof *R);
  if (!L || !R) { perror("malloc"); exit(EXIT_FAILURE); }

  for (int i = 0; i < n1; ++i) L[i] = a[left + i];
  for (int j = 0; j < n2; ++j) R[j] = a[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) a[k++] = L[i++];
    else               a[k++] = R[j++];
  }
  while (i < n1) a[k++] = L[i++];
  while (j < n2) a[k++] = R[j++];

  free(L);
  free(R);
}

void timsort(int a[], const int n)
{
    const int MINRUN = GetMinrun(n);
    run_t stack[64];
    int sz = 0;

    for (int i = 0; i < n; ) {
        int run_len = 1;
        if (i + 1 < n && a[i] > a[i + 1]) {
            while (i + run_len < n && a[i + run_len - 1] > a[i + run_len])
                ++run_len;
            for (int l = i, r = i + run_len - 1; l < r; ++l, --r) {
                int t = a[l]; a[l] = a[r]; a[r] = t;
            }
        } else {
            while (i + run_len < n && a[i + run_len - 1] <= a[i + run_len])
                ++run_len;
        }

        if (run_len < MINRUN) {
            int extra = MINRUN;
            if (i + extra > n) extra = n - i;
            insertion_sort(a, i, i + extra - 1);
            run_len = extra;
        } else {
            insertion_sort(a, i, i + run_len - 1);
        }

        stack[sz++] = (run_t){ i, run_len };
        i += run_len;

        while (sz > 2 &&
               stack[sz - 3].len <= stack[sz - 2].len + stack[sz - 1].len) {

            int lo   = stack[sz - 3].start;
            int mid  = lo + stack[sz - 3].len - 1;
            int hi   = lo + stack[sz - 3].len + stack[sz - 2].len - 1;

            merge(a, lo, mid, hi);

            stack[sz - 3].len += stack[sz - 2].len;
            stack[sz - 2] = stack[sz - 1];
            --sz;
        }
    }

    while (sz > 1) {
        int lo   = stack[sz - 2].start;
        int mid  = lo + stack[sz - 2].len - 1;
        int hi   = lo + stack[sz - 2].len + stack[sz - 1].len - 1;
        merge(a, lo, mid, hi);
        stack[sz - 2].len += stack[sz - 1].len;
        --sz;
    }
}