#include <stdlib.h>

#include "efficient_sorts.h"

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

static void merge_sort_td(int a[], const int left, const int right)
{
  if (left >= right) return;

  const int mid = left + (right - left) / 2;
  merge_sort_td(a, left,  mid);
  merge_sort_td(a, mid+1, right);
  merge(a, left, mid, right);
}

void merge_sort_bt(int a[], const size_t n)
{
  int *tmp = malloc(n * sizeof *tmp);
  if (!tmp) { perror("malloc"); exit(EXIT_FAILURE); }

  for (size_t width = 1; width < n; width <<= 1) {
    for (size_t i = 0; i < n; i += 2 * width) {
      size_t left  = i;
      size_t mid   = (i + width < n) ? i + width - 1 : n - 1;
      size_t right = (i + 2 * width < n) ? i + 2 * width - 1 : n - 1;

      size_t l = left, r = mid + 1, k = left;
      while (l <= mid && r <= right) {
        tmp[k++] = (a[l] <= a[r]) ? a[l++] : a[r++];
      }
      while (l <= mid) tmp[k++] = a[l++];
      while (r <= right) tmp[k++] = a[r++];
      for (k = left; k <= right; ++k) a[k] = tmp[k];
    }
  }
  free(tmp);
}


void merge_sort(int a[], const size_t n, const int option)
{
  if (option == 0) merge_sort_bt(a, n);
  else if (n > 1)
  {
    merge_sort_td(a, 0, (int)n - 1);
  }
}