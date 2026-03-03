#include "simple_sorts.h"

#define N 6

int int_cmp(const void *a, const void *b)
{
  int x = *(const int*)a;
  int y = *(const int*)b;
  return (x > y) - (x < y);
}

void print_array(int *arr, int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void run_sort(const char *name,
                void (*sort_func)(void*, int, size_t,
                int(*)(const void*, const void*),
                long*, long*))
{

  int original[N] = {5, 2, 4, 6, 1, 3};
  int arr[N];
  memcpy(arr, original, sizeof(arr));

  long cmp = 0, swp = 0;

  printf("=== %s ===\n", name);

  printf("Before: ");
  print_array(arr, N);

  sort_func(arr, N, sizeof(int), int_cmp, &cmp, &swp);

  printf("After : ");
  print_array(arr, N);

  printf("Comparisons: %ld\n", cmp);
  printf("Swaps: %ld\n\n", swp);
}

void run_stooge()
{

  int original[N] = {5, 2, 4, 6, 1, 3};
  int arr[N];
  memcpy(arr, original, sizeof(arr));

  long cmp = 0, swp = 0;

  printf("=== Stooge Sort ===\n");

  printf("Before: ");
  print_array(arr, N);

  stooge_sort(arr, 0, N - 1, sizeof(int), int_cmp, &cmp, &swp);

  printf("After : ");
  print_array(arr, N);

  printf("Comparisons: %ld\n", cmp);
  printf("Swaps: %ld\n\n", swp);
}

int main()
{

  run_sort("Insertion Sort", insertion_sort);
  run_sort("Selection Sort", selection_sort);
  run_sort("Bubble Sort", bubble_sort);
  run_sort("Gnome Sort", gnome_sort);
  run_stooge();
  run_sort("Shell Sort", shell_sort);

  return 0;
}