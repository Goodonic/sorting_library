#include "simple_sorts.h"

int int_cmp(const void *a, const void *b)
{
  int x = *(const int*)a;
  int y = *(const int*)b;
  return (x > y) - (x < y);
}

int is_sorted(int *arr, int n)
{
  for (int i = 1; i < n; i++)
    if (arr[i-1] > arr[i])
      return 0;
  return 1;
}

void run_test(void (*sort_func)(void*,int,size_t,
              int(*)(const void*,const void*),
              long*,long*))
{

  int tests[][6] = {
    {5,2,4,6,1,3},          // random
    {1,2,3,4,5,6},          // sorted
    {6,5,4,3,2,1},          // reversed
    {1,1,1,1,1,1},          // identical
};

  for (int t = 0; t < 4; t++)
  {
    int arr[6];
    memcpy(arr, tests[t], sizeof(arr));

    long cmp = 0, swp = 0;

    sort_func(arr, 6, sizeof(int), int_cmp, &cmp, &swp);

    assert(is_sorted(arr, 6));
  }

  // null
  sort_func(NULL, 0, sizeof(int), int_cmp, NULL, NULL);
}

int main()
{

  run_test(insertion_sort);
  run_test(selection_sort);
  run_test(bubble_sort);
  run_test(gnome_sort);
  run_test(shell_sort);

  printf("All simple sort tests passed.\n");

  return 0;
}